#pragma once
#include<vector>
#include <iostream>
#include<string>
using namespace std;
class Number
{
public:
	vector<char> number;
public:
	vector<char> carry(vector<char>&);
	//union 
	//{
	//	int INT;
	//	Number NUMBER;
	//}dom;
public:
	friend istream& operator>>(istream&, Number&);
	friend ostream& operator<<(ostream&, Number&);
	Number operator+(const Number&);
	Number operator-(const Number&);
	Number operator*(const Number&);
	Number operator/(const Number&);

	Number operator+(int);

	//friend Number stringTonum(const string&);
	Number();
	Number(const Number&);
	Number(const Number* const);
	Number(const vector<char>&);
	Number(const string &);
	~Number();
};