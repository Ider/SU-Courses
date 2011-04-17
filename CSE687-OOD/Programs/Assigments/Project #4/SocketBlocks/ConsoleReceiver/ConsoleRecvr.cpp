/////////////////////////////////////////////////////////////////////
// ConsoleRecvr.cpp - Uses sockets to send and receive messages    //
// ver 2.4                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Precision 7500, Windows Vista, SP 1.0       //
// Application:   Utility for CSE687 Project #4                    //
// Author:        Jim Fawcett, Syracuse University, CST 2-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////

#include <iostream>
#include <conio.h>
#include "..\SocketCommunicator\Communicator.h"
#include "..\SocketCommunicator\MsgHandler.h"
#include "..\BlockingQueue\BlockingQueue.h"
#include "..\Threads\locks.h"

/////////////////////////////////////////////////////////////////////
// Thread Proc classes for receiver

class MsgReceiver_Proc : public Thread_Processing<MsgReceiver_Proc>
{
public:
  MsgReceiver_Proc(IMsgHandler* pMsgHandler) : _pMsgHandler(pMsgHandler) {}
  void run()
  {
    GLock<1> lock;
    std::string msg;
    lock.lock();
    BQueue<std::string>* pBQ = _pMsgHandler->getQueue();
    ICommunicator* pComm = _pMsgHandler->getCommunicator();
    EndPoint remoteEp = _pMsgHandler->getEndPoint();
    lock.unlock();
    ///////////////////////////////////////////////////////
    // insert your server processing here
    while(true)
    {
      sout << locker << "\n  receiver processing message: " 
           << (msg = pBQ->deQ()).c_str() << unlocker;
      lock.lock();
      EndPoint remoteEp = _pMsgHandler->getEndPoint();
      if(pComm->connect(remoteEp.getIP(), remoteEp.getPort()))
      {
        pComm->postMessage(std::string("got message"));
        pComm->disconnect();
      }
      else
        sout << "\n  failed to connect";
      lock.unlock();

      if(msg == "quit")
        break;
    }
    // end of your code
    ///////////////////////////////////////////////////////
  }
private:
  IMsgHandler* _pMsgHandler;
};

class FileReceiver_Proc : public Thread_Processing<FileReceiver_Proc>
{
public:
  FileReceiver_Proc(IFileHandler* pFileHandler) : _pFileHandler(pFileHandler) {}
  void run()
  {
    GLock<1> lock;
    std::string msg;
    lock.lock();
    BQueue<std::string>* pBQ = _pFileHandler->getQueue();
    ICommunicator* pComm = _pFileHandler->getCommunicator();
    EndPoint remoteEp = _pFileHandler->getEndPoint();
    lock.unlock();
    ///////////////////////////////////////////////////////
    // insert your server code here
    while(true)
    {
      sout << locker << "\n  receiver processing file: " << (msg = pBQ->deQ()).c_str() << unlocker;
      //lock.lock();
      //EndPoint remoteEp = _pFileHandler->getEndPoint();
      //if(pComm->connect(remoteEp.getIP(), remoteEp.getPort()))
      //{
      //  pComm->postMessage(std::string("got file"));
      //  pComm->disconnect();
      //}
      //else
      //  sout << "\n  failed to connect";
      //lock.unlock();

      if(msg == "quit")
        break;
    }
    // end of your code
    ///////////////////////////////////////////////////////
  }
private:
  IFileHandler* _pFileHandler;
};

int main()
{
  sout << locker << "\n  Console Receiver Demo "
                 << "\n =======================\n" << unlocker;

  try
  {
    EndPoint rep("127.0.0.1",8081);
    //EndPoint sep("127.0.0.1",2049);
    
    // MsgReceiver_Proc is your receiver's server message handling
    // FileReceiver_Proc is your receiver's server file handling
    Communicator rcvr(rep);
    MsgHandler<MsgReceiver_Proc> rMsgHandler;
    rMsgHandler.setCommunicator(&rcvr);
    rcvr.attachMsgHandler(&rMsgHandler);
    FileHandler<FileReceiver_Proc> rFileHandler;
    rFileHandler.setFileDestination(".\\debug");
    rFileHandler.setCommunicator(&rcvr);
    rcvr.attachFileHandler(&rFileHandler);
    rcvr.listen();

    sout << "\n\n  press key to exit:  ";
    sout.flush();
    _getche();
    sout << "\n\n";
    rcvr.disconnect();
  }
  catch(std::exception& ex)
  {
    sout << locker << "\n  " << ex.what() << "\n\n" << unlocker;
  }
}



