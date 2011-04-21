#ifndef ICOMMUNICATOR_H
#define ICOMMUNICATOR_H 
/////////////////////////////////////////////////////////////////////
// ICommunicator.h - Interface for users of Communicator class     //
// ver 1.2                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Precision 7500, Windows Vista, SP 1.0       //
// Application:   Utility for CSE687 Project #4                    //
// Author:        Jim Fawcett, Syracuse University, CST 2-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * This module provides one interface:
 *   ICommunicator:
 *   - provides Communicator abstraction for clients so they don't 
 *     couple to any of the socket implementation.
 */
/*
 *   Build Process:
 *   ==============
 *   Required Files
 *   - ICommunicator
 *     
 *   Compiler Command
 *     none
 *
 *   Maintenance History:
 *   ====================
 *   ver 1.2 : 05 May 2009
 *   - added InvalidSocketCount() and SocketConnectionCount()
 *   ver 1.1 : 26 Apr 2009
 *   - cosmetic changes to these comments
 *   ver 1.0 : 25 Apr 2009
 *   - factored out of Communicator
  *
 *   Planned Modifications:
 *   ======================
 *   - None
 */

#include <string>
#include "MsgHandler.h"
#include "BlockingQueue.h"
#include "Threads.h"

struct ICommunicator
{
  static ICommunicator* Create(EndPoint ep, size_t BlkSize=1024);
  virtual bool listen()=0;
  virtual void stop()=0;

  // connecting
  virtual bool connect(const std::string& ip, int port)=0;
  virtual void disconnect()=0;
  virtual long getSocketConnectionCount()=0;  // from connector
  virtual long getInvalidSocketCount()=0;     // from listener

  // sending messages and files
  virtual void postMessage(const std::string& msg)=0;
  virtual void postFile(const std::string& fileName)=0;
  virtual void setFileSource(const std::string& path)=0;

  // attach receive handlers for messages and files
  virtual void attachMsgHandler(IMsgHandler* pMsgHandler)=0;
  virtual void attachFileHandler(IFileHandler* pFileHandler)=0;

  virtual size_t getBlockSize()=0;
};

#endif
