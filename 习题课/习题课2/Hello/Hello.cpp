// Hello.cpp
#include <iostream>
using namespace std;

int main()
{
	char name[20];
	int age;

	cout << "What's your name?" << endl;	// �˴������ſɲ���ת���ַ�
	cin.getline(name, 20);

	cerr << "How old are you?" << endl;
	cin >> age;

	clog << "������" << name << "�����䣺"
		 << age << "����ã�" << endl;

	return 0;
}
