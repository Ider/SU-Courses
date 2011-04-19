#ifndef BLOCKINGQUEUE_H
#define BLOCKINGQUEUE_H
/////////////////////////////////////////////////////////////////////
//  blockingQueue.cpp - queue that blocks on deQ of empty queue    //
//  ver 1.2                                                        //
//  Language:       Visual C++, ver 7.1, SP 2                      //
//  Platform:       Dell Dimension 8300, Win XP Pro, SP2           //
//  Application:    CSE687 - Object Oriented Design                //
//  Author:         Jim Fawcett, CST 2-187, Syracuse Univ          //
//                  (315) 443-3948, jfawcett@twcny.rr.com          //
//                                                                 //
/////////////////////////////////////////////////////////////////////
/*
    Module Operations
    =================
    This module provides a simple thread-safe blocking queue, based 
    on the STL queue container adapter.  When a client thread attempts
    to deQ an empty queue, it will block until another thread enQs an
    item.  This prevents very high CPU utilization while a reading
    thread spin locks on an empty queue.

    Public Interface
    ================
    BQueue<std::string> Q       // create blocking queue holding std::strings
    Q.enQ("an item");           // push onto queue
    std::string str = Q.deQ();  // pop from queue
    size_t s = Q.size();        // number of elements in queue
    Q.clear()                   // remove all contents from queue
*/      
//
///////////////////////////////////////////////////////////////////////
//  Build Process                                                    //
///////////////////////////////////////////////////////////////////////
//  Required Files:                                                  //
//    blockingQueue.h, blockingQueue.cpp                             //
//                                                                   //
//  Compiler Command:                                                //
//    cl /GX /DTEST_BLOCKINGQUEUE blockingQueue.cpp                  //
//                                                                   //
///////////////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    ver 1.2 : 11 Apr 2010
    - added std:: qualifer to exception in both constructors
    ver 1.1 : 03 Feb 2007
    - simplified deQ() function, removing waitflag
    ver 1.0 : 09 Apr 2005
    - extracted from threads ver 3.8
    ver 3.7 : 08 May 2004
    - fixed a subtle bug in the blocking queue.  Added a second check
      to the deQ locking test.  See deQ prologue for details.
    ver 3.6 : 01 May 2004
    - fixed blocking queue, BQueue<T>::clear() function which called a 
      non-existing std::queue<T> function, discovered by Arun Iyer.  
    - added copy ctors and assignment operators to LLock and BQueue<T>
      classes.

*/
//
#include <process.h>
#include <Windows.h>
#include <iostream>
#include <queue>
#include "..\threads\locks.h"

/////////////////////////////////////////////////////////////////////
//  BQueue<T> class declaration - blocking queue based on STL queue

template <typename T>
class BQueue
{
public:
  BQueue();
  BQueue(const BQueue<T>& bq);
  ~BQueue();
  BQueue<T>& operator=(const BQueue<T>& Q);
  void enQ(const T& t);
  T deQ();
  void clear();
  size_t size();
private:
  std::queue<T> _Q;
  LLock _l;
  HANDLE _hEvent;
};
//----< constructor >------------------------------------------------

template <typename T>
BQueue<T>::BQueue()
{
  _hEvent = CreateEvent(0,FALSE,TRUE,0);
  if(_hEvent==NULL)
    throw std::exception("CreateEvent failed in BQueue<T>::BQueue()");
}
//----< copy constructor >-------------------------------------------

template <typename T>
BQueue<T>::BQueue(const BQueue<T>& bq) : _Q(bq._Q)
{
  _hEvent = CreateEvent(0,FALSE,TRUE,0);
  if(_hEvent==NULL)
    throw std::exception("CreateEvent failed in BQueue<T>::BQueue()");
}
//----< destructor >-------------------------------------------------

template <typename T>
BQueue<T>::~BQueue() { CloseHandle(_hEvent); }

//----< assignment >-------------------------------------------------

template <typename T>
BQueue<T>& BQueue<T>::operator =(const BQueue<T>& bq)
{
  if(this==&bq) return *this;
  _Q = bq._Q;
  SetEvent(_hEvent);
  return *this;
}
//
//----< enqueue >----------------------------------------------------

template <typename T>
void BQueue<T>::enQ(const T& t)
{
  _l.lock();
  _Q.push(t);
  SetEvent(_hEvent);
  _l.unlock();
}
//----< dequeue >----------------------------------------------------

template <typename T>
T BQueue<T>::deQ()
{
  T msg;
  while(true)
  {
    _l.lock();
    if(_Q.size() != 0)
    {
      msg = _Q.front();
      _Q.pop();
      _l.unlock();
      break;
    }
    ResetEvent(_hEvent);
    _l.unlock();
    WaitForSingleObject(_hEvent,INFINITE);
  }
  return msg;
}
//
//----< purge queue >------------------------------------------------

template <typename T>
void BQueue<T>::clear()
{ 
  while(_Q.size() > 0)
    _Q.pop();
}

//----< return number of elements in queue >-------------------------

template <typename T>
size_t BQueue<T>::size() { return _Q.size(); }

#endif
