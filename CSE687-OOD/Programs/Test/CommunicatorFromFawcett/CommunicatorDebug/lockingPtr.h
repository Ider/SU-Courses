#ifndef LOCKINGPTR_H
#define LOCKINGPTR_H
/////////////////////////////////////////////////////////////////////
//  lockingPtr.h  -  provides serialized access to class objects   //
//  ver 1.5                                                        //
//  Language:        Visual C++, ver 6.0                           //
//  Platform:        Dell Dimension 8100, Win2000, SP 2            //
//  Application:     CSE691 - Useful for projects #2 and #3        //
//  Author:          Jim Fawcett, CST 2-187, Syracuse University   //
//                   (315) 443-3948, jfawcett@twcny.rr.com         //
/////////////////////////////////////////////////////////////////////
/*
  This module introduces the classes Mutex, GlobalMutex<int i>, safeOut,
  lockingPtr<class Obj, class Mtx>, and wrapper<class T>.  
  
  Four of these classes are closely modeled after those described by 
  Andrei Alexandrescu in "Generic<Programming>:volatile -- Multithreaded 
  Programmer's Best Friend ... ", C/C++ Users Journal, Feb 2001.

  Mutex Class Operation
  =====================
  Objects of the Mutex class are used to serialize access to specific
  locations in the using code, e.g., code between calls to lock() and
  unlock().  Note that we use the standard definition of Mutex, a lock
  ensuring mutually exclusive access, not the Microsoft definition, an
  inter-process lock.

  Public Interface for Mutex:
  ===========================
  Mutex mtx;                          // construct local Mutex object
  mtx.lock();                         // acquire lock for this code region
  cout << "\n  a serialized use of cout" << endl;
  mtx.unlock();                       // release the lock

  GlobalMutex Class Operation
  ===========================
  If you need to serialize access to an object that can be accessed from 
  several different locations in code, e.g., cout or a queue, then you 
  want to use an object of the GlobalMutex class.  You can declare an
  instance of GlobalMutex<int i> anywhere and the objects it locks will
  be locked for all locations in your code that are protected by a locally 
  declared instance of the same GlobalMutex<i> class.
  
  Public Interface for GlobalMutex:
  =================================
  MTQueue<int> intQ;      // declare an MTQueue holding integers
  GlobalMutex<1> gmtx1;   // declare once in each scope where you
    :                     //   want to access an the intQ object.
  gmtx1.lock();           // acquire a lock for cout object
  intQ.enQ(3);            // access the locked object
  gmtx1.unlock();         // release the lock

//

  If you want to independently lock some other queue, say dblQ, then you
  declare:
  
  MTQueue<double> dblQ;   // another queue, to be locked independently
  GlobalMutex<2> gmtx2;   // an instance of the GlobalMutex<2> class
    :
  gmtx2.lock();           // lock dblQ, independently of intQ
  double d = dblQ.deQ();  // access dblQ
  gmtx2.unlock();         // unlock it

  safeOut Class Operation
  =======================
  An object of the safeOut class serializes access to a std::ostream,
  like cout or an output file stream.

  Public Interface for SafeOut;
  =============================
  safeOut out(cout);      // creates a safeOut object for cout
  sout("....");           // uses safeOut::operator()
  sout << "...";          // sends string, safely. to cout

  If you need to lock several tandem calls to sout you have to do this:

  sout << locker << "the value is: " << val << '\n' << unlocker;

  lockingPtr Class Operation
  ==========================
  An object of the lockingPtr class provides serialized access to
  objects it references.  It implements a smart pointer that uses 
  an object of the Mutex  or GlobalMutex classes to provide a lock 
  mechanism.

  Public Interface for lockingPtr:
  ================================
  myObjType myObj;        // some arbitrary object you want to lock
  Mutex mtx;              // here we use an instance lock which locks
                          //   myObj only in this location
  lockingPtr<myObjType,Mutex>(*pMyObj,mtx)->memberFunction(args);
                          // create, use temporary lockingPtr

  This last statement is a very useful idiom.  It causes the lockingPtr
  object to be constructed, used, and immediately destroyed.  Thus, it 
  provides a single locked access to an object with only one line of code
  and immediately unlocks the object.

  You may wish to use typedefs to shorten the lockingPtr declarations.
  See this module's test stub to see how to do that.
*/

//

