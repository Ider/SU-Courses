/////////////////////////////////////////////////////////////////
//  typename.cpp - Issue #2                                    //
//                                                             //
//  Jim Fawcett, CSE687 - Object Oriented Design, Spring 2005  //
/////////////////////////////////////////////////////////////////
//  Compiler sometimes needs help in determining if a 
//  template expression is a type declaration.  When you
//  get the error: dependent name is not a type
//  you need to qualify with: typename

#include <vector>

template <typename C>
typename C::iterator func(C& c)  // iterator a type or a data member of C?
{
  typename C::iterator i=c.begin();

  // more code

  return i;
}

///////////////////////////////////////////////////////////////
// Note: VC7 will compile without the second typename
//       C::iterator but not without the first.
//       Without the typename you get the error:
//       dependent name (iterator) is not a type.

void main()
{
  std::vector<int> v;

  std::vector<int>::iterator i = func(v);
}
