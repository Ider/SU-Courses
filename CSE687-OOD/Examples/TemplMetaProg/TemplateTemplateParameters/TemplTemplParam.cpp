/////////////////////////////////////////////////////////////////////
// TemplTemplParam.cpp                                             //
//             - Illustrates use of template template parameters   //
//                                                                 //
// Jim Fawcett, CSE687 - Object Oriented Design, Spring 2004       //
/////////////////////////////////////////////////////////////////////

#include <vector>
#include <string>

template <typename T>
class Widget
{
public:
  Widget(const T& t) : _t(t) {}
  T& value() { return _t; }
private:
  T _t;
};

template <typename Object>
class container
{
public:
  void add(const Object &ob) { Objs.push_back(ob); }
  Object& operator[](int n) { return Objs[n]; }
  unsigned int size() { return Objs.size(); }
private:
  std::vector<Object> Objs;
};

/////////////////////////////////////////////////////////////////////
// template with template parameter
// - its odd, but typename does not work here
// - user will instantiate with containerTTP<T,Object>
//   where T and Object are a type and template respectively 

template < class T, template<class> class Object >
class containerTTP
{
public:
  void add(const Object<T>& ob) { Objs.push_back(ob); }
  Object<T>& operator[](int n) { return Objs[n]; }
  unsigned int size() { return Objs.size(); }
private:
  std::vector< Object<T> > Objs;
};

//
/////////////////////////////////////////////////////////////////////
// template with template parameter, version 2
// - template parameter isn't used in class or is explicitly specified
// - user instantiates as PolicyUser<somePolicy>

template <template <class T> class Policy>
class PolicyUser
{
public:
  void say() { std::cout << "\n  PolicyUser here with " << a; }
  Policy<std::string>& value() { return a; }
private:
  Policy<std::string> a;  // explicit parameter
};

template<class T>
class Test
{ 
public:
  void say()
  {
    std::cout << "\n  PolicyUser here";
  }
  T& value() { return t; }
private:
  T t;
};

template<class T>
std::ostream& operator<<(std::ostream& out, Test<T>& t)
{
  out << t.value();
  return out;
}
//
/////////////////////////////////////////////////////////////////////
// Demonstration

#include <iostream>

void main()
{
  std::cout << "\n  Demonstrating Template-Template Parameters "
            << "\n ============================================\n";

  Widget<std::string> w("cheeta");

  container< Widget<std::string> > c;
  c.add(w);
  c.add(w.value() = "panther");
  c.add(w.value() = "lion");
  c.add(w.value() = "angora");
  c.add(w.value() = "wildcat");

  for(unsigned int i=0; i<c.size(); ++i)
    std::cout << "\n  " << c[i].value();
  std::cout << "\n\n";

  ///////////////////////////////////////////////////////////////////
  // template template parameter, version 1
  // - if you have lots of parameters, the TTP form
  //   is easier for client to use than first form, e.g.,
  //   C<T,X,Y,Z> myC; instead of C< X<T>, Y<T>, Z<T> > myC

  containerTTP<std::string, Widget> cTTP;
  cTTP.add(w);
  cTTP.add(w.value() = "panther");
  cTTP.add(w.value() = "lion");
  cTTP.add(w.value() = "angora");
  cTTP.add(w.value() = "wildcat");

  for(unsigned int i=0; i<cTTP.size(); ++i)
    std::cout << "\n  " << cTTP[i].value();
  std::cout << "\n\n";

  ///////////////////////////////////////////////////////////////////
  // template template parameter, version 2
  // - client doesn't need to say PolicyUser< Test<std::string> > myUser;

  PolicyUser<Test> myUser;
  Test<std::string> t;
  t.value() = "a policy";
  myUser.value() = t;
  myUser.say();

  std::cout << "\n\n";
}
