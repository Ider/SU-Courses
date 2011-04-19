/////////////////////////////////////////////////////////////////////
// Comm.cpp    -  Enables sending Messages between machines        //
// ver 1.2                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Dimension T7400, Win 7 Pro                  //
// Application:   Utility for CSE687 projects                      //
// Author:        Jim Fawcett, Syracuse University, CST 4-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////

#include "Comm.h"
#include <iostream>
#include <sstream>

#ifdef TRACING
  #include "..\threads\locks.h"
  #define TRACE(msg) sout << "\n  " << msg;
#else
  #define TRACE(msg) ;
#endif

//----< send thread deQueues message and pushes into socket >------------
//
//  You shouldn't change this handler
//
class SendThreadProc : public Thread_Processing<SendThreadProc>
{
public:
  SendThreadProc(Socket& sock, BQueue<Message>& sendQ) 
    : sendSock(sock), sendQ_(sendQ) {}
  void run()
  {
    do
    {
      Message msg = sendQ_.deQ();
      std::string out = msg.ToString();
      if(!sendSock.send(out.c_str(), out.size()))
        throw std::exception("\n\n  could not send message\n\n");

      // done msg stops sender thread
      // quit msg stops both sender thread and receiver thread

      if(msg.body() == "quit" || msg.body() == "done")
      {
        sendSock.disconnect();
        break;
      }
    } while(true);
  }
private:
  Socket& sendSock;
  BQueue<Message>& sendQ_;
};
//----< start sending thread >-------------------------------------------

Sender::Sender() : pSendThread(new tthread(*new SendThreadProc(s_, sendQ))) 
{
  pSendThread->start();
}
//----< attempt to connect to a listening endpoint >---------------------

bool Sender::connect(EndPoint ep)
{
  std::string address = ep.address();
  long port = ep.port();
  if(!s_.connect(ep.address(), ep.port()))
  {
    return false;
  }
  return true;
}
//----< enqueue message for sending >------------------------------------

void Sender::PostMsg(const Message& msg)
{
  sendQ.enQ(msg);
}
//----< wait for send thread to finish >---------------------------------

void Sender::wait()
{
  pSendThread->wait();
}
//----< receive thread frames messages >---------------------------------
//
//  You shouldn't change this handler
//
class ConnectHandler : public Thread_Processing<ConnectHandler>
{
public:
  ConnectHandler(Socket* pSock, BQueue<Message>& recvQ) 
    : pSock_(pSock), recvQ_(recvQ) {}
  void run()
  {
    bool ClientActive = true;
    char buffer[1];
    std::string out;
    TRACE("entered ConnectHandler");
    do
    {
      do
      {
        if(pSock_->recv(buffer,1))
        {
          out += (char)buffer[0];
          if(isDone(out))
            break;
        }
        else
        {
          ClientActive = false;
          break;  // client closed
        }
      } while(true);
      if(!ClientActive)
        break;
      Message msg = Message::FromString(out);
      out = "";
      recvQ_.enQ(msg);
      if(msg.body() == "quit")
      {
        break;
        pSock_->disconnect();
      }
    } while(true);
    delete pSock_;  // created in listener for this handler only
  }
private:
  static bool isDone(std::string msg);
  Socket* pSock_;
  BQueue<Message>& recvQ_;
};
//----< did we receive terminating markup for message? >-----------------

bool ConnectHandler::isDone(std::string msg)
{
  static std::string terminal = "</msg>";
  for(size_t i=0; i<terminal.size(); ++i)
    if(terminal[6-i-1] != msg[msg.size()-i-1])
      return false;
  return true;
}
//----< define listener's activities >-----------------------------------
//
//  You shouldn't change this handler
//
class ListenProc : public Thread_Processing<ListenProc>
{
public:
  ListenProc(SocketListener& lsock, BQueue<Message>& recvQ) 
    : lsock_(lsock), recvQ_(recvQ) {}
  void run()
  {
    SOCKET sock;
    Socket* pSock;
    try
    {
      do
      {
        sock = lsock_.waitForConnect();
        pSock = new Socket(sock);  // will be deleted in ConnectHandler
        TRACE("\n  connected in listener: ");
        tthread* pThread = new tthread(*new ConnectHandler(pSock,recvQ_));
        pThread->start();
      } while(true);
    }
    catch(std::exception&)
    {
      TRACE("\n  Receiver's listener shutting down\n\n");
    }
  }
private:
  SocketListener& lsock_;
  BQueue<Message>& recvQ_;
};
//----< construct listener and start listening for connections >---------

Receiver::Receiver(long port)
        : s_(port), pListenThread(new tthread(*new ListenProc(s_, recvQ)))
{
  pListenThread->start();
}
//----< extract message from receive queue >-----------------------------

Message Receiver::GetMsg()
{
  return recvQ.deQ();
}

#ifdef TEST_COMM

///////////////////////////////////////////////////////////////
// Start testing

template <typename T>
std::string ToString(T t)
{
  std::ostringstream temp;
  temp << t;
  return temp.str();
}

void main()
{
  std::cout << "\n  Demonstrating Communicator Classes";
  std::cout << "\n ====================================\n";

  Receiver rcvr(8000);

  /////////////////////////////////////////////////////////////
  // Start message receiver thread

  class RecvProc : public Thread_Processing<RecvProc>
  {
  public:
    RecvProc(Receiver& rcvr) : rcvr_(rcvr) {}
    void run()
    {
      std::string msgBody;
      do
      {
        Message msg = rcvr_.GetMsg();
        msgBody = msg.body();
        sout << locker << "\n  received " << msgBody << unlocker;
      } while(msgBody != "quit");
    }
  private:
    Receiver& rcvr_;
  };

  tthread* pRt = new tthread(*new RecvProc(rcvr));
  pRt->start();

  /////////////////////////////////////////////////////////////
  // Start sending messages

  EndPoint ep("127.0.0.1:8000");
  Message msg("a message",ep,Message::text);

  Sender sndr;
  if(!sndr.connect(ep))
    std::cout << "\n  can't connect to " << ep.ToString();
  else
  {
    size_t count = 0;
    for(size_t i=0; i<20; ++i)
    {
      msg.body() = "msg #" + ToString(i) + " - some text";
      sout << locker << "\n  Posting  " << msg.body() << unlocker;
      sndr.PostMsg(msg);
    }
    Message end("quit");
    sndr.PostMsg(end);
  }

  pRt->wait();

  std::cout << "\n\n";
}

#endif
