/////////////////////////////////////////////////////////////////////
// typelist.cpp - compile-time function lists via recursion        //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004       //
/////////////////////////////////////////////////////////////////////

#include "typelist.h"
#include <iostream>

#define first "\n  "
#define mid   ", "
#define last  "\n\n"

void main()
{
  typedef TypeList< int, NullType > TL1;
  TL1::Head Int = 1;

  std::cout << first << Int << last;

  typedef TypeList< char, TL1 > TL2;
  TL2::Head Char = 'a';

  std::cout << first << Int << mid << Char << last;

  typedef TypeList< double, TL2> TL3;
  TL3::Head Double = 3.1415927;

  std::cout << first << Int << mid << Char << mid << Double << last;
}
