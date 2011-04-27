#ifndef SOCKETCOMMUNICATOR
#define SOCKETCOMMUNICATOR
/////////////////////////////////////////////////////////////////////
// Communicator.h - Uses sockets and blocks to send messages       //
// ver 2.7                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Precision 7500, Windows Vista, SP 1.0       //
// Application:   Utility for CSE687 Project #4                    //
// Author:        Jim Fawcett, Syracuse University, CST 2-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * This module provides three classes that users will touch (see test
 * stub for details):
 *   Communicator:
 *   - runs socket listener on its own thread so applications don't
 *     block waiting for connections
 *   - Supports connecting, listening, sending Blocks and receiving
 *     Blocks.
 *   - Each served client gets its own block processing thread that
 *     converts a block stream into enqueued messages and/or files.
 *     Application will probably provide an additional thread to read
 *     each message and carry out requested processing.
 *   MsgReceive_Proc:
 *   - defines application specific processing performed by the receiver
 *     of messages
 *   FileReceive_Proc:
 *   - defines processing performed by the receiver of files.
 *
 * This Module also defines two other modules that are infrastructure,
 * not touched by most users.
 *   BlockProc:
 *   - receives blocks from a remote socket, and enqueues them.
 *   listenProc:
 *   - uses listener socket to accept connections, and for each,
 *     spawn a thread, using BlockProc, to handle the connection.
 */
/*
 *   Build Process:
 *   ==============
 *   Required Files
 *   - Communicator.h(cpp), Sockets.h(cpp), BlockHandler.h(cpp),
 *     BlockingQueue.h(cpp), Threads.h(cpp), locks.h(cpp),
 *     MsgHandler.h(cpp), ICommunicator.h
 *     
 *   Compiler Command
 *     cl /EHsc Communicator.cpp Sockets.cpp BlockHandler.cpp \
 *              BlockingQueue.cpp Threads.cpp locks.cpp \
 *              MsgHandler.cpp wsock32.lib user32.lib
 *
 *   Maintenance History:
 *   ====================
 *   ver 2.7 : 05 May 2009
 *   - fixed bug, found by Phil Pratt-Szeliga, in 
 *     SocketListener::WaitForConnection() due to allowing a
 *     client handling thread to be created with an invalid socket.
 *     That was fixed in SocketListener::WaitForConnect().
 *   ver 2.6 : 26 Apr 2009
 *   - fixed a bug identified by Karthik Partibhan, due to a missed 
 *     clone operation in listenProc::run()
 *   ver 2.5 : 26 Apr 2009
 *   - fixed bug with file send and receive directory paths
 *   - factored out MsgHandler.h(cpp)
 *   ver 2.4 : 25 Apr 2009
 *   - fixed bug in file transfer, reported by Vinay Vasyani, due to
 *     missing last byte of file.  Fix in Communicator::PostFile in
 *     the area send data blocks, in Communicator.cpp.
 *   - have not found a satisfactory solution for file directory
 *     path setting.  Will continue to look at that this weekend.
 *   - started a WinForm demo using SocketCommunicator - still has
 *     significant code to add.
 *   ver 2.3 : 23 Apr 2009
 *   - fixed bug that caused linking errors with modules that use
 *     Communicator by moving two static initializations from
 *     Communicator.h to Communicator.cpp.  This problem was caused
 *     by changing Communicator from template to non-template class.
 *   ver 2.2 : 22 Apr 2009
 *   - made cosmetic changes to these comments
 *   ver 2.1 : 22 Apr 2009
 *   - fixed bug in file handling
 *   ver 2.0 : 21 Apr 2009
 *   - removed map of queues
 *   - now, each client gets:
 *       - a block processor running on a child thread
 *       - a MsgReceive_Proc running on a child thread
 *       - a FileReceive_Proc running on a child thread
 *     many of the templates are no longer needed as the map is gone
 *   ver 1.3 : 04 Apr 2008
 *   - simplified (believe it or not) the structure of communicator.
 *   - fixed bug in test stub that allowed process to exit before
 *     worker thread completed.
 *   - removed MessageHandler, including its AccumulateData function,
 *     cited below.
 *   ver 1.2 : 27 Mar 2007
 *   - fixed another bug in AccumulateData, by replacing 1 with i 
 *     in the next to last statement.  Again, spotted by Estepan.
 *   ver 1.1 : 26 Mar 2007
 *   - fixed BuffSize bug in AccumulateData, found by Avinash Bhat 
 *     and Estepan Melikasetian
 *   ver 1.0 : 18 Feb 2007
 *   - first release
 *
 *   Planned Modifications:
 *   ======================
 *   - Support configuration at load time of parameters like:
 *     - number of connect retries
 *     - number of accept retries (zero to always)
 *   - Provide Block pool to avoid so many Block creations and 
 *     fragmenting of the heap
 *   - Add notification, using the Command Pattern, to let
 *     listener tell user when a new connection has been made.
 *     This has been started with the notify Command object.
 *   - Support for IPv6
 */
