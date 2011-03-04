/////////////////////////////////////////////////////////////////////
// typelists.cpp  -  Better compile-time lists via recursion       //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004       //
/////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include "typelists.h"

#define first "\n  "
#define mid   ", "
#define line  "\n";
#define last  "\n\n"

void main()
{
  std::cout << "\n  Demonstrating Better TypeLists "
            << "\n ================================\n";

  ///////////////////////////////////////////////////////////////////
  // Basic construction of TypeList

  typedef TYPELIST_4(int,char,double,std::string) tl4a;
  tl4a::Head Int = 1;

  typedef tl4a::Tail tl4b;
  tl4b::Head Char = 'a';

  typedef tl4b::Tail tl4c;
  tl4c::Head Double = 3.5;

  typedef tl4c::Tail tl4d;
  tl4d::Head String = "\"a string\"";

  typedef tl4d::Tail tl4e;

  std::cout << first << Int << mid << Char << mid << Double << mid << String 
            << line;

  std::cout << first << "Length of tl4a is: " << Length<tl4a>::value;
  std::cout << first << "Length of tl4b is: " << Length<tl4b>::value;
  std::cout << first << "Length of tl4c is: " << Length<tl4c>::value;
  std::cout << first << "Length of tl4d is: " << Length<tl4d>::value;
  std::cout << first << "Length of tl4e is: " << Length<tl4e>::value << line;

  ///////////////////////////////////////////////////////////////////
  // Using MakeTypeList

  std::cout << "\n  Making a TypeList the Easy Way "
            << "\n --------------------------------\n";

  typedef MakeTypeList<int,char,double,std::string>::Result tlf;
  std::cout << first << "Type list tlf:";
  std::cout << first << typeid(TypeAt<tlf,0>::Result).name();
  std::cout << mid << typeid(TypeAt<tlf,1>::Result).name();
  std::cout << mid << typeid(TypeAt<tlf,2>::Result).name();
  std::cout << mid << typeid(TypeAt<tlf,3>::Result).name() << line;
  std::cout << first << "Length of tlf is: " << Length<tlf>::value << line;

//
  ///////////////////////////////////////////////////////////////////
  // Indexing and Searching in TypeLists

  std::cout << "\n  Demonstrate indexing and searching in TypeList "
            << "\n ------------------------------------------------\n";

  std::cout << first << "Type list tl4a:";
  std::cout << first << typeid(TypeAt<tl4a,0>::Result).name();
  std::cout << mid << typeid(TypeAt<tl4a,1>::Result).name();
  std::cout << mid << typeid(TypeAt<tl4a,2>::Result).name();
  std::cout << mid << typeid(TypeAt<tl4a,3>::Result).name();

///////////////////////////////////////////////////////////////////
// - The good news is that indexing beyond the end of the list
//   is a compile-time error.
// - The bad news is that the error location is not at the site
//   of the error (the error message does make sense - ok).
//
//  std::cout << mid << typeid(TypeAt<tl4a,4>::Result).name();
  
  std::cout << line;

  TypeAt< tl4a, 1 >::Result IndexedCharType = 'z';
  std::cout << first << "type at index 1 in tl4a is: " 
            << typeid(IndexedCharType).name() << line;

  std::cout << first << "index of double type in tl4a is: " 
            << IndexOf< tl4a, double >::value << line;

  std::cout << first << "index of long type in tl4a is: " 
            << IndexOf< tl4a, long >::value << line;

  ///////////////////////////////////////////////////////////////////
  // Appending another type on a TypeList

  std::cout << "\n  Demonstrate Appending to TypeList "
            << "\n -----------------------------------\n";

  std::cout << first << "appending long to tl4a:" << line;

  typedef Append<tl4a,long>::Result tl5;
  std::cout << first << "index of long type in tl5 is: "
            << IndexOf< tl5, long >::value << line;

  ///////////////////////////////////////////////////////////////////
  // Replacing a type in a TypeList

  std::cout << "\n  Demonstrating TypeList Replacement "
            << "\n ------------------------------------\n";

  std::cout << first << "replacing double in tl4a with short:" << line;

  typedef Replace<tl4a,double,short>::Result tl6;
  std::cout << first << "index of short type in tl6 is: "
            << IndexOf< tl6, short >::value << line;
  std::cout << first << "index of double type in tl6 is: "
            << IndexOf< tl6, double >::value << last;
}
