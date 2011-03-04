#ifndef TYPELIST_H
#define TYPELIST_H
/////////////////////////////////////////////////////////////////////
// typelist.h  -  compile-time function lists via recursion        //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004       //
/////////////////////////////////////////////////////////////////////

template <typename H, typename T>
struct TypeList
{
  typedef H Head;
  typedef T Tail;
};

struct NullType
{
  struct Head { private: Head(); };
  struct Tail { private: Tail(); };
};

struct EmptyType {};

#endif
