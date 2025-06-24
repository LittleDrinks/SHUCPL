	MIDIexample.cpp
#include "MIDIexample.h"
#include <iostream>
#include <ctime>
using namespace std;

double gettime(int restart)					// 参数带默认值，非零表示重新计时
{											// 否则累计计时
	const double c = 1.0/CLOCKS_PER_SEC;
	static clock_t t = clock();				// 静态局部变量。第一次调用时，确定计时起点
	if(restart) t = clock();				// 根据实参决定是否重新确定计时起点
	return c*(clock()-t);					// 从上一计时点到现在所经历的时间
}

DWORD MidiOutMessage(HMIDIOUT hMidi, int iStatus, int iChannel, int iFlip, int iVolume)
{
	DWORD dwMessage = (iVolume << 16) | (iFlip << 8) | iStatus         | iChannel;
					//      音量      |     音符     | 状态字节(高4位) | 通道(低4位)
	return midiOutShortMsg(hMidi, dwMessage);
}

void HelloWorld(HMIDIOUT hMidiOut)
{
	MidiOutMessage(hMidiOut, 0xC0, 0, 0, 0);	// 设置通道0的音色为钢琴

	MidiOutMessage(hMidiOut, 0x90, 0, 60, 112);	// 开音中央C(小字1组c1)，力度112(ff)
	Sleep(500);
	MidiOutMessage(hMidiOut, 0x80, 0, 60, 127);	// 关音中央C(小字1组c1)，速度127（立即）

	MidiOutMessage(hMidiOut, 0x90, 0, 64, 80);	// 开音e1，力度80(mf)
	Sleep(500);
	MidiOutMessage(hMidiOut, 0x80, 0, 64, 127);	// 关音e1

	MidiOutMessage(hMidiOut, 0x90, 0, 67, 96);	// 开音g1，力度96(f)
	Sleep(500);
	MidiOutMessage(hMidiOut, 0x80, 0, 67, 127);	// 关音g1

	MidiOutMessage(hMidiOut, 0x90, 0, 60, 80);	// 和弦，力度80(mf)
	MidiOutMessage(hMidiOut, 0x90, 0, 64, 80);
	MidiOutMessage(hMidiOut, 0x90, 0, 67, 80);
	MidiOutMessage(hMidiOut, 0x90, 0, 72, 80);
	Sleep(2500);
	MidiOutMessage(hMidiOut, 0x80, 0, 60, 127);	// 关音
	MidiOutMessage(hMidiOut, 0x80, 0, 64, 127);
	MidiOutMessage(hMidiOut, 0x80, 0, 67, 127);
	MidiOutMessage(hMidiOut, 0x80, 0, 72, 127);
}

