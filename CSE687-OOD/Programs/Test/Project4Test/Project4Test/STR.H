#ifndef STR_H
#define STR_H

#include <iostream>

class str
{
private:
	char *array;
	int len, max;

public:
	str(int n=10);
	str(const str& s);
	~str();
	//explicit 
		str(const char* s);
	str& operator=(const str& s);
	//char& operator[](int n);
	char& operator[](int n) const;
	str& operator+=(char ch);
	str& operator+=(const str& s);
	str operator+(const str& s);
	operator const char* ();
	int size() const;
	void flush();

};


std::ostream& operator<<(std::ostream& out, const str &s);

std::istream& operator>>(std::istream& in, str &s);

inline int str::size() const {return len;}

inline void str::flush() {len = 0;}

inline str::operator const char* () {return array;}

#endif

