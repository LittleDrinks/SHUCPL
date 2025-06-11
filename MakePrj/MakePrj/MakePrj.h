// MakePrj.h
#ifndef MAKEPRJ_H
#define MAKEPRJ_H

#include <string>
#include <vector>
using namespace std;

int GetFiles(string path, string ext, vector<string> &filenames);	// ��ȡָ��·����ָ�����ͣ���չ�����������ļ���
void GetCurDir(char *curdir);	// ���ص�ǰ��Ŀ¼���ơ����⣬����ǰ��Ŀ¼����Դ���룬�򴴽�3���������ļ�
int CreateMDSP(char *prjName);	// ���ݵ�ǰ��Ŀ¼�е�Դ�����ļ�������MinGW Developer Studio����̨Ӧ�ó���Win32 Console Application�������ļ�
int CreateCBP(char *prjName);	// ���ݵ�ǰ��Ŀ¼�е�Դ�����ļ�������Code::Blocks����̨Ӧ�ó���Console Application�������ļ�
int CreateDEV(char *prjName);	// ���ݵ�ǰ��Ŀ¼�е�Դ�����ļ�������Dev C++����̨Ӧ�ó���Console Application�������ļ�

#endif