/*
  wrapper Class Operation
  =======================
  The wrapper class wraps a C++ primitive data type, e.g., int, double,
  etc, so that it can be locked with a lockingPtr.

  Public Interface for wrapper:
  =============================
  wrapper<double> dwrap(3.1415927)  // wrap a double
  double d = dwrap.value();         // uninteresting use of value member
  Mutex mtx;                        // make a Mutex lock

  double d = lockingPtr<wrapper<double>,Mutex>(dwrap,mtx)->value();

                                    // Here we used lockingPtr with the
                                    // double.  We locked the wrapped
                                    // double, accessed its value, and
                                    // unlocked it in one line of code.
*/

///////////////////////////////////////////////////////////////
//  build process                                            //
///////////////////////////////////////////////////////////////
//  required files:                                          //
//    lockingPtr.h, lockingPtr.cpp                           //
//  command line compile:                                    //
//    cl /GX /GZ /DTEST_LOCKINGPTR lockingPtr.cpp            //
///////////////////////////////////////////////////////////////
/*
    Maintenance History:
    ====================
    ver 1.5 : 17 Nov 2001
      - fixed a bug with reference counting, e.g., changed refCount++
        to InterlockedIncrement(&refCount) and changed refCount--
        to InterlockedDecrement(&refCount).
    ver 1.4 : 06 Nov 2001
      - provided manipulators, locker and unlocker, for safeOut class
      - made cosmetic changes to the manual page and safeOut class
    ver 1.3 : 28 Oct 2001
      - fixed omission in GlobalMutex classes by added reference 
        counting to ensure critical section is initialized and
        deleted just once.
      - added safeOut class
      - Modified lockingPtr class to use two template parameters.
        The first parameter represents the type of object being
        locked, the second represents the type of mutex used to
        lock.  Now you can use both Mutex and GlobalMutex objects.
    ver 1.2 : 26 Oct 2001
      - added GlobalMutex Class
    ver 1.1 : 23 Oct 2001
      - added missing #include <windows.h>
      - added test stub and more detail to manual page
      - added annunciators used during lockingPtr test, e.g., when
        TEST_LOCKINGPTR is defined
      - removed unnecessary #include <process.h>
    ver 1.0 : 10 Oct 2001
      - first release
*/
//
/*
    Design Notes:
    =============
    These notes address the template <int i> GlobalMutex<i> class.  We 
    address three issues: (1) the use of a static CRITICAL_SECTION, 
    (2) the need for an integer template parameter, and (3) how, and where
    to declare objects of this type.

    First Issue:
    The GlobalMutex classes use a static CRITICAL_SECTION and a static 
    integer refCount.  One static CRITICAL_SECTION is shared by all 
    instances of the class, due to the static qualifier.  That means that 
    you can declare a GlobalMutex<1> gmtx in any scope and always get the 
    same CRITICAL_SECTION variable.  Thus, you can lock a queue, that may 
    be accessed by different threads from several locations, simply by 
    declaring the gmtx object whereever you need the lock.

    There is one issue with that, however.  You do not want to keep 
    initializing and destroying the CRITICAL_SECTION variable every time 
    you declare the object or it goes out of scope.  So, this design uses 
    a reference counting scheme to avoid that.  The reference count starts 
    at zero, and when a GlobalMutex<1> object is declared, its constructor 
    initializes the CRITICAL_SECTION, but only if the reference count is 
    zero.  Then it increments the reference count.  Therefore, it only gets 
    initialized once.  Anytime a GlobalMutex<1> object goes out of scope 
    its reference count is decremented by its destructor.  Only when the 
    reference count is decremented to zero does the CRITICAL_SECTION get 
    destroyed.

    Second Issue:
    Because we may need to lock more than one queue object (or whatever we
    lock) independently, we need a way to get more than one GlobalMutex
    class, since each class shares a single CRITICAL_SECTION.  We can do
    that by templatizing the GlobalMutex class with an integer parameter:

        template <int i> class GlobalMutex<i> { ... };

    So, the declarations:

        GlobalMutex<1> gmtx1;
        GlobalMutex<2> gmtx2;

    generate objects from two different classes, and hence they do not share
    a common CRITICAL_SECTION, and so they lock independently.

    Third Issue:
    So, how and where do we declare objects of these classes.  In order to
    properly initialize and destroy a GlobalMutex class's CRITICAL_SECTION,
    you need to declare an instance before you do any locking, that will
    stay in scope until after you're done with all your locking.  One way to
    do that is to declare an instance near the beginning of the main routine.
    Then, anytime you need to lock an object, just declare an instance 
    locally, to introduce the class and object name into that scope, and use
    it's lock() and unlock() member functions.  The test stub shows you how
    to do that.
*/
//

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <iostream>
#include <string>

