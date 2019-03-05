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

	//---------allow multiple dom--------

	//if (st_found_e!=string::npos && (str.find('E', st_found_e+1) != string::npos || str.find('e', st_found_e+1) != string::npos))
	//	throw string("error cin number");
	string::size_type st_found_point = str.find('.') > st_found_e ? string::npos : str.find('.');
	//if (st_found_point != string::npos && (str.find('.', st_found_point + 1) != string::npos || st_found_point >= st_found_e))
	//	throw string("error cin number");

//	string str_dom(str, st_found_e, str.size()-st_found_e);//str_dom: Decimal order of magnitude
//	Number dom(str_dom);
	if (st_found_point == 0)
		number.push_back('0');
	
	number.push_back(str[0]);
	if (st_found_point != string::npos&& st_found_point > 1)
		number.push_back('.');
	string::size_type stop = st_found_e != string::npos ? st_found_e : str.size();
	string::size_type st_i = 1;
	for (; (st_i == st_found_point&&st_found_point>1 ? ++st_i : st_i) < stop; ++st_i)
		number.push_back(str[st_i]);
	if (st_found_e != string::npos)
		dom = new Number(string(str, st_found_e+1,str.size() - st_found_e-1));

	*dom = *dom+ ((st_found_point > 1) ? st_found_point - 1 : 0);
}

Number::~Number()
{
	if(dom)
		delete dom;
}

istream & operator>>(istream& in, Number& num)
{
	string str;
	in >> str;
	//str.push_back('\0');
	if (str.find_first_not_of("0123456789.Ee") != string::npos )
		throw string("error cin number");
	string::size_type st_found_e = str.find('E') != string::npos ? str.find('E') : str.find('e');

	//---------allow multiple dom--------

	//if (st_found_e!=string::npos && (str.find('E', st_found_e+1) != string::npos || str.find('e', st_found_e+1) != string::npos))
	//	throw string("error cin number");
	string::size_type st_found_point = str.find('.')>st_found_e?string::npos:str.find('.');
	//if (st_found_point != string::npos && (str.find('.', st_found_point + 1) != string::npos || st_found_point >= st_found_e))
	//	throw string("error cin number");

//	string str_dom(str, st_found_e, str.size()-st_found_e);//str_dom: Decimal order of magnitude
//	Number dom(str_dom);
	if (st_found_point == 0)
		num.number.push_back('0');

	num.number.push_back(str[0]);
	if (st_found_point != string::npos&& st_found_point > 1)
		num.number.push_back('.');
	string::size_type stop = st_found_e != string::npos ? st_found_e : str.size();
	string::size_type st_i = 1;
	for (; (st_i == st_found_point && st_found_point > 1 ? ++st_i : st_i) < stop; ++st_i)
		num.number.push_back(str[st_i]);
	if (st_found_e != string::npos)
		num.dom = new Number(string(str, st_found_e + 1, str.size() - st_found_e - 1));

	*num.dom = *num.dom + ((st_found_point > 1) ? st_found_point - 1 : 0);

	return in;
}
ostream & operator<<(ostream& out, Number& num)
{
	for (vector<char>::size_type i = 0; i < num.number.size(); ++i)
		out << num.number[i];
	if(num.dom)
		out << "*10^(" <<* num.dom << ")";//out << "E^(" << *num.dom << ")";
	
	return out;
}
Number Number::operator+(const Number& num)
{
	vector<char> ret;

	vector<char>::size_type aline_this = 0, aline_num = 0;
	for (; aline_this < this->number.size() && this->number[aline_this]!='.'; ++aline_this);
	for (; aline_num < num.number.size() && num.number[aline_num]!='.'; ++aline_num);
	vector<char>::size_type size_diff = ABS(aline_this, aline_num);
	//Number num_big(aline_this >= aline_num ? this : num), num_sma(aline_this >= aline_num ? num : this);
	const Number& num_big = (aline_this >= aline_num) ? this : num, num_sma=(aline_this >= aline_num) ? num : this;
	
	char buf = num_big.number[0] + (size_diff) ? 0 : (num_sma.number[0] - '0') - '0';
	if (buf > 9)
		ret.push_back('1');
	else if (buf == 9)
		ret.push_back('0');
	ret.push_back(buf % 10 + '0');

	vector<char>::size_type i = 1;
	for (; i < (aline_this>aline_num ? aline_this : aline_num); ++i)
	{
		buf = num_big.number[i] + ((i >= size_diff) ? num_sma.number[i - size_diff] - '0' : 0) - '0';
		if (buf > 9)
			carry(ret);
		ret.push_back(buf % 10 + '0');
	}

	if (aline_this != this->number.size() || aline_num != num.number.size())
	{
		ret.push_back('.');
		++i;
		for (; i < num_big.number.size() || i < num_sma.number.size(); ++i)
		{
			buf = num_big.number[i] + ((i <= num_sma.number.size()) ? num_sma.number[i - size_diff] : '0') - '0' - '0';
			if (buf > 9)
				carry(ret);
			ret.push_back(buf % 10 + '0');
		}
	}
	
	if (ret.front() == '0')
		ret.erase(ret.begin());
	return Number(ret);
 }

vector<char> Number::carry(vector<char>& vec)
{
	for (vector<char>::size_type i = vec.size()-1; i >= 0; --i)
	{
		if(vec[i]=='.')
			continue;
		if (vec[i] == '9')
			vec[i] = '0';
		else
		{
			++vec[i];
			break;
		}
	}
	return vec;
}

vector<char> Number::decom(vector<char>& vec)
{
	for (vector<char>::size_type i = vec.size()-1; i >= 0; --i)
	{
		if(vec[i]=='.')
			continue;
		if (vec[i] == '0')
			vec[i] = '9';
		else
		{
			--vec[i];
			break;
		}
	}
	return vec;
}
