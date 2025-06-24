/*	MIDIexample.h											*
 *  ע: ����Project/Settings.../Link/Libraries:��������		*
 *		C:\MinGWStudio\MinGW\lib\libwinmm.a					*
 *      Debug �� Release ����Ҫ����                         */
#ifndef MIDI_EXAMPLE_H
#define MIDI_EXAMPLE_H
#include <windows.h>

double gettime(int restart=0);
DWORD MidiOutMessage(HMIDIOUT hMidi, int iStatus, int iChannel, int iFlip, int iVolume);

struct Music
{
	char note, volume;
	double deltaTime, time;
};

void Test(HMIDIOUT hMidiOut, int flag=3);
void HelloWorld(HMIDIOUT hMidiOut);
#endif
