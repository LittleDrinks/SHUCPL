// KbMIDI.cpp		键盘弹奏MIDI
#include "KbMIDI.h"
#include <cstdio>
#include <cstring>
#include <conio.h>
using namespace std;

char Notes[88][4] = {										  "A2", "#A2", "B2",	// 21,22,23
	"C1", "#C1", "D1", "#D1", "E1", "F1", "#F1", "G1", "#G1", "A1", "#A1", "B1",	// 24~35
	"C",  "#C",  "D",  "#D",  "E",  "F",  "#F",  "G",  "#G",  "A",  "#A",  "B",		// 36~47
	"c",  "#c",  "d",  "#d",  "e",  "f",  "#f",  "g",  "#g",  "a",  "#a",  "b",		// 48~59
	"c1", "#c1", "d1", "#d1", "e1", "f1", "#f1", "g1", "#g1", "a1", "#a1", "b1",	// 60~71(60中央C，小字1组c1)
	"c2", "#c2", "d2", "#d2", "e2", "f2", "#f2", "g2", "#g2", "a2", "#a2", "b2",	// 72~83
	"c3", "#c3", "d3", "#d3", "e3", "f3", "#f3", "g3", "#g3", "a3", "#a3", "b3",	// 84~95
	"c4", "#c4", "d4", "#d4", "e4", "f4", "#f4", "g4", "#g4", "a4", "#a4", "b4",	// 96~107
	"c5"};																			// 108

DWORD MidiOutMessage(HMIDIOUT hMidi, int iStatus, int iChannel, int iFlip, int iVolume)
{
	DWORD dwMessage = (iVolume << 16) | (iFlip << 8) | iStatus         | iChannel;
					//      音量      |     音符     | 状态字节(高4位) | 通道(低4位)
	return midiOutShortMsg(hMidi, dwMessage);
}

int Do2Si(int a[8], const char *notes)
{
	int i;
	for(i=0; i<88; i++)
		if(strcmp(notes, Notes[i])==0)
			break;
	i += 21;
	if(i>108) i = 60;
	a[0] = 0;		// 休止符
	a[1] = i;		// Do
	a[2] = i+2;		// Re
	a[3] = i+4;		// Mi
	a[4] = i+5;		// Fa
	a[5] = i+7;		// Sol
	a[6] = i+9;		// La
	a[7] = i+11;	// Si
	return i;
}

void Show(HANDLE hStdOut, const char *notes)
{
	DWORD result;
	COORD coord;
	char str0[100], str1[100] = "弹奏时Shift组合升半音  ↑曲调升半音  ↓曲调降半音  [9]打击乐通道  [End]退出     ";
	char *str[100]={"F1  F2  F3  F4  F5  F6  F7 (高八度)",
					"1   2   3   4   5   6   7",
					" Q   W   E   R   T   Y   U (低八度)"};
	coord.X = 10;	coord.Y = 4;
	for(int i=0; i<3; i++)
	{
		SetConsoleCursorPosition(hStdOut, coord);
		WriteConsole(hStdOut, str[i], strlen(str[i]), &result, NULL);
		coord.Y += 2;
	}

	coord.X = 0;	coord.Y = 23;
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED | BACKGROUND_BLUE);
	WriteConsole(hStdOut, str1, strlen(str1), &result, NULL);
	
	coord.X = 10;	coord.Y = 2;
	sprintf(str0, "1 = %s ", notes);
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY | BACKGROUND_RED);
	WriteConsole(hStdOut, str0, strlen(str0), &result, NULL);
	coord.Y = 16;
	SetConsoleCursorPosition(hStdOut, coord);
	SetConsoleTextAttribute(hStdOut, 7);
}

