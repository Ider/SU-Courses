#ifndef MSGHANDLER_H
#define MSGHANDLER_H
/////////////////////////////////////////////////////////////////////
// MsgHandler.h - Processing for Received Messages                 //
// ver 1.0                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Precision 7500, Windows Vista, SP 1.0       //
// Application:   Utility for CSE687 Project #4                    //
// Author:        Jim Fawcett, Syracuse University, CST 2-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * This module provides two interfaces and three classes:
 *   EndPoint:
 *   - converts ipaddress string and int port to and from a composite
 *     string ipaddress:port.
 *   IMsgHandler:
 *   - interface used by MsgHandler, Communicator, ListenProc, and BlockProc
 *   MsgHandler:
 *   - implements IMsgHandler and translates blocks into message strings
 *   IFileHandler:
 *   - interface used by FileHandler, Communicator, ListenProc, and BlockProc
 *   FileHandler:
 *   - implements IFileHandler and translates blocks to saved files
 */
/*
 *   Build Process:
 *   ==============
 *   Required Files
 *   - MsgHandler.h, MsgHandler.cpp,
 *     Threads.h(cpp), locks.h(cpp), BlockingQueue.h(cpp)
 *     
 *   Compiler Command
 *     cl /EHsc MsgHandler.cpp Threads.cpp locks.cpp BlockingQueue.cpp
 *
 *   Maintenance History:
 *   ====================
 *   ver 1.0 : 26 Apr 2009
 *   - factored out of ICommunicator
  *
 *   Planned Modifications:
 *   ======================
 *   - None
 */

#include <string>
#include <sstream>
#include "BlockingQueue.h"
#include "Threads.h"

/////////////////////////////////////////////////////////////////////
// EndPoint - helps manipulate ip and port

class EndPoint
{
public:
  EndPoint() {}
  EndPoint(const std::string& epStr) : _ipport(epStr) {}
  EndPoint(const std::string& ip, int port);
  std::string getIP();
  int getPort();
  operator std::string () { return _ipport; }
  bool operator ==(const EndPoint& other){return _ipport == other._ipport;}
  std::string toString() { return _ipport; }
private:
  std::string _ipport;
};

struct ICommunicator;

class IMsgHandler
{
public:
//  static IMsgHandler* Create(Thread_Processing* pProc);
  virtual void postMessage(std::string& msg)=0;
  virtual IMsgHandler* clone()=0;
  virtual BQueue<std::string>* getQueue()=0;
  virtual void start()=0;
  virtual EndPoint getEndPoint()=0;
  virtual void setCommunicator(ICommunicator* pComm)=0; 
  virtual ICommunicator* getCommunicator()=0;
};

class Block;

class IFileHandler
{
public:
  //static IFileHandler* Create(Thread_Processing* pProc);
  virtual void postFileName(std::string& msg)=0;
  virtual void postFileBlock(Block* pBlock)=0;
  virtual IFileHandler* clone()=0;
  virtual BQueue<std::string>* getQueue()=0;
  virtual void start()=0;
  virtual EndPoint getEndPoint()=0;
  virtual void setCommunicator(ICommunicator* pComm)=0;
  virtual ICommunicator* getCommunicator()=0;
  virtual void setFileDestination(const std::string& path)=0;
};

/////////////////////////////////////////////////////////////////////
// MsgHandler
//   - template argument is type of receiver thread proc
//   - extracts and stores remote endpoint from first message
//   - provides hooks for receiver thread procs
//   - runs on BlockProc thread, spawned by listener

template <typename Proc>
class MsgHandler : public IMsgHandler
{
public:
  MsgHandler() : _pComm(0)
  {
    // shares these with its receiver thread proc
    lock.lock();
    _pBQ = new BQueue<std::string>();
    _pProc = new Proc(this);
    _pThrd = new Thread<terminating_thread>(*_pProc);
    lock.unlock();
  }
  MsgHandler(const MsgHandler& mh)
  {
    lock.lock();
    _pBQ = new BQueue<std::string>();
    _pProc = new Proc(this);
    _pThrd = new Thread<terminating_thread>(*_pProc);
    _pComm = mh._pComm;
    lock.unlock();
  }
  ~MsgHandler()
  {
    lock.lock();
    delete _pBQ;
    delete _pProc;
    // - thread deletes itself
    // - don't own communicator
    lock.unlock();
  }
  /////////////////////////////////////////////////////////////////////
  // Each client gets its own MsgHandler with a deep clone like this:

  IMsgHandler* clone() 
  { 
    return new MsgHandler(*this); 
//    return new MsgHandler(); 
  }

  /////////////////////////////////////////////////////////////////////
  // Clients share a single MsgHandler with a shallow clone line this:
  // IMsgHandler* clone() { return this; }

  BQueue<std::string>* getQueue() { return _pBQ; }

  // called by BlockProc after it attaches this instance
  void start() { _pThrd->start(); }

