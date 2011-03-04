/////////////////////////////////////////////////////////////////////
// PartialTemplateSpecialization.cpp                               //
//       - demonstrating no, partial, and complete specialization  //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004       //
/////////////////////////////////////////////////////////////////////

#include <iostream>

/////////////////////////////////////////////////////////////////////
// Original template class

template <class T> 
class test1
{ 
public:
  test1(const T& t) : _t(t) {}
  void say()
  {
    std::cout << "\n  unspecialized: _t's value is: " << _t;
  }
private:
  T _t;
};

/////////////////////////////////////////////////////////////////////
// Complete specialization
//   - if template parameter is double use this

template <>
class test1<double>
{
public:
  test1(const double& d) : _d(d) {}
  void say()
  {
    std::cout << "\n    specialized: _d's value is: " << _d;
  }
private:
  double _d;
};

//
/////////////////////////////////////////////////////////////////////
// Original template class with two parameters

template <class T, class U>
class test2
{
public:
  test2(const T& t, const U& u) : _t(t), _u(u) {}
  void sayAll()
  {
    std::cout << "\n          Unspecialized: _t's value is: " << _t
      << ", _u's value is: " << _u;
  }
private:
  T _t;
  U _u;
};

/////////////////////////////////////////////////////////////////////
// Partial Template Specialization
//   - if first template parameter is int use this

template <class U>
class test2<int,U>
{
public:
  test2(const int& i, const U& u) : _i(i), _u(u) {}
  void sayAll()
  {
    std::cout << "\n  partially specialized: _i's value is: " << _i
      << ", _u's value is: " << _u;
  }
private:
  int _i;
  U _u;
};

/////////////////////////////////////////////////////////////////////
// Total Specialization for Two Parameters
//   - more specialized so use this for double in second parameter

template <>
class test2<int,double>
{
public:
  test2(const int& i, const double& d) : _i(i), _d(d) {}
  void sayAll()
  {
    std::cout << "\n    totally specialized: _i's value is: " << _i
      << ", _d's value is: " << _d;
  }
private:
  int _i;
  double _d;
};


//
/////////////////////////////////////////////////////////////////////
// Demonstration

void main()
{
  std::cout << "\n  Demonstrating no, partial, and full specialization "
            << "\n ====================================================\n";

  test1<char> t1d('a');
  t1d.say();

  test1<int> t1i(1);
  t1i.say();

  test1<double> t1s(2.2222);
  t1s.say();

  std::cout << "\n";

  test2<char,int> t2ci('b',2);
  t2ci.sayAll();

  test2<int,int> t2ii(3,3);
  t2ii.sayAll();

  test2<int,double> t2id(4,3.1415927);
  t2id.sayAll();

  std::cout << "\n\n";
}