void kbMIDI(char *notes)
{
	int delay = 10;		// 375;
	int index, key = 1, note=60, a[8];
	bool flag = true;
	char noteStr[4];
	HANDLE hStdIn, hStdOut;
	hStdIn = GetStdHandle(STD_INPUT_HANDLE);
	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTitle("键盘MIDI即兴弹奏");

	HMIDIOUT hMidiOut;
	midiOutOpen(&hMidiOut, MIDIMAPPER, 0, 0, 0);
	MidiOutMessage(hMidiOut, 0xC0, 0, 0, 0);	// 钢琴

	index = Do2Si(a, notes) - 21;
	strcpy(noteStr, notes);
	
	while(true)
	{
		flag = true;
		Show(hStdOut, Notes[index]);
		key = getch();
		if(key==224)
		{
			key = getch();
			if(key==72)			// Up
			{
				strcpy(noteStr, Notes[index+1]);
				index = Do2Si(a, noteStr) - 21;
				continue;
			}
			else if(key==80)	// Down
			{
				strcpy(noteStr, Notes[index-1]);
				index = Do2Si(a, noteStr) - 21;
				continue;
			}
			else if(key==79)	// End
				break;
			else
				continue;
		}
		if(key==0)
		{
			key = getch();
			if(59<=key && key<=65)					// F1~F7，高八度
				note = a[key-58] + 12;
			else if(84<=key && key<=90)				// Shift+F1~F7，高八度且升半音
				note = a[key-83] + 13;
			else
				continue;
		}
		else
		{
			switch(key)
			{
			case '1': note = a[1];		break;
			case '!': note = a[1]+1;	break;
			case '2': note = a[2];		break;
			case '@': note = a[2]+1;	break;
			case '3': note = a[3];		break;
			case '#': note = a[3]+1;	break;
			case '4': note = a[4];		break;
			case '$': note = a[4]+1;	break;
			case '5': note = a[5];		break;
			case '%': note = a[5]+1;	break;
			case '6': note = a[6];		break;
			case '^': note = a[6]+1;	break;
			case '7': note = a[7];		break;
			case '&': note = a[7]+1;	break;
			case 'q': note = a[1]-12;	break;
			case 'Q': note = a[1]-11;	break;
			case 'w': note = a[2]-12;	break;
			case 'W': note = a[2]-11;	break;
			case 'e': note = a[3]-12;	break;
			case 'E': note = a[3]-11;	break;
			case 'r': note = a[4]-12;	break;
			case 'R': note = a[4]-11;	break;
			case 't': note = a[5]-12;	break;
			case 'T': note = a[5]-11;	break;
			case 'y': note = a[6]-12;	break;
			case 'Y': note = a[6]-11;	break;
			case 'u': note = a[7]-12;	break;
			case 'U': note = a[7]-11;	break;
			case '9': flag = false;
					  kbMIDICh9(hStdOut, hMidiOut);		break;
			default: continue;
			}
		}
		if(flag)
		{
			MidiOutMessage(hMidiOut, 0x90, 0, note, 127);
			Sleep(delay);
		}
	}
	midiOutClose(hMidiOut);
}

