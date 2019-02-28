#pragma once
#include<vector>
using namespace std;
class num
{
public:
	vector<char> number;
	friend istream& operator>>(istream& , num&);
	friend ostream& operator<<(ostream&, num&);
	num operator+(const num&);
	num operator-(const num&);
	num operator*(const num&);
	num operator/(const num&);

	num();
	~num();
};