///////////////////////////////////////////////////////////////
//  class declaration for Mutex                              //
///////////////////////////////////////////////////////////////

class Mutex {

  public:
    Mutex();
    ~Mutex();
    void lock();
    void unlock();

  private:

  // different critical section for each Mutex object
  
    CRITICAL_SECTION cs;
};

//----< default constructor >----------------------------------

inline Mutex::Mutex() { InitializeCriticalSection(&cs); }

//----< destructor >-------------------------------------------

inline Mutex::~Mutex() { DeleteCriticalSection(&cs); }

//----< set lock >---------------------------------------------

inline void Mutex::lock() { EnterCriticalSection(&cs); }

//----< remove lock >------------------------------------------

inline void Mutex::unlock() { LeaveCriticalSection(&cs); }


//

///////////////////////////////////////////////////////////////
//  class declaration for GlobalMutex                        //
///////////////////////////////////////////////////////////////

template <int i>
class GlobalMutex {

  public:
    GlobalMutex();
    ~GlobalMutex();
    void lock();
    void unlock();

  private:

  // shared critical section for all GlobalMutex objects

    static CRITICAL_SECTION cs;
    static long refCount;
};

//----< initialize static variables >--------------------------

template <int i>
CRITICAL_SECTION GlobalMutex<i>::cs;

template <int i>
long GlobalMutex<i>::refCount = 0;

//----< default constructor >----------------------------------

template <int i>
GlobalMutex<i>::GlobalMutex() { 

  if(refCount == 0)
    InitializeCriticalSection(&cs);
  InterlockedIncrement(&refCount);
}

//----< destructor >-------------------------------------------

template <int i>
GlobalMutex<i>::~GlobalMutex() { 

//  safeOut sout(std::cout);
//  sout << "\n  into ~GlobalMutex()";
  InterlockedDecrement(&refCount);
  if(refCount == 0)
    DeleteCriticalSection(&cs); 
//  sout << "\n  closing ~GlobalMutex()";
}

//----< set lock >---------------------------------------------

template <int i>
void GlobalMutex<i>::lock() { EnterCriticalSection(&cs); }

//----< remove lock >------------------------------------------

template <int i>
void GlobalMutex<i>::unlock() { LeaveCriticalSection(&cs); }


//

///////////////////////////////////////////////////////////////
//  class declaration for lockingPtr                         //
///////////////////////////////////////////////////////////////

template <class Obj, class Mtx> class lockingPtr {

  public:
    lockingPtr(volatile Obj &obj, Mtx &mtx);
    ~lockingPtr();
    Obj& operator*();
    Obj* operator->();

  private:
    Obj* _pObj;
    Mtx *_pMtx;
    lockingPtr(const lockingPtr&);
    lockingPtr& operator=(const lockingPtr&);
};

//----< constructor takes object to lock and Mutex >-----------

template <class Obj, class Mtx> inline
lockingPtr<Obj, Mtx>::lockingPtr(volatile Obj &obj, Mtx &mtx) 
             : _pObj(const_cast<Obj*>(&obj)), _pMtx(&mtx) { 

#ifdef TEST_LOCKINGPTR
  cout << "\n  constructing a LockingPtr object - calls lock()";
  cout.flush();
#endif

  mtx.lock(); 
}

//----< destructor >-------------------------------------------

template <class Obj, class Mtx> inline
lockingPtr<Obj, Mtx>::~lockingPtr() { 
  
  _pMtx->unlock(); 

#ifdef TEST_LOCKINGPTR
   cout << "\n  destroying a LockingPtr object - calls unlock()";
   cout.flush();
#endif
}

//

//----< get locked object >------------------------------------

template <class Obj, class Mtx> inline
Obj& lockingPtr<Obj, Mtx>::operator*() { 
  
#ifdef TEST_LOCKINGPTR
  cout << "\n accessing contents of locked object";
  cout.flush();
#endif

  return *_pObj; 
}

//----< get access to locked object's members >----------------

template <class Obj, class Mtx> inline
Obj* lockingPtr<Obj, Mtx>::operator->() { 

#ifdef TEST_LOCKINGPTR
  cout << "\n  accessing member of locked object";
  cout.flush();
#endif
  
  return _pObj; 
}

