	MIDIexample.cpp
#include "MIDIexample.h"
#include <iostream>
#include <ctime>
using namespace std;

double gettime(int restart)					// ������Ĭ��ֵ�������ʾ���¼�ʱ
{											// �����ۼƼ�ʱ
	const double c = 1.0/CLOCKS_PER_SEC;
	static clock_t t = clock();				// ��̬�ֲ���������һ�ε���ʱ��ȷ����ʱ���
	if(restart) t = clock();				// ����ʵ�ξ����Ƿ�����ȷ����ʱ���
	return c*(clock()-t);					// ����һ��ʱ�㵽������������ʱ��
}

DWORD MidiOutMessage(HMIDIOUT hMidi, int iStatus, int iChannel, int iFlip, int iVolume)
{
	DWORD dwMessage = (iVolume << 16) | (iFlip << 8) | iStatus         | iChannel;
					//      ����      |     ����     | ״̬�ֽ�(��4λ) | ͨ��(��4λ)
	return midiOutShortMsg(hMidi, dwMessage);
}

void HelloWorld(HMIDIOUT hMidiOut)
{
	MidiOutMessage(hMidiOut, 0xC0, 0, 0, 0);	// ����ͨ��0����ɫΪ����

	MidiOutMessage(hMidiOut, 0x90, 0, 60, 112);	// ��������C(С��1��c1)������112(ff)
	Sleep(500);
	MidiOutMessage(hMidiOut, 0x80, 0, 60, 127);	// ��������C(С��1��c1)���ٶ�127��������

	MidiOutMessage(hMidiOut, 0x90, 0, 64, 80);	// ����e1������80(mf)
	Sleep(500);
	MidiOutMessage(hMidiOut, 0x80, 0, 64, 127);	// ����e1

	MidiOutMessage(hMidiOut, 0x90, 0, 67, 96);	// ����g1������96(f)
	Sleep(500);
	MidiOutMessage(hMidiOut, 0x80, 0, 67, 127);	// ����g1

	MidiOutMessage(hMidiOut, 0x90, 0, 60, 80);	// ���ң�����80(mf)
	MidiOutMessage(hMidiOut, 0x90, 0, 64, 80);
	MidiOutMessage(hMidiOut, 0x90, 0, 67, 80);
	MidiOutMessage(hMidiOut, 0x90, 0, 72, 80);
	Sleep(2500);
	MidiOutMessage(hMidiOut, 0x80, 0, 60, 127);	// ����
	MidiOutMessage(hMidiOut, 0x80, 0, 64, 127);
	MidiOutMessage(hMidiOut, 0x80, 0, 67, 127);
	MidiOutMessage(hMidiOut, 0x80, 0, 72, 127);
}

