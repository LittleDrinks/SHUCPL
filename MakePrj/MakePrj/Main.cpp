// Main.cpp
#include <iostream>
#include <conio.h>		// for getch()
#include "MakePrj.h"
using namespace std;

void Help()
{
	cout << "===============================================================================" << endl;
	cout << "    根据当前文件夹(子目录)中的C/C++源代码文件，创建用于MinGW Developer Studio、\n"
		 << "Code::Blocks和Dev-C++集成开发环境(IDE)下的控制台应用程序(Console Application)的\n"
		 << "工程文件。" << endl;
	cout << "【提示】请将本程序编译连接生成的可执行文件(MakePrj.exe)拷贝至D盘根目录(D:\\)中。\n"
		 << "或操作系统的辅助检索路径PATH中已经设置的某个文件夹中，以方便启动运行。\n" << endl;
	cout << "【使用方法】" << endl;
	cout << "  1. 事先创建一个文件夹（文件夹名将作为工程文件名）；" << endl;
	cout << "  2. 在该文件夹下用“记事本”编写一个批处理文件，文件内容仅一行(如D:\\MakePrj)，"<< endl;
	cout << "     存盘退出后，将文件名的扩展名改成bat（表示批处理文件）；"<< endl;
	cout << "  3. 鼠标双击批处理文件，则将创建3个IDE的控制台应用程序工程文件。\n" << endl;
	cout << "  4. 运行本程序时命令行参数中含字母m、c或d分别表示创建MinGW Developer Studio、\n"
		 << "     Code::Blocks或Dev-C++集成开发环境的工程文件。\n"
		 << "     例如：D:\\MakePrj md，或D:\\MakePrj m d 均表示创建对应的两种IDE的工程文件。\n" << endl;
	cout << "【说明】" << endl;
	cout << "    若当前文件夹中无C/C++源代码，则本程序将创建2个源程序文件、1个头文件。" << endl;
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
	if(flag==0) cout << "未创建任何工程文件。" << endl;

	cout << "按任意键退出..." << endl;
	getch();
	return 0;
}
