#include "pch.h"
#include "num.h"
#define ABS(x,y) (((x)>(y))?((x)-(y)):((y)-(x)))
Number::Number()
{

}
Number::Number(const Number& num)
{
	number = num.number;
}
Number::Number(const Number* const num)
{
	number = num->number;
}
Number::Number(const vector<char>& vec)
{
	number = vec;
}
Number::Number(const string& str)
{
	if (str.find_first_not_of("0123456789.Ee") != string::npos)
		throw string("error cin number");
	string::size_type st_found_e = str.find('E') != string::npos ? str.find('E') : str.find('e');
	if (st_found_e != string::npos && (str.find('E', st_found_e + 1) != string::npos || str.find('e', st_found_e + 1) != string::npos))
		throw string("error cin number");
	string str_dom(str, st_found_e, str.size() - st_found_e);
	string::size_type st_found_point = str.find('.');
	if (st_found_point != string::npos && (str.find('.', st_found_point + 1) != string::npos || st_found_point >= st_found_e))
		throw string("error cin number");
	if (st_found_point == 0)
		number.push_back(0);
	string::size_type stop = st_found_e != string::npos ? (st_found_point != string::npos ? st_found_point : st_found_e) : str.size();
	string::size_type st_i = 0;
	for (; st_i < stop; ++st_i)
		number.push_back(str[st_i]);
	//++st_i;
}
Number::~Number()
{

}

istream & operator>>(istream& in, Number& num)
{
	string str;//str_dom: Decimal order of magnitude
	in >> str;
	//str.push_back('\0');
	if (str.find_first_not_of("0123456789.Ee") != string::npos )
		throw string("error cin number");
	string::size_type st_found_e = str.find('E') != string::npos ? str.find('E') : str.find('e');
	if (st_found_e!=string::npos && (str.find('E', st_found_e+1) != string::npos || str.find('e', st_found_e+1) != string::npos))
		throw string("error cin number");
	string::size_type st_found_point = str.find('.');
	if (st_found_point != string::npos && (str.find('.', st_found_point + 1) != string::npos || st_found_point >= st_found_e))
		throw string("error cin number");
//	string str_dom(str, st_found_e, str.size()-st_found_e);
//	Number dom(str_dom);
	if (st_found_point == 0)
		num.number.push_back(0);
	string::size_type stop = st_found_e != string::npos ? (st_found_point != string::npos ? st_found_point : st_found_e) : str.size();
	string::size_type st_i = 0;
	for (; st_i<stop; ++st_i)
		num.number.push_back(str[st_i]);
	++st_i;

	return in;
}
ostream & operator<<(ostream& out, Number& num)
{
	for (vector<char>::size_type i = 0; i < num.number.size(); ++i)
		out << num.number[i];
	return out;
}
Number Number::operator+(const Number& num)
{
	vector<char> ret;
	vector<char>::size_type size_diff = ABS(number.size(), num.number.size());
	Number num_big(number.size() - num.number.size() > 0 ? this : num), num_sma(number.size() - num.number.size() > 0 ? num : this);

	vector<char>::size_type i = 0;
	char buf = num_big.number[i] + ((i >= size_diff) ? num_sma.number[i - size_diff] : '0') - '0' - '0';
	if (buf > 9)
		ret.push_back('1');
	else if (buf == 9)
		ret.push_back('0');
	ret.push_back(buf % 10 + '0');
	++i;

	for (; i < number.size() || i < num.number.size(); ++i)
	{
		buf = num_big.number[i] + ((i >= size_diff) ? num_sma.number[i - size_diff] : '0') - '0' - '0';
		if (buf > 9)
			carry(ret);
		ret.push_back(buf % 10 + '0');
	}
	if (ret.front() == '0')
		ret.erase(ret.begin());
	return Number(ret);
 }

vector<char> Number::carry(vector<char>& vec)
{
	for (vector<char>::size_type i = vec.size()-1; i >= 0; --i)
	{
		if (vec.at(i) == '9')
			vec[i] = '0';
		else
		{
			++vec[i];
			break;
		}
	}
	return vec;
}