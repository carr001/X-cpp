//#include "hppDemo.hpp"
#include <iostream>
using namespace std;

int main1(void) {
	int data = 20;
	//func(data);
	system("pause");
	return 0;
}

//�ظ�ģ��ʵ��==>name mangling
void  caller1();
void caller2();
int main(void) {
	caller1();
	caller2();
	system("pause");
	return 0;
}