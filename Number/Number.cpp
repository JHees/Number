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
	while (1)
	{
		Number num1,num2;
		cin >> num1>>num2;
		Number num3(num1 + num2);
		cout <<num3<<endl;
	}
	system("pause");
}

