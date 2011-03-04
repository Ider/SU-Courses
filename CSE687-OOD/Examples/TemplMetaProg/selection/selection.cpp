/////////////////////////////////////////////////////////////////////
// selection.cpp - compile-time type selections                    //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004       //
/////////////////////////////////////////////////////////////////////

#include <iostream>

/////////////////////////////////////////////////////////////////////
// type selection

template <bool p, class T, class F>
struct SELECT { typedef T RET; };

template <class T, class F>
struct SELECT<false,T,F> { typedef F RET; };

class TrueType
{
public:
  void say() {  std::cout << "\n  I'm true"; }
};

class FalseType
{
public:
  void say() {  std::cout << "\n  I'm false"; }
};

/////////////////////////////////////////////////////////////////////
// Demonstrations

void main()
{
  std::cout << "\n";
  SELECT<true,TrueType,FalseType>::RET first;   // declared type
  first.say();

  SELECT<false,TrueType,FalseType>::RET second; // declared type
  second.say();
 
  std::cout << "\n\n";
}
