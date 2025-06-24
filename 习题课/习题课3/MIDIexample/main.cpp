//	main.cpp
#include "MIDIexample.h"
#include <iostream>
#include <conio.h>				// 因为getche函数
using namespace std;

int main()
{
	int choice;
	HMIDIOUT hMidiOut;							// 定义变量（句柄）
	midiOutOpen(&hMidiOut, MIDIMAPPER, 0, 0, 0);// 打开MIDI播放设备
	
	HelloWorld(hMidiOut);
	
	while(true)
	{
		cout << "\n1 --- Right\n2 --- Left\n3 --- Both\n0 --- exit : ";
		choice = getche();
		cout << endl;
		if(choice<='0') break;
		switch(choice)
		{
		case '1':	Test(hMidiOut, 1);	break;
		case '2': 	Test(hMidiOut, 2);	break;
		default:	Test(hMidiOut, 3);	break;
		}
	}
	midiOutClose(hMidiOut);						// 关闭MIDI播放设备
	return 0;
}