#include "Sockets.h"
#include "BlockHandler.h"
#include "Threads.h"
#include "BlockingQueue.h"
#include "Command.h"
#include "ICommunicator.h"
#include <fstream>
#include <string>

enum { BlockSize = 1024 };

class Communicator;

/////////////////////////////////////////////////////////////////////
// class BlockProc
// - provides processing for child thread spawned by listener
//   to handle all blocks in a message
// - clone is required to allow listener thread to make a copy
//   to avoid catastrophic overwriting in listener loop
// - run is where the action is, reading blocks out of the
//   socket, passed by listenProc when spawning a new clienthandling
//   thread.  It then calls its MessageProcessor process function.
// - Note: Exception handling is deferred to application code

class BlockProc : public Thread_Processing<BlockProc>
{
public:
  typedef void (*Process)(Block*);

  BlockProc(SOCKET s) 
    : _socket(s), _clientId(""), _pMsgHandler(0), _pFileHandler(0) {}

  BlockProc(const BlockProc& bp) 
    : _socket(bp._socket), _clientId(bp._clientId), _pMsgHandler(bp._pMsgHandler), _pFileHandler(bp._pFileHandler) {}

  virtual void run();
  void attachMsgHandler(IMsgHandler* pMsgHandler);
  void attachFileHandler(IFileHandler* pFileHandler);
  void handleMsgBlock(Block* pBlk);
  void handleFileBlock(Block* pBlk);

//  static Invoker<EndPoint> notify;

private:
  GLock<1> lock;
  SOCKET _socket;
  std::string _clientId;
  IMsgHandler* _pMsgHandler;
  IFileHandler* _pFileHandler;
};

/////////////////////////////////////////////////////////////////////
// class listenProc:
// - provides processing for listener thread
// - clone function is required to allow thread to make a copy
// - registerMP accepts a MessageProcessor to pass on to the
//   BlockProc instance it creates, as a constructor argument
// - run provides a forever loop to listen for connections

class listenProc : public Thread_Processing<listenProc>
{
public:
  listenProc(SocketListener* pListener) 
    : _pListener(pListener), _pMsgHandler(0), _pFileHandler(0) {}
  listenProc(const listenProc& lp) 
    : _pListener(lp._pListener), _pMsgHandler(lp._pMsgHandler), _pFileHandler(lp._pFileHandler) {}

  void attachMsgHandler(IMsgHandler* pMsgHandler) { _pMsgHandler = pMsgHandler; }
  void attachFileHandler(IFileHandler* pFileHandler) { _pFileHandler = pFileHandler; }
  virtual void run();
private:
  SocketListener* _pListener;
  IMsgHandler* _pMsgHandler;
  IFileHandler* _pFileHandler;
};


class Communicator : public ICommunicator
{
public:
  Communicator(EndPoint localEp, int BlkSize=1024) 
    : _listener(localEp.getPort()), _localEp(localEp), _pMsgHandler(0), _pFileHandler(0) 
  {
    _BlkSize = BlkSize;
    _path = ".\toSend";
  }
  
  // listening for connections
  bool listen();
  void stop() { _listener.stop(); }

