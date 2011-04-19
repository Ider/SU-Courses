#ifndef LOCKS_H
#define LOCKS_H
/////////////////////////////////////////////////////////////////////
//  locks.h       - classes supporting synchronization of shared   //
//  ver 1.4         objects                                        //
//                                                                 //
//  Language:       Visual C++, ver 7.1, SP 2                      //
//  Platform:       Dell Dimension 8300, Win XP, SP2               //
//  Application:    CSE687 - Object Oriented Design                //
//  Author:         Jim Fawcett, CST 2-187, Syracuse Univ          //
//                  (315) 443-3948, jfawcett@twcny.rr.com          //
//                                                                 //
/////////////////////////////////////////////////////////////////////
/*
    Module Operations
    =================
    This module provides local locking via LLock and global locking
    with GLock<i>, where i is a group that shares a common lock.

    Public Interface
    ================
    LLock l;                    // local lock that protects holder 
    l.lock();                   // set lock
    l.unlock();                 // unset lock
                                // Global lock protects holder of any GLock<1>
    GLock<1> l1;                // instance.  GLock<-1> reserved for syncOut.
    l1.lock();                  // set lock
    l1.unlock();                // unset lock

    sout << "a string";         // globally available synchronized output
    sout << locker << "a string" << 3.1415927 << myObject << unlocker;
                                // locker & unlocker are manipulators needed
                                // to protect a sequence of insertions
    
*/      
//
///////////////////////////////////////////////////////////////////////
//  Build Process                                                    //
///////////////////////////////////////////////////////////////////////
//  Required Files:                                                  //
//    locks.h, locks.cpp                                             //
//                                                                   //
//  Compiler Command:                                                //
//    cl /GX /DTEST_LOCKS locks.cpp                                  //
//                                                                   //
///////////////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    ver 1.4 : 24 Apr 2008
    - added #define WIN32_LEAN_AND_MEAN to ensure no socket link problems
      This prevents windows.h from including wsock.h which clashes with
      wsock2.h that we use.
    ver 1.3 : 04 Apr 2008
    - instrumented to help find bugs in Communicator.  Now removed,
      hopefully without introducing any new bugs.
    ver 1.2 : 03 Feb 2007
    - added synchOut::flush();
    ver 1.1 : 12 Apr 2005
    - moved global definition of sout to locks.cpp
    ver 1.0 : 09 Apr 2005
    - extracted from threads 3.8
*/
//
#define WIN32_LEAN_AND_MEAN
#include <process.h>
#include <Windows.h>
#include <iostream>
//#include <queue>

/////////////////////////////////////////////////////////////////////
//  LLock - local locking class declaration

class LLock
{
  public:
    LLock();
    LLock(const LLock& ll);
    ~LLock();
    LLock& operator=(const LLock& ll);
    void lock();
    void unlock();

  private:
    CRITICAL_SECTION cs;
};

//----< constructor >------------------------------------------------

inline LLock::LLock() { InitializeCriticalSection(&cs); }

//----< copy constructor >-------------------------------------------

inline LLock::LLock(const LLock& ll)
{ 
  InitializeCriticalSection(&cs);  // intentionally same as void ctor
}

//----< destructor >-------------------------------------------------

inline LLock::~LLock() { DeleteCriticalSection(&cs); }

//----< assignment >-------------------------------------------------

inline LLock& LLock::operator =(const LLock& ll)
{
  return *this;  // do nothing
}

//----< set lock >---------------------------------------------------

inline void LLock::lock() { EnterCriticalSection(&cs); }

//----< unset lock >-------------------------------------------------

inline void LLock::unlock() { LeaveCriticalSection(&cs); }

//
/////////////////////////////////////////////////////////////////////
//  GLock<i> - global locking class declaration
//             Please reserve GLock<-1> for use by syncOut

template <int i>
class GLock
{
  public:
    GLock();
    GLock(const GLock&) { InterlockedIncrement(&refCount); }
    ~GLock();
    void lock();
    void unlock();

  private:
  // shared critical section for all GLock<i> objects

    static CRITICAL_SECTION cs;
    static long refCount;
};

//----< initialize static variables >--------------------------

template <int i>
CRITICAL_SECTION GLock<i>::cs;

