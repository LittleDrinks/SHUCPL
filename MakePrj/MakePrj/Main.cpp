// Main.cpp
#include <iostream>
#include <conio.h>		// for getch()
#include "MakePrj.h"
using namespace std;

void Help()
{
	cout << "===============================================================================" << endl;
	cout << "    ���ݵ�ǰ�ļ���(��Ŀ¼)�е�C/C++Դ�����ļ�����������MinGW Developer Studio��\n"
		 << "Code::Blocks��Dev-C++���ɿ�������(IDE)�µĿ���̨Ӧ�ó���(Console Application)��\n"
		 << "�����ļ���" << endl;
	cout << "����ʾ���뽫����������������ɵĿ�ִ���ļ�(MakePrj.exe)������D�̸�Ŀ¼(D:\\)�С�\n"
		 << "�����ϵͳ�ĸ�������·��PATH���Ѿ����õ�ĳ���ļ����У��Է����������С�\n" << endl;
	cout << "��ʹ�÷�����" << endl;
	cout << "  1. ���ȴ���һ���ļ��У��ļ���������Ϊ�����ļ�������" << endl;
	cout << "  2. �ڸ��ļ������á����±�����дһ���������ļ����ļ����ݽ�һ��(��D:\\MakePrj)��"<< endl;
	cout << "     �����˳��󣬽��ļ�������չ���ĳ�bat����ʾ�������ļ�����"<< endl;
	cout << "  3. ���˫���������ļ����򽫴���3��IDE�Ŀ���̨Ӧ�ó��򹤳��ļ���\n" << endl;
	cout << "  4. ���б�����ʱ�����в����к���ĸm��c��d�ֱ��ʾ����MinGW Developer Studio��\n"
		 << "     Code::Blocks��Dev-C++���ɿ��������Ĺ����ļ���\n"
		 << "     ���磺D:\\MakePrj md����D:\\MakePrj m d ����ʾ������Ӧ������IDE�Ĺ����ļ���\n" << endl;
	cout << "��˵����" << endl;
	cout << "    ����ǰ�ļ�������C/C++Դ���룬�򱾳��򽫴���2��Դ�����ļ���1��ͷ�ļ���" << endl;
	cout << "===============================================================================" << endl;
}

int Pos(char c, const char *str)
{
	for(int i=0; str[i]!='\0'; i++)
		if(c==str[i])
			return i;
	return -1;
}

int main(int argc, char *argv[])
{
	char curdir[200];
	int flag = (argc==1)? 7 : 0;

	Help();
	GetCurDir(curdir);
	
	for(int i=1; i<argc; i++)
	{
		strlwr(argv[i]);
		if(Pos('m', argv[i])>=0) flag |= 1;
		if(Pos('c', argv[i])>=0) flag |= 2;
		if(Pos('d', argv[i])>=0) flag |= 4;
	}
	if(flag & 1) CreateMDSP(curdir);
	if(flag & 2) CreateCBP(curdir);
	if(flag & 4) CreateDEV(curdir);
	if(flag==0) cout << "δ�����κι����ļ���" << endl;

	cout << "��������˳�..." << endl;
	getch();
	return 0;
}
