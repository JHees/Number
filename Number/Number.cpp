// Number.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include "pch.h"
#include <iostream>
#include<vector>

#include"num.h"
using namespace std;

//class chatoint
//{
//public:
//	operator int()
//	{
//		return ch - '0';
//	};
//private:
//	char ch;
//};

int main()
{
	Number num1("12.5E8");
	cout <<num1<<endl;
	cout << string(".").size() << endl;
	system("pause");
}

