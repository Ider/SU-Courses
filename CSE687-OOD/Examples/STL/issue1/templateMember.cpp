/////////////////////////////////////////////////////////////////
//  templateMembers.cpp - Issue #1                             //
//                                                             //
//  Jim Fawcett, CSE687 - Object Oriented Design, Spring 2005  //
/////////////////////////////////////////////////////////////////

class X
{
public:

  /////////////////////////////////////
  // template member

  template <typename T>
  T* clone() { return new T; }

  // other members
};

///////////////////////////////////////
// Note: class X above could also have
//       been a template class of some
//       other paramter, say U.  The
//       results are the same.

void main()
{
  X x;

  /////////////////////////////////////////////////////////////
  // Stroustrup, pg 858
  // X* newx = x.clone();  compiler can't deduce parameter

  X* newx = x.template clone<X>();  
}
