//	main.cpp
#include "MIDIexample.h"
#include <iostream>
#include <conio.h>				// ��Ϊgetche����
using namespace std;

int main()
{
	int choice;
	HMIDIOUT hMidiOut;							// ��������������
	midiOutOpen(&hMidiOut, MIDIMAPPER, 0, 0, 0);// ��MIDI�����豸
	
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
	midiOutClose(hMidiOut);						// �ر�MIDI�����豸
	return 0;
}