template <int i>
long GLock<i>::refCount = 0;

//----< default constructor >----------------------------------

template <int i>
GLock<i>::GLock()
{ 
  if(refCount == 0)
    InitializeCriticalSection(&cs);
  InterlockedIncrement(&refCount);
}
//----< destructor >-------------------------------------------

template <int i>
GLock<i>::~GLock()
{ 
  InterlockedDecrement(&refCount);
  if(refCount == 0)
    DeleteCriticalSection(&cs); 
}
//----< set lock >---------------------------------------------

template <int i>
void GLock<i>::lock() { EnterCriticalSection(&cs); }

//----< remove lock >------------------------------------------

template <int i>
void GLock<i>::unlock() { LeaveCriticalSection(&cs); }

//
/////////////////////////////////////////////////////////////////////
// syncOut class

class syncOut
{
public:
  syncOut(std::ostream& out);
  template <typename T>
  syncOut& operator<<(const T& t);
  syncOut& operator<<(syncOut& (*op)(syncOut&));
  template <typename T>
      void operator()(const T& t);
  void flush();

private:
  GLock<-1> _l;
  std::ostream& _out;
};
//----< constructor >------------------------------------------------

inline syncOut::syncOut(std::ostream& out) : _out(out) {}

//----< insertion >--------------------------------------------------

template <typename T>
syncOut& syncOut::operator<<(const T& t)
{
  _l.lock();
  _out << t;
  _out.flush();
  _l.unlock();
  return *this;
}
//----< insertion >--------------------------------------------------

inline syncOut& syncOut::operator<<(syncOut& (*op)(syncOut&))
{
  return (*op)(*this);
}
//----< functor >----------------------------------------------------

template <typename T>
void syncOut::operator()(const T& t)
{
  _l.lock();
  _out << t;
  _out.flush();
  _l.unlock();
}
//----< flush output stream >----------------------------------------

inline void syncOut::flush() { _out.flush(); }

//
//----< lock manipulator >-------------------------------------------

inline syncOut& locker(syncOut& so)
{
  GLock<-1>().lock();
  return so;
}

//----< unlock manipulator >-----------------------------------------

inline syncOut& unlocker(syncOut& so)
{
  GLock<-1>().unlock();
  return so;
}

extern syncOut sout;

//

///////////////////////////////////////////////////////////////
//  class declaration for lockingPtr                         //
///////////////////////////////////////////////////////////////

template <class Obj, class Lock> class lockingPtr {

  public:
    lockingPtr(volatile Obj &obj, Lock &lck);
    ~lockingPtr();
    Obj& operator*();
    Obj* operator->();

  private:
    Obj* _pObj;
    Lock *_pLock;
    lockingPtr(const lockingPtr&);
    lockingPtr& operator=(const lockingPtr&);
};

//----< constructor takes object to lock and Mutex >-----------

template <class Obj, class Lock> inline
lockingPtr<Obj, Lock>::lockingPtr(volatile Obj &obj, Lock &lck) 
             : _pObj(const_cast<Obj*>(&obj)), _pLock(&lck) { 

#ifdef TEST_LOCKINGPTR
  cout << "\n  constructing a LockingPtr object - calls lock()";
  cout.flush();
#endif

  lck.lock(); 
}

//----< destructor >-------------------------------------------

template <class Obj, class Lock> inline
lockingPtr<Obj, Lock>::~lockingPtr() { 
  
  _pLock->unlock(); 

#ifdef TEST_LOCKINGPTR
   cout << "\n  destroying a LockingPtr object - calls unlock()";
   cout.flush();
#endif
}

//

//----< get locked object >------------------------------------

template <class Obj, class Lock> inline
Obj& lockingPtr<Obj, Lock>::operator*() { 
  
#ifdef TEST_LOCKINGPTR
  cout << "\n accessing contents of locked object";
  cout.flush();
#endif

  return *_pObj; 
}

//----< get access to locked object's members >----------------

template <class Obj, class Lock> inline
Obj* lockingPtr<Obj, Lock>::operator->() { 

#ifdef TEST_LOCKINGPTR
  cout << "\n  accessing member of locked object";
  cout.flush();
#endif
  
  return _pObj; 
}

#endif