//

///////////////////////////////////////////////////////////////
//  class declaration for safeOut                            //
///////////////////////////////////////////////////////////////

class safeOut {

  friend safeOut& locker(safeOut &);
  friend safeOut& unlocker(safeOut &);

  public:
    safeOut(std::ostream &Out);
    ~safeOut();
    void operator()(const std::string &msg);
    void operator()(const char *msg);
    void operator()(double val);
    void operator()(int val);
    void operator()(char ch);
    safeOut& operator<<(const std::string &msg);
    safeOut& operator<<(const char *msg);
    safeOut& operator<<(double val);
    safeOut& operator<<(int val);
    safeOut& operator<<(char ch);
    safeOut& operator<<(safeOut& (*op)(safeOut&));

  private:
    static CRITICAL_SECTION cs;
    static long refCount;
    std::ostream &out;
};

//----< constructor >------------------------------------------

inline safeOut::safeOut(std::ostream &Out) : out(Out) { 
  if(refCount == 0) 
    InitializeCriticalSection(&cs); 
  InterlockedIncrement(&refCount);
}

//----< destructor >-------------------------------------------

inline safeOut::~safeOut() { 
  InterlockedDecrement(&refCount);
  if(refCount == 0) 
    DeleteCriticalSection(&cs); 
}

//

//----< function with string argument overload >---------------

inline void safeOut::operator()(const std::string &msg) {
  EnterCriticalSection(&cs);
    out << msg.c_str();
    out.flush();
  LeaveCriticalSection(&cs);
}

//----< function with char* argument overload >----------------

inline void safeOut::operator()(const char *msg) {
  EnterCriticalSection(&cs);
    out << msg;
    out.flush();
  LeaveCriticalSection(&cs);
}

//----< function with double argument overload >---------------

inline void safeOut::operator()(double val) {
  EnterCriticalSection(&cs);
    out << val;
    out.flush();
  LeaveCriticalSection(&cs);
}

//----< function with long argument overload >-----------------

inline void safeOut::operator()(int val) {
  EnterCriticalSection(&cs);
    out << val;
    out.flush();
  LeaveCriticalSection(&cs);
}

//----< function with char argument overload >-----------------

inline void safeOut::operator()(char ch) {
  EnterCriticalSection(&cs);
    out << ch;
    out.flush();
  LeaveCriticalSection(&cs);
}

//

//----< insertion of string >----------------------------------

inline safeOut& safeOut::operator<<(const std::string &msg) {
  operator()(msg);
  return *this;
}

//----< insertion of char* >-----------------------------------

inline safeOut& safeOut::operator<<(const char *msg) {
  operator()(msg);
  return *this;
}

//----< insertion of double >----------------------------------

inline safeOut& safeOut::operator<<(double val) {
  operator()(val);
  return *this;
}

//----< insertion of long >------------------------------------

inline safeOut& safeOut::operator<<(int val) {
  operator()(val);
  return *this;
}

//----< insertion of char >------------------------------------

inline safeOut& safeOut::operator<<(char ch) {
  operator()(ch);
  return *this;
}

//

//----< operator accepting a manipulator with no arguments >---

inline safeOut& safeOut::operator<<(safeOut& (*op)(safeOut&)) {
  return (*op)(*this);
}

//----< a locking manipulator used with no arguments >---------

inline safeOut& locker(safeOut &sstrm) {
  EnterCriticalSection(&safeOut::cs);
  return sstrm;
}

//----< an unlocking manipulator used with no arguments >------

inline safeOut& unlocker(safeOut &sstrm) {
  LeaveCriticalSection(&safeOut::cs);
  return sstrm;
}

//

///////////////////////////////////////////////////////////////
//  class declaration for generic wrapper                    //
//    allows us to use lockingPtr with primitive types       //
//    like int or double                                     //
///////////////////////////////////////////////////////////////

template <class T> class wrapper {

  public:
    wrapper(T t);
    T value();

  private:
    T _t;
};

//----< constructor wraps a reference to primitive object >----
//
//  This class will wrap virtually anything, but it is intended
//  to wrap the C++ primitive data, char, int, double, etc. for
//  use with lockingPtrs

template <class T> wrapper<T>::wrapper(T t) : _t(t) { }

//----< provides access to the object >------------------------

template <class T> T wrapper<T>::value() { return _t; }


#endif
