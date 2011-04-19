#ifndef THREAD_H
#define THREAD_H
/////////////////////////////////////////////////////////////////////////
// Threads.h   -  Wraps Win32 threads, providing a simple interface    //
// ver 6.3        similar to the .Net Thread class                     //
//                                                                     //
// Language:      Visual C++, ver 8.0                                  //
// Platform:      Dell Dimension 9150, Windows XP Pro, SP2             //
// Application:   Demo for CSE687 - Object Oriented Design             //
// Author:        Jim Fawcett, Syracuse University, CST 2-187          //
//                jfawcett@twcny.rr.com, (315) 443-3948                //
/////////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * This module provides two thread classes, Thread<default_thread> and
 * Thread<terminating_thread>, and an abstract Thread_Processing class, 
 * that both wrap native Win32 threads.
 *
 *   Thread<default_thread>     - may be created on either stack or heap
 *   - This thread type uses a pointer to its processing object, derived
 *     from Thread_Processing, so your application must not overwrite that
 *     object.
 *   - The module provides a typedef Thread<default_thread> thread to
 *     provide a shorter alias for this common case.
 *
 *   Thread<terminating_thread> - must be created on heap 
 *   - This thread type will call delete on itself when its thread
 *     processing has completed, so it must be created on the heap.
 *   - It makes a clone of its processing object, derived from 
 *     Thread_Processing object, so it does not matter whether the 
 *     original is overwritten.
 *   - This thread will delete its processing object when that
 *     processing is complete.
 *   - Don't use non-static member functions of this class after
 *     calling start, as its destruction is non-deterministic.
 *   The design of this class supports a "Fire and Forget" model.
 *   Threads and Thread_Processing objects reside on the heap, and
 *   destroy themselves as soon as their processing completes.
 *
 *   Thread_Processing - an abstract base class
 *   - Your application overrides this base to define application 
 *     specific thread processing:
 *       class MyProc : public Thread_Processing { ... }.
 *   - The class forces you to override two functions:
 *       MyProc* clone() { return new MyProc(*this); }
 *       void run() { // application specific code }
 *
 *  Note that assignment and copy operations are disabled for the Thread
 *  classes, but are permitted for instances of the Thread_Processing class
 *  and its derived classes.
 */
//
/* Public Interface (see test stub for details):
 * =============================================
 *
 * // create thread on local stack
 *
 * class threadProc : public Thread_Processing { ... }
 *                            // create instance of thread_processing object
 * thread t(threadProc);      // create thread with clone of threadProc
 * t.start();                 // start thread running
 * t.suspend();               // suspend thread until resume()'d
 * t.resume();                // resume thread operation after suspend()'d
 * t.sleep(100);              // sleep for 100 millisecond
 * t.setPriority(very_high);  // set thread priority to highest level
 * t.wait();                  // caller waits for thread t to terminate
 *
 * // create self-destructing thread on heap
 * // - Note: after calling start(), you must not call non-static
 * //         members, as the thread will delete itself at some
 * //         non-deterministic time.
 *
 * Thread<terminating_thread>* pTT 
 *   = new Thread<terminating_thread>(threadProc);
 * HANDLE tHandle = pTT->handle();      // get handle for wait before starting
 * pTT->start();                                    // start thread running
 *   // do some processing, then:
 * Thread<terminating_thread>::wait(tHandle);       // static wait for thread
 * 
 */
/* Build Process
 * =============
 * Required Files:
 * - Threads.h, Threads.cpp,  // always required
 * - Locks.h, Locks.cpp       // required for test stub and many apps
 *
 * Build Command:
 * - cl /EHcs /DTEST_THREADS threads.cpp locks.cpp
 *
 * Maintenance History:
 * ====================
 * ver 6.3 : 08 Apr 10
 * - moved clone code into non-virtual base class.  Now, derived classes
 *   don't need to (and should not) provide a clone() member function.
 * ver 6.2 : 08 Apr 10
 * - decide in haste ==> repent at leasure
 * - The last "bug" fixed introduced an error by "fixing" a non-bug, sigh!
 * - delete this should NOT be in thread destructor.  The correct deletion was
 *   already in threadproc, just after the call to run().  When that call
 *   completes, the Win32 thread has expired and it's time to clean up.  There
 *   we correctly call delete pSelf.
 * ver 6.1 : 07 Apr 10
 * - added delete this to thread destructor for terminating_thread
 * ver 6.0 : 03 Feb 07
 * - This is a major rewrite of the Threads module designed to 
 *   simplify its implementation and use.
 * - Earlier maintenance history has been truncated, as no longer
 *   relevant.
 */
//
#include <process.h>
#include <windows.h>

///////////////////////////////////////////////////////////////////
// Classes derived from IThread_Processing, indirectly through
// class Thread_Processing, define code that created thread executes.
// The derived processing class must have correct copy semantics.

struct IThread_Processing
{
  virtual IThread_Processing* clone() = 0;
  virtual void run() = 0;
};

template<typename myDerived>
class Thread_Processing : public IThread_Processing
{
public:
  virtual ~Thread_Processing() {}
  IThread_Processing* clone() 
  {
    myDerived* pMyDerived = dynamic_cast<myDerived*>(this);
    if(pMyDerived == 0)
      throw std::exception("class must derive from Thread_Processing<DerivedType>");
    return new myDerived(*pMyDerived);
  }
};

/////////////////////////////////////////////////////////////
// Template parameter for thread class, determines 
// termination behavior
//
enum thread_type 
{ 
  default_thread,       // no self destruction
  terminating_thread    // will delete itself when thread is done
};

/////////////////////////////////////////////////////////////
// wrap most of the Win32 thread prioritites
//
enum thread_priority { very_low, low, normal, high, very_high };

//
/////////////////////////////////////////////////////////////
// class Thread<thread_type> wraps Win32 threads
//

template <thread_type type>
class Thread
{
public:
  Thread(IThread_Processing& p);
  ~Thread();
  void start();
  void wait();
  static void wait(HANDLE tHandle);
  unsigned long id();
  HANDLE handle();
  void sleep(long Millisecs);
  void suspend();
  void resume();
  thread_priority getPriority();
  void setPriority(thread_priority p);
  void endThread(unsigned int exit_code);
private:
  IThread_Processing* pProc;
  HANDLE hThread;
  static unsigned int __stdcall threadProc(void *pSelf);
  unsigned int _threadID;
  thread_priority _priority;
  // disable copy and assignment
  Thread(const Thread<type>& t);
  Thread<type>& operator=(const Thread<type>& t);
};

/////////////////////////////////////////////////////////////
// alias for default thread
//
typedef Thread<default_thread> thread;
typedef Thread<terminating_thread> tthread;

//
//----< new Thread object holds copy of Thread_Processing object >-------
//
//  p.clone creates, on heap, a copy of class
//  derived from Thread_Processing object
//
template <thread_type type>
Thread<type>::Thread(IThread_Processing& p) 
            : hThread(NULL), _priority(normal) 
{
  if(type == default_thread)
    pProc = &p;
  else
    pProc = p.clone();
  hThread = (HANDLE)_beginthreadex
            (
              NULL,             // default security properties
              0,                // default stack size
              threadProc,       // thread processing function uses pProc
              (void*)this,      // pointer to me
              CREATE_SUSPENDED, // create thread in suspended state
              &_threadID        // identifier assigned by OS
            );
  
}

//----< destroy thread and its Thread_Processing object >----------------

template <thread_type type>
Thread<type>::~Thread()
{
  CloseHandle(hThread);   // cleanup Win32 resource
  if(type == terminating_thread)
  {
    delete pProc;         // delete clone of thread_processing object
  }
}
//----< return Win32 thread id >-----------------------------------------

template <thread_type type>
unsigned long Thread<type>::id() { return _threadID; }

//----< start Win32 thread running >-------------------------------------

template <thread_type type>
void Thread<type>::start()
{
  ResumeThread(hThread);  // start it running
}
//----< Win32 thread processing wrapper for process object >-------------

template <thread_type type>
unsigned int __stdcall Thread<type>::threadProc(void *pSelf)
{
  ((Thread<type>*)pSelf)->pProc->run();  // child's synchronous call
  if(type == terminating_thread)
  {
    delete pSelf;   // must not access member data after calling start(),
  }                 // as time of destruction is non-deterministic
  return 0;
}
//
//----< wait for thread to terminate >-----------------------------------

template <thread_type type>
void Thread<type>::wait()
{
  WaitForSingleObject(hThread,INFINITE);
}
//----< wait for thread to terminate >-----------------------------------

template <thread_type type>
void Thread<type>::wait(HANDLE hThread)
{
  WaitForSingleObject(hThread,INFINITE);
}
//----< return Win32 Thread handle >-------------------------------------

template <thread_type type>
HANDLE Thread<type>::handle()
{
  return hThread;
}
//----< set thread priority >--------------------------------------------

template <thread_type type>
void Thread<type>::setPriority(thread_priority p)
{ 
  _priority = p; 
  switch(_priority)
  {
  case very_high:
    SetThreadPriority(hThread,THREAD_PRIORITY_HIGHEST);
    break;
  case high:
    SetThreadPriority(hThread,THREAD_PRIORITY_ABOVE_NORMAL);
    break;
  case normal:
    SetThreadPriority(hThread,THREAD_PRIORITY_NORMAL);
    break;
  case low:
    SetThreadPriority(hThread,THREAD_PRIORITY_BELOW_NORMAL);
    break;
  case very_low:
    SetThreadPriority(hThread,THREAD_PRIORITY_LOWEST);
    break;
  }
}
//
//----< get thread priority >--------------------------------------------

template <thread_type type>
thread_priority Thread<type>::getPriority() { return _priority; }

//----< put thread to sleep >--------------------------------------------

template <thread_type type>
void Thread<type>::sleep(long Millisecs) { Sleep(Millisecs); }

//----< suspend thread >-------------------------------------------------

template <thread_type type>
void Thread<type>::resume() { ResumeThread(hThread); }

//----< suspend thread >-------------------------------------------------

template <thread_type type>
void Thread<type>::suspend() { SuspendThread(hThread); }

//----< terminate thread >-----------------------------------------------
//
// It is usually a good idea to avoid calling this function, as it will
// abruptly terminate thread processing, not calling any cleanup code
// you may have put into Thread_Processing::run().

template <thread_type type>
void Thread<type>::endThread(unsigned int exit_code)
{ 
  _endthreadex(exit_code); 
}

#endif
