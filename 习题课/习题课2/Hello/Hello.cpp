// Hello.cpp
#include <iostream>
using namespace std;

int main()
{
	char name[20];
	int age;

	cout << "What's your name?" << endl;	// 此处单引号可不用转义字符
	cin.getline(name, 20);

	cerr << "How old are you?" << endl;
	cin >> age;

	clog << "姓名：" << name << "，年龄："
		 << age << "。你好！" << endl;

	return 0;
}
