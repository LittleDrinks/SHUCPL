// MakePrj.h
#ifndef MAKEPRJ_H
#define MAKEPRJ_H

#include <string>
#include <vector>
using namespace std;

int GetFiles(string path, string ext, vector<string> &filenames);	// 获取指定路径中指定类型（扩展名）的所有文件名
void GetCurDir(char *curdir);	// 返回当前子目录名称。另外，若当前子目录中无源代码，则创建3个基本的文件
int CreateMDSP(char *prjName);	// 根据当前子目录中的源代码文件，创建MinGW Developer Studio控制台应用程序（Win32 Console Application）工程文件
int CreateCBP(char *prjName);	// 根据当前子目录中的源代码文件，创建Code::Blocks控制台应用程序（Console Application）工程文件
int CreateDEV(char *prjName);	// 根据当前子目录中的源代码文件，创建Dev C++控制台应用程序（Console Application）工程文件

#endif