  // connecting
  bool connect(const std::string& ip, int port);
  void disconnect();
  Socket& getConnector() { return _connector; }
  long getSocketConnectionCount();  // from connector
  long getInvalidSocketCount();     // from listener

  // sending messages and files
  void postMessage(const std::string& msg);
  void postFile(const std::string& fileName);
  void setFileSource(const std::string& path);

  // attach receive handlers for messages and files
  void attachMsgHandler(IMsgHandler* pMsgHandler);
  void attachFileHandler(IFileHandler* pFileHandler);

  // block handling
  size_t getBlockSize();
  bool postBlock(Block* pBlock);
  Block* getBlock(const std::string& id, bool wait=true);
  Block* startMsgBlock(EndPoint ep, Block::Type type, size_t BlkSize=_BlkSize);
  Block* midMsgBlock(Block::Type type, byte_* pData, size_t DataSize, size_t BlkSize=_BlkSize);
  Block* endMsgBlock(Block::Type type, byte_* pData=0, size_t DataSize=0, size_t BlkSize=_BlkSize);
  Block* closeDlgBlock(size_t BlkSize=_BlkSize);
  Block* closeConnBlock(size_t BlkSize=_BlkSize);
  
private:
  Socket _connector;
  SocketListener _listener;
  IMsgHandler* _pMsgHandler;
  IFileHandler* _pFileHandler;
  GLock<1> lock;
  std::string _path;
  EndPoint _localEp;
  static size_t _BlkSize;
};

inline long Communicator::getInvalidSocketCount()
{
  return _listener.getInvalidSocketCount();
}

inline long Communicator::getSocketConnectionCount()
{
  return _connector.getSocketConnectionCount();
}

//----< return size of socket blocks >-------------------------------

inline size_t Communicator::getBlockSize() { return _BlkSize; }

//----< set path to file source >------------------------------------

inline void Communicator::setFileSource(const std::string& path)
{
  _path = path;
}
//----< attempt to connect to a listener >---------------------------

inline bool Communicator::connect(const std::string& ip, int port)
{
  return _connector.connect(ip,port);
}
////----< break connection >-------------------------------------------

inline void Communicator::disconnect()
{
  _connector.disconnect();
}
//----< make start msg block on heap >-------------------------------

inline Block* Communicator::startMsgBlock(EndPoint endpoint, Block::Type type, size_t BlkSize)
{
  std::string ep = endpoint.toString();
  return Block::makeHeapBlock(
    BlkSize,type,Block::address,(byte_*)ep.c_str(),ep.size()+1
  );
}
//----< make mid msg block on heap >---------------------------------

inline Block* Communicator::midMsgBlock(Block::Type type, byte_* pData, size_t DataSize, size_t BlkSize)
{
  return Block::makeHeapBlock(
    BlkSize,type,Block::partial_message,pData,DataSize+1
  );
}
//----< make msg end block on heap >---------------------------------

inline Block* Communicator::endMsgBlock(Block::Type type, byte_* pData, size_t DataSize, size_t BlkSize)
{
  return Block::makeHeapBlock(BlkSize,type,Block::end_message,pData,DataSize+1);
}
//----< make ending block on heap >----------------------------------

inline Block* Communicator::closeDlgBlock(size_t BlkSize)
{
  return Block::makeHeapBlock(BlkSize,Block::message,Block::end_dialog,0,1);
}
//----< make closing block on heap >---------------------------------

inline Block* Communicator::closeConnBlock(size_t BlkSize)
{
  return Block::makeHeapBlock(BlkSize,Block::message,Block::end_connection,0,1);
}

inline void Communicator::attachMsgHandler(IMsgHandler* pMsgHandler)
{
  lock.lock();
  _pMsgHandler = pMsgHandler;//->clone();
  _pMsgHandler->setCommunicator(this);
  lock.unlock();
}

inline void Communicator::attachFileHandler(IFileHandler* pFileHandler)
{
  lock.lock();
  _pFileHandler = pFileHandler;//->clone();
  _pFileHandler->setCommunicator(this);
  lock.unlock();
}

#endif