void kbMIDICh9(HANDLE &hStdOut, HMIDIOUT &hMidiOut)
{
	DWORD result;
	COORD coord;
	int delay = 100, key;
	static int index=27;
	const char *names[128] = {
		"未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知",
		"未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知",
		"未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知",								// 0~26
		"Hi Q (激光枪声)",				"Synth Slap (合成拍音)",			"Scratch 2 (高音刷音)",			// 27, 28, 29
		"Scratch 1 (低音刷音)",			"Sticks (鼓槌)",					"Square Click (敲方板)",		// 30, 31, 32
		"Metronome Click (节拍器)",		"Metronome Bell (节拍器重音)",		"Acoustic Bass Drum (低音大鼓)",// 33, 34, 35
		"Bass Drum 1 (高音大鼓)",		"Side Stick (鼓边)",				"Acoustic Snare (小鼓)",		// 36, 37, 38
		"Hand Clap (拍手声)",			"Electric Snare (电子小鼓)",		"Low Floor Tom (低音落地嗵鼓)",	// 39, 40, 41
		"Closed Hi-Hat (合音踩镲)",		"High Floor Tom (高音落地嗵鼓)",	"Pedal Hi-Hat (踏音踩镲)",		// 42, 43, 44
		"Low Tom (低音嗵鼓)",			"Open Hi-Hat (开音踩镲)",			"Low-Mid Tom (中低音嗵鼓)",		// 45, 46, 47
		"Hi-Mid Tom (中高音嗵鼓)",		"Crash Cymbal 1 (低砸音镲)",		"High Tom (高音嗵鼓)",			// 48, 49, 50
		"Ride Cymbal 1 (低浮音镲)",		"Chinese Cymbal (中国镲)",			"Ride Bell (浮音镲碗)",			// 51, 52, 53
		"Tambourine (铃鼓)",			"Splash Cymbal (溅音镲)",			"Cowbell (牛铃)",				// 54, 55, 56
		"Crash Cymbal 2 (高砸音镲)",	"Vibraslap (颤音叉)",				"Ride Cymbal 2 (高浮音镲)",		// 57, 58, 59
		"Hi Bongo (高音邦戈)",			"Low Bongo (低音邦戈)",				"Mute Hi Conga (弱音康加)",		// 60, 61, 62
		"Open Hi Conga (高音康加)",		"Low Conga (低音康加)",				"High Timbale (高音铜鼓)",		// 63, 64, 65
		"Low Timbale (低音铜鼓)",		"High Agogo (高音拉丁打铃)",		"Low Agogo (低音拉丁打铃)",		// 66, 67, 68
		"Cabasa (沙锤)",				"Maracas (响葫芦)",					"Short Whistle (短哨)",			// 69, 70, 71
		"Long Whistle (长哨)",			"Short Guiro (短锯琴)",				"Long Guiro (长锯琴)",			// 72, 73, 74
		"Claves (击杆)",				"Hi Wood Block (高音木块)",			"Low Wood Block (低音木块)",	// 75, 76, 77
		"Mute Cuica (弱音吉加)",		"Open Cuica (开音吉加)",			"Mute Triangle (弱音三角铁)",	// 78, 79, 80
		"Open Triangle (开音三角铁)",	"Shaker (沙锤（比69沙锤高）)",		"Jingle Bell (铃铛)",			// 81, 82, 83
		"Bell Tree (铃树)",				"Castanets (响板)",					"Mute Surdo (弱音瑟多)",		// 84, 85, 86
		"Open Surdo (开音瑟多)",		"Applause2 (欢呼2(Roland SC-88Pro))",								// 87, 88
		"未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知",						// 89~98
		"未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知",						// 99~108
		"未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知",						// 109~118
		"未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知", "未知"								// 119~127
	};
	char prompt[4][61] = {
		"                          [Up] -10                          ",
		"-1 [Left]                                         [Right] +1",
		"                         [Down] +10                         ",
		"                       【Space 播放】                       "
	};
	char str[40];
	while(true)
	{
		coord.X = 10;
		coord.Y = 15;
		for(int i=0; i<4; i++)
		{
			SetConsoleCursorPosition(hStdOut, coord);
			SetConsoleTextAttribute(hStdOut, 7);
			WriteConsole(hStdOut, prompt[i], strlen(prompt[i]), &result, NULL);
			coord.Y += 2;
		}
		sprintf(str, "%3d %s", index, names[index]);
		coord.Y = 17;
		coord.X = 40-strlen(str)/2;
		SetConsoleCursorPosition(hStdOut, coord);
		SetConsoleTextAttribute(hStdOut, 9<<4 | 15);
		WriteConsole(hStdOut, str, strlen(str), &result, NULL);
		
		key = getch();
		switch(key)
		{
		case ' ':	MidiOutMessage(hMidiOut, 0x90, 9, index, 127);
					Sleep(delay);
					break;
		case 224:
			{
				switch(getch())
				{
				case 72:	index -= 10;	break;	// Up
				case 80:	index += 10;	break;	// Down
				case 75:	index--;		break;	// Left
				case 77:	index++;		break;	// Rignt
				case 79:	coord.X = 0;
							coord.Y = 16;
							SetConsoleCursorPosition(hStdOut, coord);
							SetConsoleTextAttribute(hStdOut, 7);
							return;					// End
				}
			}
			if(index < 0) index = 0;
			if(index > 127) index = 127;
		}
	}
}