  // called by BlockProc at the end of a message block sequence
  void postMessage(std::string& msg)
  {
    size_t pos = msg.find('@');
    lock.lock();
    _remoteEp = msg.substr(0,pos);
    lock.unlock();
    msg = msg.substr(pos+1);
    _pBQ->enQ(msg);
  }
  EndPoint getEndPoint() 
  { 
    std::string temp;
    lock.lock();
    temp = _remoteEp;
    lock.unlock();
    return temp;
  }
  void setCommunicator(ICommunicator* pComm) 
  {
    lock.lock();
    _pComm = pComm;
    lock.unlock();
  }
  ICommunicator* getCommunicator() { return _pComm; }
private:
  GLock<1> lock;
  std::string _msg;
  BQueue<std::string>* _pBQ;
  Proc* _pProc;
  Thread<terminating_thread>* _pThrd;
  EndPoint _remoteEp;
  ICommunicator* _pComm;
};

//IMsgHandler* IMsgHandler::Create(Thread_Processing* pProc)
//{
//  return new MsgHandler
//}
/////////////////////////////////////////////////////////////////////
// FileHandler
//   - template argument is type of receiver thread proc
//   - extracts and stores remote endpoint from first message
//   - provides hooks for receiver thread procs
//   - runs on BlockProc thread, spawned by listener

template <typename Proc>
class FileHandler : public IFileHandler
{
public:
  typedef char byte_;
  FileHandler() : pBuffer(0), _pComm(0)
  {
    // shares these with its receiver thread proc
    lock.lock();
    _pBQ = new BQueue<std::string>();
    _pProc = new Proc(this);
    _pThrd = new Thread<terminating_thread>(*_pProc);
    _path = ".\\debug\\received\\";
    lock.unlock();
  }
  FileHandler(const FileHandler& fh) : pBuffer(0)
  {
    lock.lock();
    _pBQ = new BQueue<std::string>();
    _pProc = new Proc(this);
    _pThrd = new Thread<terminating_thread>(*_pProc);
    _path = fh._path;
    _pComm = fh._pComm;
    lock.unlock();
  }
  ~FileHandler()
  {
    lock.lock();
    delete _pBQ;
    delete _pProc;
    // - thread deletes itself
    // - don't own communicator
    lock.unlock();
    delete [] pBuffer; // ok to delete pointer with zero value
  }
  /////////////////////////////////////////////////////////////////////
  // Each client gets its own MsgHandler with a deep clone like this:

  IFileHandler* clone() { 
    return new FileHandler(*this); 
  }
  //IFileHandler* clone() { return new FileHandler(); }

  /////////////////////////////////////////////////////////////////////
  // Clients share a single FileHandler with a shallow clone line this:
  // IFileHandler* clone() { return this; }

  BQueue<std::string>* getQueue() { return _pBQ; }

  // called by BlockProc after it attaches this instance
  void start() { _pThrd->start(); }

  // called by BlockProc for first block
  void postFileName(std::string& msg)
  {
    size_t pos = msg.find('@');
    lock.lock();
    _remoteEp = msg.substr(0,pos);
    msg = msg.substr(pos+1);
    msg = _path + msg;
    lock.unlock();
    writeBuff.open(msg.c_str(), std::ios::out | std::ios::binary | std::ios::trunc);
    if(!writeBuff.is_open())
    {
      msg = std::string("\n  Can't open ") + msg + "\n";
    }
    _pBQ->enQ(msg);
  }

  void postFileBlock(Block* pBlock)
  {
    if(pBuffer == 0)
    {
      size_t BlkSize = _pComm->getBlockSize();
      pBuffer = new byte_[BlkSize];
    }
    if(writeBuff.is_open())
    {
      if(pBlock->getState() == Block::end_message)
      {
        pBlock->copyDataFromBlock(pBuffer,pBlock->sizeOfData());
        writeBuff.sputn(pBuffer,pBlock->sizeOfData());
        writeBuff.close();
      }
      else
      {
        pBlock->copyDataFromBlock(pBuffer,pBlock->sizeOfData());
        writeBuff.sputn(pBuffer,pBlock->sizeOfData());
      }
    }
  }
  EndPoint getEndPoint() { return _remoteEp; }
  void setCommunicator(ICommunicator* pComm) 
  {
    lock.lock();
    _pComm = pComm; 
    lock.unlock();
  }
  ICommunicator* getCommunicator() { return _pComm; }
  void setFileDestination(const std::string& path)
  { 
    lock.lock();
    _path = path;
    lock.unlock();
  }
private:
  GLock<1> lock;
  std::string _msg;
  std::filebuf writeBuff;
  byte_* pBuffer;
  BQueue<std::string>* _pBQ;
  Proc* _pProc;
  Thread<terminating_thread>* _pThrd;
  std::string _path;
  EndPoint _remoteEp;
  ICommunicator* _pComm;
};

#endif