/*	本下面的测试函数采取的是最简单的处理方式。存在的问题主要有：
1. 使用Sleep函数，在时间同步上很不精确，还产生了较大的累积误差（程序中用dt和dt1的目的是想尽量抵消一些误差）。
   【改进方案】 可考虑改用多媒体计时器，精确到1毫秒。
2. 音符的表达不直观，数据录入不方便。曲调、拍子数、速度固定，不灵活。
   【改进方案】 可考虑设计一套符号系统直观表达乐谱（音符、时长、力度等）存入数据文件（如文本文件），
				然后读取文件，并将符号转换成MIDI所需的信息，最后播放。
				或者研究mid文件的格式，直接生成mid文件，在用音频播放器播放。
*/
void Test(HMIDIOUT hMidiOut, int flag)			// 党啊，亲爱的妈妈（钢琴伴奏前2小节）
{
	double t=1000;								// 速度：1拍的时值（1000毫秒=1秒），每分钟60拍
	char mf=80;									// 力度：mf中强
	Music PianoR[] = { {77,mf-10,0,0}, {81,mf-10,0}, {84,mf-10,0}, {89,mf-10,t/2},			// 钢琴伴奏（右手部分）
					   {77,mf   ,0},   {81,mf   ,0}, {84,mf   ,0}, {89,mf   ,t},			// 切分音改变小节中的强弱
					   {79,mf-10,0},   {91,mf-10,t/2},
					   {77,mf-10,0},   {82,mf-10,0}, {86,mf-10,0}, {89,mf-10,t/4},
					   {74,mf- 5,0},   {86,mf- 5,t/2},
					   {72,mf-10,0},   {84,mf-10,t/4},
					   {70,mf-10,0},   {82,mf-10,t/2},
					   {69,mf-10,0},   {81,mf-10,t/2},
					   {72,mf   ,0}, {77,mf   ,0}, {81,mf,0}, {84,mf,t/2},					// 第2小节
					   {72,mf   ,0}, {77,mf   ,0}, {81,mf,0}, {84,mf,t/4},
					   {74,mf   ,0}, {86,mf   ,t/4},
					   {72,mf-10,0}, {84,mf-10,t/2},
					   {70,mf-10,0}, {82,mf-10,t/4},
					   {69,mf-10,0}, {81,mf-10,t/4},
					   {67,mf- 5,0}, {72,mf- 5,0}, {76,mf-5,0}, {79,mf-2,2*t} };
	Music PianoL[] = { {41,mf   ,t/4,0}, {48,mf   ,t/4}, {57,mf   ,t/4}, {60,mf   ,t/4},	// 钢琴伴奏（左手部分）
					   {69,mf-10,t/4},   {65,mf-10,t/4}, {60,mf-10,t/4}, {57,mf-10,t/4},
					   {46,mf- 5,t/4},   {53,mf- 5,t/4}, {58,mf- 5,t/4}, {62,mf- 5,t/4},
					   {65,mf-10,t/4},   {62,mf-10,t/4}, {58,mf-10,t/4}, {53,mf-10,t/4},
					   {41,mf   ,t/4},   {48,mf   ,t/4}, {57,mf   ,t/4}, {60,mf   ,t/4},	// 第2小节
					   {69,mf-10,t/4},   {65,mf-10,t/4}, {60,mf-10,t/4}, {57,mf-10,t/4},
					   {48,mf- 5,t/4},   {55,mf- 5,t/4}, {60,mf- 5,t/4}, {64,mf- 5,t/4},
					   {67,mf-10,t/4},   {64,mf-10,t/4}, {60,mf-10,t/4}, {55,mf-10,t/4} };
	Music *p[] = {PianoR, PianoL};															// 指针数组，方便访问上述两个数组
	int n = sizeof(p)/sizeof(*p), i, j, i0=0, i1=n, dt=250, dt1=dt-18;
	int len[] = {sizeof(PianoR)/sizeof(*PianoR), sizeof(PianoL)/sizeof(*PianoL)};
	double totalTime = 0;
	int k[]={0,0}, beg[]={0,0}, end[]={0,0}, channel[]={0,1};
	
	if(flag==1)												// 仅播放钢琴伴奏的右手部分
		i1 = i0+1;
	else if(flag==2)										// 仅播放钢琴伴奏的左手部分
		i0 = 1;
	
	for(i=i0; i<i1; i++)									// 计算总时长
	{
		for(j=0; j<len[i]; j++)
			p[i][j].time = p[i][j-1].time + p[i][j].deltaTime;
		if(p[i][j-1].time > totalTime)
			totalTime = p[i][j-1].time;
	}

	cout << "\n\t\t党啊，亲爱的妈妈(钢琴伴奏前2小节)" << endl;
	for(i=i0; i<i1; i++)									// 播放各通道的第一个音符
	{
		MidiOutMessage(hMidiOut, 0xC0, channel[i], 0, 0);	// 设置通道channel[i]的音色为钢琴
	}
	gettime(1);
	for(double time=0; time < totalTime; time+=dt)			// 对于本例而言，最小的delta为t/4=250，故本循环步长为50
	{
		for(i=i0; i<i1; i++)
		{
			if(p[i][k[i]].time < time)
			{
				for(j=beg[i]; j<end[i]; j++)							// 关音，可能是和弦
					MidiOutMessage(hMidiOut, 0x80, channel[i], p[i][j].note, 127);
				beg[i] = k[i];
				cout << '[' << i << ']';
				for( ; k[i]<len[i] && p[i][k[i]].time < time; k[i]++)	// 开音，可能是和弦
				{
					MidiOutMessage(hMidiOut, 0x90, channel[i], p[i][k[i]].note, p[i][k[i]].volume);
					cout << "\t(" << int(p[i][k[i]].note) << ", " << p[i][k[i]].deltaTime << ", " << int(p[i][k[i]].volume) << ')';
				}
				end[i] = k[i];
				cout << endl;
			}
		}
		Sleep(dt1);
	}
	for(i=i0; i<i1; i++)
	{
		for(j=beg[i]; j<end[i]; j++)									// 关音，可能是和弦
			MidiOutMessage(hMidiOut, 0x80, channel[i], p[i][j].note, 127);
	}
	cout << "总时长: " << gettime() << "秒" << endl;
}
