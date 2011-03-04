/////////////////////////////////////////////////////////////////////
// functions.cpp - compile-time function evaluation                //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004       //
/////////////////////////////////////////////////////////////////////

#include <iostream>

/////////////////////////////////////////////////////////////////////
// square

template <int i>
class square { public: enum { value = i*i }; };

template <int i>
class square2 { public: static const int value = i*i; };


/////////////////////////////////////////////////////////////////////
// power

template <int n, int p>
struct POWER
{
  enum { value = n * POWER<n, p-1>::value };
};

template <int n> struct POWER<n,0> { enum { value = 1 }; };

/////////////////////////////////////////////////////////////////////
// Demonstrations

void main()
{
	std::cout << "\n  " << square<9>::value << "\n";
  std::cout << "\n  " << square2<10>::value << "\n";

  std::cout << "\n  " << POWER<2,16>::value << "\n";

  std::cout << "\n\n";
}