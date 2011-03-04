/////////////////////////////////////////////////////////////////////
// StaticAssert.cpp - creates compile-time assert with decent      //
//                    error messages                               //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2005       //
/////////////////////////////////////////////////////////////////////

#include "StaticAssert.h"
//using namespace Loki;
/*
template <bool> struct CompileTimeChecker
{
  CompileTimeChecker(...);
};

template <> struct CompileTimeChecker<false> {};

#define STATIC_CHECK(expr, msg) \
{\
  class ERROR_##msg {}; \
  (void)sizeof(CompileTimeChecker<(expr)>(ERROR_##msg()));\
}

template <class To, class From>
To safe_reinterpret_cast(From from)
{
  STATIC_CHECK(sizeof(From) <= sizeof(To), Dest_Type_Too_Narrow);
  return reinterpret_cast<To>(from);
}

*/

void main()
{
  //StaticAssert(0,"error message");
  //void* somePointer = 0;
  //double* pD = safe_reinterpret_cast<double*>(somePointer);

  //char ch = safe_reinterpret_cast<ch>(somePointer);
}