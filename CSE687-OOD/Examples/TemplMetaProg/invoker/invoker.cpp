/////////////////////////////////////////////////////////////////
//  invoker1.cpp - defines classes to wrap function pointers   //
//                                                             //
//  Jim Fawcett, CSE687 - Object Oriented Design, Spring 05    //
/////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>

template <class R, class A, R(*fptr)(A)>
class delegate
{
public:

  virtual ~delegate() {}

  R invoke(A a)
  {
    return fptr(a);
  }
  R operator()(A a)
  {
    return fptr(a);
  }
};

template <class T, class R, class A, R(T::*fPtr)(A)>
class mDelegate
{
public:

  mDelegate(T t) : obj(t) {}

  virtual ~mDelegate() {}

  R invoke(A a)
  {
    return (obj.*fPtr)(a);
  }
  R operator()(A a)
  {
    return (obj.*fPtr)(a);
  }
private:
  T obj;
};

//
int trunc(double d)
{
  return static_cast<int>(d);
}

struct Args
{
  int i;
  double d;
};

void simulateArgs(Args& a)
{
  std::cout << "\n  1st arg = " << a.i;
  std::cout << "\n  2nd arg = " << a.d;
}

class X
{
public:
  int fun(int i) { return 2*i; }
};

void main()
{
  std::cout << "\n  Demonstrating Template-based Delegates";
  std::cout << "\n ========================================\n";

  delegate<int, double, trunc> del;
  std::cout << "\n  received " << del.invoke(3.5) << " from invoker";
  std::cout << "\n  received " << del(-3.5) << " from invoker\n";

  delegate<void, Args&, simulateArgs> rdel;
  Args a = { -3, 3.1415927 };
  rdel.invoke(a);
  a.i = 3;
  a.d = 0.333333333;
  rdel(a);
  std::cout << std::endl;

  X x;
  mDelegate<X, int, int, &X::fun> mdel(x);
  std::cout << "\n  X::fun returns " << mdel.invoke(3);
  std::cout << "\n  X::fun returns " << mdel(17);

  std::cout << "\n\n";
}