/*	������Ĳ��Ժ�����ȡ������򵥵Ĵ���ʽ�����ڵ�������Ҫ�У�
1. ʹ��Sleep��������ʱ��ͬ���Ϻܲ���ȷ���������˽ϴ���ۻ�����������dt��dt1��Ŀ�����뾡������һЩ����
   ���Ľ������� �ɿ��Ǹ��ö�ý���ʱ������ȷ��1���롣
2. �����ı�ﲻֱ�ۣ�����¼�벻���㡣���������������ٶȹ̶�������
   ���Ľ������� �ɿ������һ�׷���ϵͳֱ�۱�����ף�������ʱ�������ȵȣ����������ļ������ı��ļ�����
				Ȼ���ȡ�ļ�����������ת����MIDI�������Ϣ����󲥷š�
				�����о�mid�ļ��ĸ�ʽ��ֱ������mid�ļ���������Ƶ���������š�
*/
void Test(HMIDIOUT hMidiOut, int flag)			// �������װ������裨���ٰ���ǰ2С�ڣ�
{
	double t=1000;								// �ٶȣ�1�ĵ�ʱֵ��1000����=1�룩��ÿ����60��
	char mf=80;									// ���ȣ�mf��ǿ
	Music PianoR[] = { {77,mf-10,0,0}, {81,mf-10,0}, {84,mf-10,0}, {89,mf-10,t/2},			// ���ٰ��ࣨ���ֲ��֣�
					   {77,mf   ,0},   {81,mf   ,0}, {84,mf   ,0}, {89,mf   ,t},			// �з����ı�С���е�ǿ��
					   {79,mf-10,0},   {91,mf-10,t/2},
					   {77,mf-10,0},   {82,mf-10,0}, {86,mf-10,0}, {89,mf-10,t/4},
					   {74,mf- 5,0},   {86,mf- 5,t/2},
					   {72,mf-10,0},   {84,mf-10,t/4},
					   {70,mf-10,0},   {82,mf-10,t/2},
					   {69,mf-10,0},   {81,mf-10,t/2},
					   {72,mf   ,0}, {77,mf   ,0}, {81,mf,0}, {84,mf,t/2},					// ��2С��
					   {72,mf   ,0}, {77,mf   ,0}, {81,mf,0}, {84,mf,t/4},
					   {74,mf   ,0}, {86,mf   ,t/4},
					   {72,mf-10,0}, {84,mf-10,t/2},
					   {70,mf-10,0}, {82,mf-10,t/4},
					   {69,mf-10,0}, {81,mf-10,t/4},
					   {67,mf- 5,0}, {72,mf- 5,0}, {76,mf-5,0}, {79,mf-2,2*t} };
	Music PianoL[] = { {41,mf   ,t/4,0}, {48,mf   ,t/4}, {57,mf   ,t/4}, {60,mf   ,t/4},	// ���ٰ��ࣨ���ֲ��֣�
					   {69,mf-10,t/4},   {65,mf-10,t/4}, {60,mf-10,t/4}, {57,mf-10,t/4},
					   {46,mf- 5,t/4},   {53,mf- 5,t/4}, {58,mf- 5,t/4}, {62,mf- 5,t/4},
					   {65,mf-10,t/4},   {62,mf-10,t/4}, {58,mf-10,t/4}, {53,mf-10,t/4},
					   {41,mf   ,t/4},   {48,mf   ,t/4}, {57,mf   ,t/4}, {60,mf   ,t/4},	// ��2С��
					   {69,mf-10,t/4},   {65,mf-10,t/4}, {60,mf-10,t/4}, {57,mf-10,t/4},
					   {48,mf- 5,t/4},   {55,mf- 5,t/4}, {60,mf- 5,t/4}, {64,mf- 5,t/4},
					   {67,mf-10,t/4},   {64,mf-10,t/4}, {60,mf-10,t/4}, {55,mf-10,t/4} };
	Music *p[] = {PianoR, PianoL};															// ָ�����飬�������������������
	int n = sizeof(p)/sizeof(*p), i, j, i0=0, i1=n, dt=250, dt1=dt-18;
	int len[] = {sizeof(PianoR)/sizeof(*PianoR), sizeof(PianoL)/sizeof(*PianoL)};
	double totalTime = 0;
	int k[]={0,0}, beg[]={0,0}, end[]={0,0}, channel[]={0,1};
	
	if(flag==1)												// �����Ÿ��ٰ�������ֲ���
		i1 = i0+1;
	else if(flag==2)										// �����Ÿ��ٰ�������ֲ���
		i0 = 1;
	
	for(i=i0; i<i1; i++)									// ������ʱ��
	{
		for(j=0; j<len[i]; j++)
			p[i][j].time = p[i][j-1].time + p[i][j].deltaTime;
		if(p[i][j-1].time > totalTime)
			totalTime = p[i][j-1].time;
	}

	cout << "\n\t\t�������װ�������(���ٰ���ǰ2С��)" << endl;
	for(i=i0; i<i1; i++)									// ���Ÿ�ͨ���ĵ�һ������
	{
		MidiOutMessage(hMidiOut, 0xC0, channel[i], 0, 0);	// ����ͨ��channel[i]����ɫΪ����
	}
	gettime(1);
	for(double time=0; time < totalTime; time+=dt)			// ���ڱ������ԣ���С��deltaΪt/4=250���ʱ�ѭ������Ϊ50
	{
		for(i=i0; i<i1; i++)
		{
			if(p[i][k[i]].time < time)
			{
				for(j=beg[i]; j<end[i]; j++)							// �����������Ǻ���
					MidiOutMessage(hMidiOut, 0x80, channel[i], p[i][j].note, 127);
				beg[i] = k[i];
				cout << '[' << i << ']';
				for( ; k[i]<len[i] && p[i][k[i]].time < time; k[i]++)	// �����������Ǻ���
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
		for(j=beg[i]; j<end[i]; j++)									// �����������Ǻ���
			MidiOutMessage(hMidiOut, 0x80, channel[i], p[i][j].note, 127);
	}
	cout << "��ʱ��: " << gettime() << "��" << endl;
}
