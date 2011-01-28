#ifndef STR_H
#define STR_H
///////////////////////////////////////////////////////////////
//  str.h      -  header file for string class               //
//  ver 2.0                                                  //
//                                                           //
//  Language:     Visual C++, ver 6.0                        //
//  Platform:     Micron Dual Pentium Pro 200, Win NT 4.0    //
//  Application:  ECS500 Example                             //
//  Author:       Jim Fawcett, ECS500 Instructor             //
//                Syracuse University, CST 2-187             //
//                fawcett@ecs.syr.edu, (315) 443-3948        //
///////////////////////////////////////////////////////////////
/*
    Class Operations:
    =================
    This class defines a string data type.  It is a simple, but
    effective user defined type.  You should prefer the standard
    C++ string class.  The purpose of this class is to demonstrate
    basic class construction techniques.

    Instances of str class perform bounds checking on all indexed
    operations and throw invalid_argument exceptions if the index 
    is out of bounds, e.g., does not refer to a valid character.

    Public Interface:
    =================
    str s;                  construct an empty string;
    str s(15);              construct empty string that holds 15 chars
    str s1 = s;             construct s1 as a copy of s
    str s2 = "a string";    construct s2 holding a literal string
    s1 = s2;                assign the value of s2 to the string s1
    s1[2] = 'a';            modify the 3rd character of s1
    char ch = s1[3];        read the 4th character of s1
    s1 += 'z';              append the character 'z'
    s1 += s2;               append the string s2 to the string s1
    s3 = s1 + s2;           concatenate s1 with s2 and assign to s3
    int len = s1.size();    get the number of characters held by s1
    s1.flush();             clear contents of s1, leaving empty string
    in >> s;                assign a string read from in to s
    out << s;               write a string to output stream;
*/
//
///////////////////////////////////////////////////////////////
//  Build Process                                            //
///////////////////////////////////////////////////////////////
//  Required files:                                          //
//    str.h, str.cpp                                         //
//                                                           //
//  compiler command:                                        //
//    cl /GX /DTEST_STR str.cpp                              //
///////////////////////////////////////////////////////////////
/*
    Maintenance History:
    ====================
    ver 2.0 : 25 Jan 2009
    - added initialization sequences.
    ver 1.9 : 29 Jan 2006
    - cosmetic changes
    ver 1.8 : 03 Feb 2005
    - added operator+, changed return type of operator+= from void
      to str&, qualified promotion ctor with explicit - note impact
      on test stub.
    ver 1.7 : 01 Feb 2005
    - str has an invariant that all string arrays held by the pointer
      array must be null terminated.  The default constructor, str(),
      did not correctly satisfy that, but now has been fixed.
    ver 1.6 : 29 Jan 2004
    - removed all checks for memory allocation failures, as the
      standard language behavior is to throw exceptions when this
      happens.  The link properties were set to include thrownew.obj
      to ensure that the compiled code conforms to this standard
      behavior.
    ver 1.5 : 27 Jan 2004
    - fixed bug in both overloads of operator+=() that resulted
      in index error exception when addition exactly fills
      available memory.  Operation was correct, throwing exception
      was not.
    ver 1.4 : 24 Jan 2004
    - added cast operator
    ver 1.3 : 17 Jan 2000
    - added bounds checking to index operators
    - made size() function inline
    ver 1.2 : 27 Sep 1999
    - added extraction operator
    - added tests for both insertion and extraction
    ver 1.1 : 15 Jun 1999
    - added manual and mainentance pages
    - simplified appends, assignment, and constructors
    ver 1.0 : 08 June 1999
    - first release

*/
//
#include <iostream>

class str {

private:
  char *array;
  int len, max;

public:
  str(int n = 10);                  // void and size ctor
  str(const str& s);                // copy ctor
  explicit str(const char* s);      // promotion ctor
  ~str();                           // dtor
  str& operator=(const str& s);     // assignment operator
  char& operator[](int n);          // index operator
  char operator[](int n) const;     // index operator for const str
  str& operator+=(char ch);         // append char
  str& operator+=(const str& s);    // append str s
  str operator+(const str& s);      // concatenate strs
  operator const char* ();          // cast operator
  int size() const;                 // return number of chars
  void flush();                     // clear string contents
};

std::ostream& operator<<(std::ostream& out, const str &s);  // non-member

std::istream& operator>>(std::istream& in, str &s);         // non-member

inline int str::size() const { return len; }                // number of chars

inline void str::flush() { len = 0; }         // remove chars, but not storage

inline str::operator const char* () { return array; }       // cast


#endif
