///////////////////////////////////////////////////////////////////////////
// BinaryConversion.cpp - first demonstration of TemplateMetaProgramming //
//                                                                       //
//            Calculates integer value of a binary                       //
//            number representation at compile time!                     //
//                                                                       //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2005             //
///////////////////////////////////////////////////////////////////////////
// Original example:
// C++ Template MetaProgramming, Abrahams, Gurtovoy, Addison-Wesley
//
// Notes:
// - Could be mildly useful when doing a lot of bit masking.
// - It's easy to write a run-time equivalent of this compile-time program.
// - If using fixed bit-mask in loop, compile-time computation is better.

#include <iostream>

// compute value recursively, prepending higher bits to lower

template <unsigned long N>
struct binary
{
  static unsigned const value = binary<N/10>::value << 1 | N%10;
};

// when recursed value of N is zero, stop recursion with
// this specialization

template <>
struct binary<0>
{
  static unsigned const value = 0;
};

void main()
{
  // starting with 11010:
  // N = 11010 => N%10 = 0
  // N =  1101 => N%10 = 1
  // N =   110 => N%10 = 0
  // N =    11 => N%10 = 1
  // N =     1 => N%10 = 1
  // compute 1*2^4 + 1*2^3 + 0*2^2 + 1*2^1 + 0*2^0

  std::cout << "\n  binary<1>::value = " 
            << binary<1>::value;      // displays 1
  std::cout << "\n  binary<11>::value = " 
            << binary<11>::value;     // displays 3
  std::cout << "\n  binary<110>::value = " 
            << binary<110>::value;    // displays 6
  std::cout << "\n  binary<1101>::value = " 
            << binary<1101>::value;   // displays 13
  std::cout << "\n  binary<11010>::value = " 
            << binary<11010>::value;  // displays 26
  std::cout << "\n\n";
}