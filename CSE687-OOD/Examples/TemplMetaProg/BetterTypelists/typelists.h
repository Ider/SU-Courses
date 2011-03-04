#ifndef TYPELISTS_H
#define TYPELISTS_H
/////////////////////////////////////////////////////////////////////
// typelists.h  -  compile-time lists via recursion                //
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

/////////////////////////////////////////////////////////////////////
// TYPELIST macros

#define TYPELIST_1(T1) TypeList< T1, NullType >
#define TYPELIST_2(T1,T2) TypeList< T1, TYPELIST_1(T2) >
#define TYPELIST_3(T1,T2,T3) TypeList< T1, TYPELIST_2(T2,T3) >
#define TYPELIST_4(T1,T2,T3,T4) TypeList< T1, TYPELIST_3(T2,T3,T4) >

/////////////////////////////////////////////////////////////////////
// make TypeList

template < class T1=NullType, 
           class T2=NullType, 
           class T3=NullType, 
           class T4=NullType >
struct MakeTypeList
{
private:
  typedef typename MakeTypeList< T2, T3, T4 >::Result TailResult;
public:
  typedef TypeList< T1, TailResult > Result;
};

template <>
struct MakeTypeList < NullType, NullType, NullType, NullType >
{
  typedef NullType Result;
};

//
/////////////////////////////////////////////////////////////////////
// Length - find length of TypeList

template < class TList > struct Length;

template <> struct Length<NullType> { enum { value = 0 }; };

template < class T, class U >
struct Length < TypeList< T, U > >
{
  enum { value = 1 + Length<U>::value };
};

/////////////////////////////////////////////////////////////////////
// TypeAt - find type at a given index

template < class TList, unsigned int index > struct TypeAt;

template < class Head, class Tail >
struct TypeAt < TypeList < Head, Tail >, 0 >
{
  typedef Head Result;
};

template < class Head, class Tail, unsigned int i >
struct TypeAt < TypeList < Head, Tail >, i >
{
  typedef typename TypeAt < Tail, i-1 >::Result Result;
};

//
/////////////////////////////////////////////////////////////////////
// Search for Type

template < class TList, class T > struct IndexOf;

template < class T >
struct IndexOf < NullType, T > { enum { value = -1 }; };

template < class Tail, class T >
struct IndexOf < TypeList < T, Tail >, T >
{
  enum { value = 0 };
};

template < class Head, class Tail, class T >
struct IndexOf < TypeList < Head, Tail >, T >
{
private:
  enum { temp = IndexOf < Tail, T >::value };
public:
  enum { value = temp == -1 ? -1 : 1 + temp };
};

/////////////////////////////////////////////////////////////////////
// Appending another type

template < class TList, class T > struct Append;

template <> struct Append < NullType, NullType >
{
  typedef NullType Result;
};

template < class T >
struct Append < NullType, T>
{
  typedef TYPELIST_1(T) Result;
};

template < class Head, class Tail >
struct Append < NullType, TypeList < Head, Tail > >
{
  typedef TypeList < Head, Tail > Result;
};

template < class Head, class Tail, class T >
struct Append < TypeList < Head, Tail >, T >
{
  typedef TypeList < Head, typename Append < Tail, T >::Result > Result;
};

//
/////////////////////////////////////////////////////////////////////
// Replace type in TypeList

template < class TList, class T, class U > struct Replace;

template < class T, class U >
struct Replace < NullType, T, U >
{
  typedef NullType Result;
};

template < class T, class Tail, class U > 
struct Replace < TypeList < T, Tail >, T, U >
{
  typedef TypeList < U, Tail > Result;
};

template < class Head, class Tail, class T, class U >
struct Replace < TypeList < Head, Tail >, T, U >
{
  typedef TypeList < Head, typename Replace < Tail, T, U >::Result > Result;
};

#endif
