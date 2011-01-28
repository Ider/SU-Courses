///////////////////////////////////////////////////////////////
//  str.cpp - implementation file for string class           //
//  ver 2.0                                                  //
//                                                           //
//  Language:     Visual C++, ver 6.0                        //
//  Platform:     Micron Dual Pentium Pro 200, Win NT 4.0    //
//  Application:  ECS500 Example                             //
//  Author:       Jim Fawcett, ECS500 Instructor             //
//                Syracuse University, CST 2-187             //
//                fawcett@ecs.syr.edu, (315) 443-3948        //
///////////////////////////////////////////////////////////////

#include "stdafx.h"
#include <iostream>
#include <cstring>
#include <stdexcept>
#include "str.h"
using namespace std;

//----< sized constructor >------------------------------------

str::str(int n) : array(new char[n]), max(n), len(0) 
{
  array[0] = '\0';
}

//----<copy constructor >--------------------------------------

str::str(const str& s) : array(new char[s.max]), max(s.max), len(s.len)
{
  int i;
  for(i=0; i<=len; i++)
    array[i] = s.array[i];
};

//----< promotion constructor >--------------------------------

str::str(const char* s) : len(static_cast<int>(strlen(s)))
{
  max = len+1;
  array = new char[len+1];
  int i;
  for(i=0; i<=len; i++)
    array[i] = s[i];
}

//

//----< destructor >-------------------------------------------

str::~str() {

  delete [] array;
  max = len = 0;
}

//----< assignment operator >----------------------------------

str& str::operator=(const str& s) {

  if(this == &s) return *this;
  if(max >= s.len+1) {
    len = s.len;
    int i;
    for(i=0; i<=len; i++)
      array[i] = s.array[i];
    return *this;
  }
  delete [] array;
  array = new char[max = s.max + 10];
  int i;
  len = s.len;
  for(i=0; i<=len; i++)
    array[i] = s.array[i];
  return *this;
}

//---< index operator >----------------------------------------

char& str::operator[](int n) {

  if(n<0 || len<=n)
    throw invalid_argument("index out of bounds in operator[]");
  return array[n];
}

//----< index operator for const str >-------------------------

char str::operator[](int n) const {

  if(n<0 || len<=n)
    throw invalid_argument("index out of bounds in operator[])");
  return array[n];
}

//

//----< append char to string >--------------------------------

str& str::operator+=(char ch) {

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

//----< append string to string >------------------------------

str& str::operator+=(const str& s) {

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

//----< addition operator >------------------------------------

str str::operator+(const str& s)
{
  str temp = *this;
  temp += s;
  return temp;
}
//
//----< insertion operator >-----------------------------------

ostream& operator<<(ostream& out, const str& s) {

  int i;
  for(i=0; i<s.size(); i++)
    out << s[i];
  return out;
}

//----< extraction operator >----------------------------------

istream& operator>>(istream& in, str& s) {

  char ch;
  s.flush();
  in >> ch;
  while((ch != '\n') && in.good()) {
    s += ch;
    in.get(ch);
  }
  return in;
}

//

//----< test stub >--------------------------------------------

#ifdef TEST_STR

#include <fstream>

int _tmain(int argc, _TCHAR* argv[]) 
{

  cout << "\n  Testing str class "
       << "\n ===================\n";

  try
  {
    cout << "\n  testing promotion constructor "
         << "\n -------------------------------\n";

    str s1 = str("this is a string");
    cout << "  new str object: " << s1 << endl;

    cout << "\n  testing copy constructor "
         << "\n --------------------------\n";

    str s2 = s1;                   // calls str(const str &s)
    cout << "  copy of original:    " << s2 << endl;

    cout << "\n  testing index operator "
         << "\n ------------------------\n";

    const str s3 = s1;
    char ch = s3[1];
    cout << "  second character is: " << ch << endl;

    s2[3] = 'x';
    cout << "  modifying fourth character: " << s2 << endl;

    cout << "\n  testing appends "
         << "\n -----------------\n";

    cout << "  appending vowel characters:\n";
    s1 += 'a';
    cout << "  " << s1 << endl;
    s1 += 'e';
    cout << "  " << s1 << endl;
    s1 += 'i';
    cout << "  " << s1 << endl;
    s1 += 'o';
    cout << "  " << s1 << endl;
    s1 += 'u';
    cout << "  " << s1 << endl;
    cout << "  size of str object is " << s1.size() << endl;
  
    cout << "\n  appending string \"yyy\": ";
    s1 += str("yyy");
    cout << s1 << endl;
    cout << "  size of str object is now " << s1.size() << endl; 

    cout << "  appending a long string to str object:\n  ";
    s1 += str(" and the rain in Spain falls mainly on the plain");
    cout << s1 << endl;
    cout << "  size of str object is now " << s1.size() << "\n\n";

//
    cout << "\n  testing addition operator "
         << "\n -----------------------------\n";

    str orig = str("  Original string");
    str sum = orig + str(" - this is a concatenated part");
    cout << sum << endl;

    cout << "\n  testing assignment operator "
         << "\n -----------------------------\n";

    cout << "  assigning the original's copy to this string: ";
    s1 = s2;
    cout << s2 << endl;
    cout << "  size of str object is now " << s1.size() << "\n\n";

    cout << "\n  testing memory resizing by multiple appends "
         << "\n ---------------------------------------------\n";  
    cout << "  appending \"C++ is great!!! \" several times to this string:\n\n";
    int i;
    for(i=0; i<5; i++) {
      s1 += str("C++ is great!!! ");
      s2 = s1;
      cout << "  " << s2 << endl;
      cout << "  size of str object is now " << s2.size() << "\n\n";
    }

    cout << "\n  testing insertion and extraction operators "
         << "\n --------------------------------------------\n";

    ofstream out("test.dat");
    if(!out.good()) {
      cout << "\n  can't open file for writing strings\n\n";
      return 1;
    }
    str insert1 = str("Now is the time for all good men ");
    insert1 += str("to come to the aid of their country");
    out << insert1 << endl;

    str insert2 = str("The rain in Spain falls mainly on the plain");
    out << insert2 << endl;

    str insert3 = str("This is the last line");
    out << insert3 << endl;

    out.close();
    ifstream in("test.dat");
    if(!in.good()) {
      cout << "\n  can't open file test.dat for input\n\n";
      return 1;
    }

    str extract;
    while(in.good()) {
      in >> extract;
      cout << "  " << extract << endl;
    }
    cout << endl;
//
    cout << "\n  testing cast operator "
         << "\n --------------------------------------------\n";

    const char* ccs = static_cast<const char*>(extract);

    cout << "  The string below is a const char*"
         << " holding address of last str's character memory:\n\n  "
         << ccs << endl << endl;

    cout << "\n  testing index operator "
         << "\n --------------------------------------------\n";

    str indexTest = str("012345");
    cout << "  " << indexTest << " - ";
    for(int i=0; i<7; ++i)
      cout << indexTest[i] << " ";
    cout << endl;
  }
  catch(exception& e)
  {
    cout << "\n  " << e.what() << endl << endl;
    return 1;
  }
  return 0;
}

#endif
