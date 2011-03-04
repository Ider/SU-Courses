/////////////////////////////////////////////////////////////////////
// switch.cpp - compile-time type "switching"                      //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004       //
/////////////////////////////////////////////////////////////////////

#include <iostream>

template <int Case>
class SWITCH
{
public:
  static inline const char* RESULT() { return "\n  case default"; }
};

template <>
class SWITCH<1>
{
public:
  static inline const char* RESULT() { return "\n  case one"; }
};

template <>
class SWITCH<2>
{
public:
  static inline const char* RESULT() { return "\n  case two"; }
};

template <>
class SWITCH<3>
{
public:
  static inline const char* RESULT() { return "\n  case three"; }
};

void main()
{
  std::cout << SWITCH<0>::RESULT();
  std::cout << SWITCH<1>::RESULT();
  std::cout << SWITCH<2>::RESULT();
  std::cout << SWITCH<3>::RESULT();

  std::cout << "\n\n";
}

