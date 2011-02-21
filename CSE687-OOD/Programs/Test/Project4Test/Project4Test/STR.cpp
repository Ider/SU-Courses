#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include "str.h"
using namespace std;


void DebugWrite(char * content)
{
	if (true)
	{
		cout << "\n -------" << content << "-------" << endl;
	}
}

str::str(int n) : array(new char[n]), max(n), len(0)
{
	DebugWrite("Default Constructor is called");
	array[0] = '\0';
}

str::str(const str& s) : array(new char[s.max]), max(s.max), len(s.len)
{
	DebugWrite("Copy Constructor is called");

	int i;
	for(i = 0; i<=len; i++)
	{
		array[i] = s.array[i];
	}
}

str::str(const char *s): len(static_cast<int>(strlen(s)))
{
	DebugWrite("Promotion Constructor is called");
	max = len + 1;
	array = new char[len+1];
	//int i;
	for( int i = 0; i<=len; i++)
	{
		array[i] = s[i];
	}
}

str:: ~str()
{
	DebugWrite("Destructor is called");

	delete [] array;
	max = len = 0;
}

str& str::operator=(const str& s)
{
	DebugWrite("Assignment Operator is called");
	if(this == &s) return *this;
	if(max < s.len+1)
	{
		delete [] array;
		array = new char[max = s.max + 10];
	}

	for(int i = 0; i<=s.len; i++)
	{
		array[i] = s.array[i];
	}

	return *this;
}


// char& str::operator[](int n)
// {
// 	//DebugWrite("Index Operator is called");
// 	if(n<0 || len<=n)
// 		throw invalid_argument("index out of bounds in operator[]");
// 	return array[n];
// }

char& str::operator[](int n) const
{
	//DebugWrite("Const Index Operator is called");
	if(n<0 || len<=0)
		throw invalid_argument("index out of bounds in operator[]");
	return array[n];
}

str& str::operator+=(char ch) {

	DebugWrite("Append character to string");

	if(len < max-1) {
		array[len] = ch;
		array[len+1] = '\0';
		len++;
	}
	else {
		max *= 2;   // multiply by 2
		char *temp = new char[max];
		int i;
		for(i=0; i<len; i++)
			temp[i] = array[i];
		temp[len] = ch;
		temp[len+1] = '\0';
		len++;
		delete [] array;
		array = temp;
	}
	return *this;
}

str& str::operator+=(const str& s) {

	DebugWrite("Append string to string");

	if(len < max-s.size()) {
		int i;
		for(i=0; i<=s.len; i++)
			array[len+i] = s.array[i];
		len += s.size();
	}
	else {
		max += max + s.size();
		char *temp = new char[max];
		for(int i=0; i<len; i++)
			temp[i] = array[i];
		for(int i=0; i<s.size(); i++)
			temp[len+i] = s.array[i];
		temp[len+s.size()] = '\0';
		len += s.size();
		delete [] array;
		array = temp;
	}
	return *this;
}

str str::operator+(const str& s)
{
	DebugWrite("addition operator");
	str temp = *this; //call copy constructor
	temp += s;
	return temp;
}


ostream& operator<<(ostream& out, const str& s)
{
	DebugWrite("insertion operator");

	int i;
	for(i=0; i<s.size(); i++)
		out << s[i];
	return out;
}


istream& operator>>(istream& in, str& s)
{
	DebugWrite("extraction operator");

	char ch;
	s.flush();
	in >> ch;
	while((ch != '\n') && in.good()) 
	{
		s += ch;
		in.get(ch);
	}
	return in;
}