// KbMIDI.h		键盘弹奏MIDI
//注：请在Project/Settings.../Link/Libraries:下面输入C:\MinGWStudio\MinGW\lib\libwinmm.a
#ifndef MY_KB_MIDI_H
#define MY_KB_MIDI_H
#include <windows.h>

DWORD MidiOutMessage(HMIDIOUT hMidi, int iStatus, int iChannel, int iFlip, int iVolume);
extern char Notes[88][4];
int Do2Si(int a[8], const char *notes="c1");
void kbMIDI(char *notes="c1");
void kbMIDICh9(HANDLE &hStdOut, HMIDIOUT &hMidiOut);

#endif
