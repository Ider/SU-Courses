/////////////////////////////////////////////////////////////////////
//  newCasts.cpp - demonstrate use of new style casts              //
//                                                                 //
//  Jim Fawcett, CSE687 - Object Oriented Design, Spring 2001      //
/////////////////////////////////////////////////////////////////////
/*
 *  Static cast:
 *  ------------
 *  Creates new object using promotion constructor or cast operator
 *  if available.
 *
 *  toType toObject = static_cast<toType>(fromObject);
 *
 *  Const cast:
 *  -----------
 *  Casts away constness, used when you know a function call won't change
 *  invoking object or parameter, but the compiler does not know that.
 *
 *  nonConstType& nct = const_cast<constType&>(ct);
 *  nonConstFunct(nct);
 *
 *  Reinterpret cast:
 *  -----------------
 *  Reinterprets an object as a different type, without changing any
 *  of its bits.
 *
 *  byte* byteArray = reinterpret_cast<char*>(&d);
 *
 *  Dynamic cast:
 *  -------------
 *  Used to test if pointer or reference to base type is really a claimed
 *  specific derived type.
 *
 *  pD = dynamic_cast<derived*>(pB);
 *
 *  Returns pB if, and only if, pB is bound to an instance of derived, else zero.
 *
 * ------------------------------------------------------------------
 */
#include <iostream>
#include <string>
using namespace std;

void title(const std::string& title, char ch='-')
{
  std::cout << "\n  " << title;
  std::cout << "\n " << std::string(title.length()+2,ch);
}
void newline(size_t n=1)
{
  for(size_t i=0; i<n; ++i)
    std::cout << std::endl;
}
///////////////////////////////////////////////////////////////////////
//  Static Cast:
//  ------------
//  toType toObject = static_cast<toType>(fromObject);
//
//  Creates toObject by calling promotion constructor from toType
//    toType::toType(fromType fromObject);
//  or cast operator from fromType:
//    fromType::operator toType ()
//

class fromType;   // forward declaration needed by toType constructor

class toType
{
public:
  toType();
  explicit toType(const fromType& fromObject);
};
//----< void ctor >--------------------------------------------------

toType::toType() { /* used by fromType cast operator */ }

//----< promotion ctor - explicit so no silent conversion >----------

toType::toType(const fromType& fromObject)
{ 
  std::cout << "\n  promotion constr of toType from fromType via static_cast"; 
}

class fromType
{
public:
  operator toType ();
};
//----< cast operator >----------------------------------------------

fromType::operator toType ()
{
  std::cout << "\n  casting fromType to toType via fromType cast operator";  
  return toType(); 
}
//----< static_cast >------------------------------------------------

void DemoStaticCast()
{
  title("Demonstrating static_cast<someType>(...) and cast operator");
  fromType fromObject;
  toType toObject = static_cast<toType>(fromObject);
  
  //as the promotion constructor is explicit, 
  //it use casting of fromObject to cast the object;
  //if pro-constr is not explicit, it will choose pro-constr first.
  toType another_toObject = fromObject; 


 // toType again_toObject =  toType(fromObject);
}

///////////////////////////////////////////////////////////////////////
//  Const cast:
//  -----------
//  nonConstType& nct = const_cast<constType&>(ct);
//  nonConstFunct(nct);
//
//  Do this only if you know that nonConstFunction()
//  doesn't change the state of nct.

void display(string &s) { cout << "\n  " << s.c_str(); }

//void showString(const string &s) {
//
//  display does not guarantee not to change s
//  so compilation will fail
//
//  display(s);
//}

void DemoConstCast(const string &s) {

//  If we cast away const, as done here, the compiler
//  will accept the string reference since it is not const.
//  Obviously, we should never do this unless we are sure
//  that the state of s will in fact remain unchanged.

  title("Demonstrating const_cast<string&>()");
  string &sRef = const_cast<string&>(s);
  display(sRef);
}

///////////////////////////////////////////////////////////////////////
//  Reinterpret cast:
//  -----------------
//  toType* &fromObject reinterpret<toType*>(&fromObject);
//
//  Reinterpretes fromObject as new type toType. No bits are changed.
//  It is very rare that this cast is useful.  Otherwise it is evil!

void DemoReinterpretCast(double d) {

  title("Demonstrating reinterpret_cast<char*>");
  typedef char byte;
  byte* byteArray = reinterpret_cast<char*>(&d);
  cout << "\n  Reinterpreting double d = "  << d << " as byte array: ";
  for(int i=0; i<sizeof(d); i++)
    cout << byteArray[i] << " ";
}
///////////////////////////////////////////////////////////////////////
//  Dynamic cast:
//  -------------
//  derivedType* derivedTypePtr = dynamic_cast<derivedType*>(baseTypePtr);
//
//  if derivedType is derived from baseType and if baseTypePtr is bound to
//  an object of derived type, then the cast succeeds and the baseTypePtr
//  is returned, otherwise 0.

class base {

public:
  virtual void mf1() { cout << "\t this is base::mf1()"; }
  virtual ~base() { }
};

class derived : public base {

public:
  virtual void mf1() { cout << "\t this is derived::mf1()"; }
  virtual void mf2() { cout << "\t this is derived::mf2()"; }
};

void DemoDynamicCast()
{
  title("Demonstrating dynamic_cast<derived*>(base*)");
  base b;
  derived d;
  base* pB1 = &b;
  base* pB2 = &d;
  derived* pD;
  if(pD = dynamic_cast<derived*>(pB1))
  {
    std::cout << "\n  dynamic_cast passed: ";
    pD->mf2();
  }
  else
  {
    std::cout << "\n  dynamic_cast failed: ";
    pB1->mf1();
  }
  if(pD = dynamic_cast<derived*>(pB2))
  {
    std::cout << "\n  dynamic_cast passed: ";
    pD->mf2();
  }
  else
  {
    std::cout << "\n  dynamic_cast failed: ";
    pB2->mf1();
  }
}

// static_cast_Operator.cpp
// compile with: /LD
class B {

public:
	B(){cout << "this is B::B()\n"; bInt =20;}

 virtual void func(){cout << " this is B::func()"<<bInt<<"\n";}
private:
	int bInt;
};

class D : public B {
public:
	D(){cout << "this is D::D()\n"; dInt = 10;}
	void func(){cout << "this is D::func()"<<dInt<<"\n";}
	void funcD(){cout << "this is D::funcD()"<<dInt<<"\n";}
private:
	int dInt;


};


void f(B* pb, D* pd) {
	D* pd2 = static_cast<D*>(pb);   // not safe, pb may // point to just B
	pd2->func();
	pd2->funcD(); //if I set funcD to virtual, this call will be break.
	
	D* pd21 = dynamic_cast<D*>(pb);   //safe
	if (pd21)
	{
		pd21->func();
		pd21->funcD();
	}
	else
	{
		cout<<"dynamic_cast return null pointer value\n";
	}
	
	B* pb2 = static_cast<B*>(pd);   // safe conversion
	pb2->func();
}

void main() {

  title("New C++ casts: static, const, reinterpret, and dynamic",'=');
  newline();
  DemoStaticCast();
  newline();
  DemoConstCast("String passed as const ref: const_cast succeeded");
  newline();
  DemoReinterpretCast(3.1415927);
  newline();
  DemoDynamicCast();
  newline(2);

  f(new B(),new D());

  D* b = (D*)(new B());
}

