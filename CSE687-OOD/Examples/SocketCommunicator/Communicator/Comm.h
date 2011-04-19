#ifndef COMM_H
#define COMM_H
/////////////////////////////////////////////////////////////////////
// Comm.h      -  Enables sending Messages between machines        //
// ver 1.2                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Dimension T7400, Win 7 Pro                  //
// Application:   Utility for CSE687 projects                      //
// Author:        Jim Fawcett, Syracuse University, CST 4-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////
/*
   Package Operations:
   ===================
   This package provides network communication services, using 
   WinSock2, a nearly Berkley Sockets compliant implementation
   with extensions.  Four classes are provided:

   EndPoint:
   ---------
   Puts address information into and pulls out of strings of the form:
   127.0.0.1:8000

   Message:
   --------
   Supports defining instances that hold type strings - either "text"
   or "file", EndPoints, and a text body.  Messages have the ability to
   serialize themselves into XML strings and to deserialize a properly
   formatted XML string into a Message.

   Sender:
   -------
   Supports connecting and posting messages to a remote EndPoint.

   Receiver:
   ---------
   Starts a listener that waits for connections, then starts a receive
   thread, for each connection, that frames XML Message strings into
   Message instances and enqueues them.  It provides a GetMsg() function
   that retrieves messages from the queue.

   Public Interface:
   =================
   EndPoint ep("127.0.0.1",8000);
   Receiver rcvr(8000);
   Sender sndr;
   sndr.connect(ep);
   Message msg("this is a msg body",ep,"text");
   sndr.PostMsg(msg);
   sndr.wait();
   Message rMsg = rcvr.GetMsg();
*/
/*
   Build Process:
   ==============
   Required Files:
     Comm.h, Comm.cpp, Sockets.h, Sockets.cpp, locks.h, locks.cpp
     Threads.h, Threads.cpp, BlockingQ.h, BlockingQ.cpp,
     XmlDocument.h, XmlNodes.h, MTree.h, XmlElementParts.h, ITokenCollection,
     XmlDocument.lib

   Compile Command:
   ================
   cl /EHa /DTEST_COMM Comm.cpp Sockets.cpp locks.cpp Threads.cpp
                       BlockingQ.cpp XmlDocument.lib wsock32.lib

   Maintenance History:
   ====================
   ver 1.2 : 01 May 2010
   - added Sender::wait() to wait for sender thread to empty the
     send queue before shutting sender down.
   - added try catch handling around listener to prevent unhandled
     exception when receiver shuts down while listener is listening.
   - added test for both "quit" and "done" messages in Sender's
     SendThreadProc.  The "done" message shuts down send thread.
     The "quit" message shuts down both send thread in Sender and
     receive thread in Receiver.
   ver 1.1 : 17 Apr 2010
   - added Manual and Maintenance pages
   - added other comments in header file, below
   - added delete of socket pointer in ConnectionHandler when thread
     processing completes.
   - fixed bug in ConnectHandler that posted empty messages if client
     broke connection.
   - refactored the code a bit so files using the communicator don't 
     need to include so much.
   ver 1.0 : 13 Apr 2010
   - first release
*/

#include "..\Sockets\Sockets.h"  // must be first
#include "..\Threads\Threads.h"
#include "..\BlockingQueue\BlockingQueue.h"
#include "..\Message\Message.h"

/////////////////////////////////////////////////////////////////////////
// Supports sending Message instances
// - Attempts to connect to EndPoint.  If that fails, returns false.
// - Has send queue so PostMsg(msg) returns quickly

class Sender
{
public:
  Sender();
  bool connect(EndPoint pEp);
  void PostMsg(const Message& pMsg);
  void wait();
private:
  BQueue<Message> sendQ;
  tthread* pSendThread;
  Socket s_;
};

/////////////////////////////////////////////////////////////////////////
// Supports receiving Message instances
// - listener starts on specified port when constructed.
// - will throw exception if another listener already occuppies the 
//   specified port
// - Will block on GetMsg() if the receive queue is empty.

class Receiver
{
public:
  Receiver(long port);
  Message GetMsg();
private:
  SocketListener s_;
  BQueue<Message> recvQ;
  tthread* pListenThread;
};

#endif
