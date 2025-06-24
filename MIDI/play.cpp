//
// Created by LittleDrinks on 25-6-20.
// Sincere gratitude to 【C++ 也能照着乐谱弹钢琴？让你的代码有 bgm 伴奏！】 https://www.bilibili.com/video/BV1DH4y117ga
//
#include <Windows.h>
#include <thread>
#include <conio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <iostream>
#include <assert.h>
#include <mutex>
#include <regex>
#include <atomic>
#include <chrono>
#include <condition_variable>

bool isNumeric(std::string const &str){
    return regex_match(str,std::regex("[(-|+)|][0-9]+"));
}

class Player {
private:
    enum scale{
        Rest=0,
        C8=108,
        B7=107,A7s=106,A7=105,G7s=104,G7=103,F7s=102,F7=101,E7=100,D7s=99, D7=98, C7s=97, C7=96,
        B6=95, A6s=94, A6=93, G6s=92, G6=91, F6s=90, F6=89, E6=88, D6s=87, D6=86, C6s=85, C6=84,
        B5=83, A5s=82, A5=81, G5s=80, G5=79, F5s=78, F5=77, E5=76, D5s=75, D5=74, C5s=73, C5=72,
        B4=71, A4s=70, A4=69, G4s=68, G4=67, F4s=66, F4=65, E4=64, D4s=63, D4=62, C4s=61, C4=60,
        B3=59, A3s=58, A3=57, G3s=56, G3=55, F3s=54, F3=53, E3=52, D3s=51, D3=50, C3s=49, C3=48,
        B2=47, A2s=46, A2=45, G2s=44, G2=43, F2s=42, F2=41, E2=40, D2s=39, D2=38, C2s=37, C2=36,
        B1=35, A1s=34, A1=33, G1s=32, G1=31, F1s=30, F1=29, E1=28, D1s=27, D1=26, C1s=25, C1=24,
        B0=23, A0s=22, A0=21
    };
    const int C_Scale[7][7]={{C1,D1,E1,F1,G1,A1,B1},
                             {C2,D2,E2,F2,G2,A2,B2},
                             {C3,D3,E3,F3,G3,A3,B3},
                             {C4,D4,E4,F4,G4,A4,B4},
                             {C5,D5,E5,F5,G5,A5,B5},
                             {C6,D6,E6,F6,G6,A6,B6},
                             {C7,D7,E7,F7,G7,A7,B7}};
    const int C_Scale_s[7][7]={{C1s,D1s,-1,F1s,G1s,A1s,-1},
                               {C2s,D2s,-1,F2s,G2s,A2s,-1},
                               {C3s,D3s,-1,F3s,G3s,A3s,-1},
                               {C4s,D4s,-1,F4s,G4s,A4s,-1},
                               {C5s,D5s,-1,F5s,G5s,A5s,-1},
                               {C6s,D6s,-1,F6s,G6s,A6s,-1},
                               {C7s,D7s,-1,F7s,G7s,A7s,-1}};
    HMIDIOUT handle;
    int dctn=500;
    int volume=0x7f;
    std::vector<std::string> musicList;
    int tick[2];
    std::atomic<bool> ENDMUSIC{false};
    std::atomic<int> STOP{0};
    std::thread bgm_thread;
    std::condition_variable cv;
    std::mutex mu;
public:
    Player() {
        musicList.clear();
        midiOutOpen(&handle, 0, 0, 0, CALLBACK_NULL);
    }
    ~Player() {
        stop();
        musicList.clear();
        midiOutClose(handle);
    }
    void setDelay(int _dctn) {
        dctn=_dctn;
    }
    void setVolume(int _v) {
        volume=_v;
    }
    bool readFile(std::string fileName) {
        musicList.clear();
        std::ifstream in(fileName);
        if (!in.is_open()) { return false; }
        in >> dctn;
        std::string s;
        while (std::getline(in, s)) { musicList.push_back(s); }
        in.close();
        return true;
    }
    void playSingle(std::string s, int idx) {
        mu.lock();
        std::cerr << "tune " << idx << " start at " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() << "\n";
        mu.unlock();

        std::vector<int> buffer;
        s = s + " ";  // 休止符
        int n = s.length();
        int ctn = 32*21;  // 音符持续时长
        int sumTic = 0;   // 累计播放时长
        int vol = volume;
        bool isChord = false;
        buffer.clear();
        int st = clock();
        for (int i = 0; i < n; ++i) {
            if (ENDMUSIC) { break; }
            char c = s[i];
            switch (c) {
                case '[': case '{': { assert(isChord==0); isChord = 1; break; }
                case ']': case '}': { assert(isChord==1); isChord = 0; break; }
                case ' ': {
                    if (!isChord) {
                        if (!buffer.empty()) {
                            for (auto note: buffer) {
                                if (note != 0) { midiOutShortMsg(handle, note); }
                            }
                            buffer.clear();
                            while ((clock() - st) * 1000.0 / CLOCKS_PER_SEC < dctn / 32.0 / 21.0 * (sumTic + ctn));
                            sumTic += ctn;
                            ctn = 32*21;
                        }
                    }
                    break;
                }
                case '|': break;
                case '_': ctn /= 2; break;
                case '*': ctn /= 3; break;
                case '&': ctn /= 7; break;
                case '%': ctn /= 5; break;
                case '.': ctn *= 1.5; break;
                case '-': ctn += 32*21; break;
                case '0': buffer.push_back(Rest); break;
                default: {
                    assert('1' <= c && c <= '7');
                    int x = c - '1';
                    int lvl = 3;  // 音高
                    bool isSharp = 0;  // 升半音
                    for (int j = i + 1; j < n; ++j) {
                        if (s[j] == '^') { ++lvl; }
                        else if (s[j] == ',') { --lvl; }
                        else if (s[j] == '#') { isSharp = 1; }
                        else { break; }
                        ++i;
                    }
                    buffer.push_back((
                        (vol << 16)
                        + ((isSharp? C_Scale_s[lvl][x]: C_Scale[lvl][x]) << 8)
                        + 0x90
                    ));
                    break;
                }
            }
        }
        tick[idx] = sumTic;
        if (++STOP >= 2) { cv.notify_all(); }
        mu.lock();
        std::cerr << "tune " << idx << " end at " << std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::high_resolution_clock::now().time_since_epoch()).count() << "\n";
        mu.unlock();
    }
    void playSync(std::string s1, std::string s2 = "") {
        STOP = 0;
        tick[0] = 0;
        tick[1] = 0;
        std::thread tune1(&Player::playSingle, this, s1, 0); tune1.detach();
        std::thread tune2(&Player::playSingle, this, s2, 1); tune2.detach();
        std::unique_lock<std::mutex> lock(mu);
        cv.wait(lock, [&]{ return STOP >= 2; });
        if (tick[0] != tick[1]) { std::cerr << "tune not sync\n"; }
        std::cerr << tick[0] << " " << tick[1] << "\n";
    }
    void playList(int st = 0) {
        ENDMUSIC = 0;
        int n = musicList.size();
        for (int i = st; i < n; ++i) {
            if (ENDMUSIC) { break; }
            std::string s = musicList[i];
            if (isNumeric(s)) { setDelay(std::stoi(s)); continue; }
            if (s == "") { continue; }
            std::string s1 = s;
            std::string s2 = "";
            if (i + 1 < n) { s2 = musicList[i + 1]; ++i; }
            playSync(s1, s2);
        }
    }
    void playThread() {
        while (!ENDMUSIC) {
            playList();
            std::this_thread::sleep_for(std::chrono::milliseconds(10));
            ENDMUSIC = 0;
            break;
        }
    }
    void start() {
        ENDMUSIC = 0;
        bgm_thread = std::thread(&Player::playThread, this);
    }
    void stop() {
        ENDMUSIC = true;
        if (bgm_thread.joinable()) bgm_thread.join();
    }
};

int main() {
    Player player;
    player.readFile("起风了.txt");
    player.start();
    // std::cout << "按下任意键停止播放...";
    std::cin.get();
    player.stop();
}