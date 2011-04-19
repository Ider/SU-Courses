///////////////////////////////////////////////////////////////////////
//  lockingPtr.cpp  -  provides serialized access to class objects   //
//  ver 1.5                                                          //
//  Language:          Visual C++, ver 6.0                           //
//  Platform:          Dell Dimension 8100, Win2000, SP 2            //
//  Application:       CSE691 - Useful for projects #2 and #3        //
//  Author:            Jim Fawcett, CST 2-187, Syracuse University   //
//                     (315) 443-3948, jfawcett@twcny.rr.com         //
///////////////////////////////////////////////////////////////////////

#include <iostream>
#include "lockingPtr.h"
using namespace std;

/////////////////////////////////////////////////////////////////////
//  initialize static data members of safeOut class

CRITICAL_SECTION safeOut::cs;
long safeOut::refCount = 0;

//----< test stub >--------------------------------------------------
//
//  NOTE:
//  In this version, the test stub does not create threads.  It simply uses
//  the locking objects in a way consistent with multithreaded programming.

#ifdef TEST_LOCKINGPTR

typedef GlobalMutex<2> glbObjLock;

/////////////////////////////////////////////////////////////////////
//  declaration of a test class

class testObj {

  public:
    testObj(int value) : _val(value) { }
    int& value() { return _val; }

  private:
    int _val;
};

typedef lockingPtr<testObj, glbObjLock> glbLockPtr;

//

//----< defines a scope in which global locks will be defined >------

void test1(testObj &to) {

  // safeOut object provides serialized access to an ostream

  safeOut sout(cout);
  sout("\n  In scope of test1 function:\n");

  // this code illustrates how to lock a local object
  // against concurrent access by more than one thread
  // for just this code location

  testObj temp(-3);
  Mutex localLock;
  localLock.lock();
  int val = temp.value();
  localLock.unlock();

  sout << "\n  value retrieved from temporary testObj, using Mutex = "
       << val << '\n';

  // or, using a lockingPtr

  val = lockingPtr<testObj,Mutex>(temp,localLock)->value();

  sout << "\n  value retrieved from temporary testObj, using Mutex = "
       << val << "\n";

  // this code illustrates how to lock a non-local object
  // against concurrent access by more than one thread in
  // this, as well as other locations

  glbObjLock outMtx;
  val = glbLockPtr(to,outMtx)->value();
  sout << "\n  value retrieved from testObj ref, using GlobalMutex = "
       << val << '\n';
}

//----< defines a scope in which global locks will be defined >------

void test2(testObj &to) {

  safeOut sout(cout);
  sout << "\n  In scope of test2 function:\n";

  // this code illustrates how to lock a non-local object
  // against concurrent access by more than one thread in
  // this, as well as other locations

  glbObjLock outMtx;
  int val = glbLockPtr(to,outMtx)->value();

  sout << "\n  value retrieved from testObj ref, using GlobalMutex = "
       << val << '\n';
}

//

//----< start of testing >-------------------------------------------

void main() {


  safeOut sout(cout);
  sout << "\n  Demo Constr'n and Destr'n of Temporary lockingPtr Objects "
       << "\n ===========================================================\n";

  Mutex mtx;
  testObj dso(5);

  sout << locker 
       << "\n  before accessing testObj with lockedPtr<testObj, Mutex>" 
       << '\n' << unlocker;

  // create, use temporary lockingPtr object, will be destroyed immediately

  int temp = lockingPtr<testObj, Mutex>(dso,mtx)->value();

  sout << "\n\n  retrieved value = " << temp << "\n\n";

  GlobalMutex<1> gmtx1;   // initializing CRITICAL_SECTION before use

  sout << "\n  before accessing testObj "
       << "with lockedPtr< testObj, GlobalMutex<1> >" << '\n';

  // create & use temporary lockingPtr object - will be destroyed immediately

  temp = lockingPtr< testObj, GlobalMutex<1> >(dso,gmtx1)->value();

  sout << "\n\n  retrieved value = " << temp << "\n\n";

  sout << locker << "\n  before accessing a double variable "
       << "using wrapper class\n" << unlocker;

  wrapper<double> dwrap(3.1415927);
  double dtemp = lockingPtr<wrapper<double>,Mutex>(dwrap,mtx)->value();

  sout << locker << "\n\n  double value = " << dtemp << '\n' << unlocker;


  sout << "\n  Testing use of GlobalMutex in Several Scopes "
       << "\n ==============================================\n";

  GlobalMutex<2> gmtx2;   // initializing CRITICAL_SECTION before use

  test1(dso);
  test2(dso);

  sout << "\n\n";

}

#endif
