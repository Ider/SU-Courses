
//#include "FormSocketProcessing.h"

//#include "..\sockets\sockets.h"
//#include "..\threads\Threads.h"
//#include "..\threads\locks.h"
//#include "..\SocketCommunicator\Communicator.h"

///////////////////////////////////////////////////////////////////////
//// Thread Proc classes for receiver
//
//class MsgReceiver_Proc : public Thread_Processing
//{
//public:
//  MsgReceiver_Proc(IMsgHandler* pMsgHandler) : _pMsgHandler(pMsgHandler) {}
//  Thread_Processing* clone() const 
//  { 
//    return new MsgReceiver_Proc(_pMsgHandler); 
//  }
//  void run()
//  {
//    GLock<1> lock;
//    std::string msg;
//    lock.lock();
//    BQueue<std::string>* pBQ = _pMsgHandler->getQueue();
//    ICommunicator* pComm = _pMsgHandler->getCommunicator();
//    EndPoint remoteEp = _pMsgHandler->getEndPoint();
//    lock.unlock();
//    ///////////////////////////////////////////////////////
//    // insert your server processing here
//    while(true)
//    {
//      sout << locker << "\n  receiver processing message: " 
//           << (msg = pBQ->deQ()).c_str() << unlocker;
//      lock.lock();
//      EndPoint remoteEp = _pMsgHandler->getEndPoint();
//      if(pComm->connect(remoteEp.getIP(), remoteEp.getPort()))
//      {
//        pComm->postMessage(std::string("got message"));
//        pComm->disconnect();
//      }
//      else
//        sout << "\n  failed to connect";
//      lock.unlock();
//
//      if(msg == "quit")
//        break;
//    }
//    // end of your code
//    ///////////////////////////////////////////////////////
//  }
//private:
//  IMsgHandler* _pMsgHandler;
//};
//
//class FileReceiver_Proc : public Thread_Processing
//{
//public:
//  FileReceiver_Proc(IFileHandler* pFileHandler) : _pFileHandler(pFileHandler) {}
//  Thread_Processing* clone() const { return new FileReceiver_Proc(_pFileHandler); }
//  void run()
//  {
//    GLock<1> lock;
//    std::string msg;
//    lock.lock();
//    BQueue<std::string>* pBQ = _pFileHandler->getQueue();
//    ICommunicator* pComm = _pFileHandler->getCommunicator();
//    EndPoint remoteEp = _pFileHandler->getEndPoint();
//    lock.unlock();
//    ///////////////////////////////////////////////////////
//    // insert your server code here
//    while(true)
//    {
//      sout << locker << "\n  receiver processing file: " << (msg = pBQ->deQ()).c_str() << unlocker;
//      lock.lock();
//      EndPoint remoteEp = _pFileHandler->getEndPoint();
//      if(pComm->connect(remoteEp.getIP(), remoteEp.getPort()))
//      {
//        pComm->postMessage(std::string("got file"));
//        pComm->disconnect();
//      }
//      else
//        sout << "\n  failed to connect";
//      lock.unlock();
//
//      if(msg == "quit")
//        break;
//    }
//    // end of your code
//    ///////////////////////////////////////////////////////
//  }
//private:
//  IFileHandler* _pFileHandler;
//};
//
//}
//std::string convert(String^ s)
//{
//  std::string temp;
//  for(int i=0; i<s->Length; ++i)
//    temp += (char)s[i];
//  return temp;
//}
//String^ convert(const std::string& s)
//{
//  StringBuilder^ temp = gcnew StringBuilder();
//  for(size_t i=0; i<s.size(); ++i)
//    temp->Append((wchar_t)s[i]);
//  return temp->ToString();
//}
//void SetUpCommunicator(String^ ip, int port)
//{
//  try
//  {
//    //EndPoint rep(convert(ip), port);
//    //
//    //// MsgReceiver_Proc is your receiver's server message handling
//    //// FileReceiver_Proc is your receiver's server file handling
//    //Communicator rcvr(rep);
//    //MsgHandler<MsgReceiver_Proc> rMsgHandler;
//    //rMsgHandler.setCommunicator(&rcvr);
//    //rcvr.attachMsgHandler(&rMsgHandler);
//    //FileHandler<FileReceiver_Proc> rFileHandler;
//    //rFileHandler.setFileDestination(".\\debug\\received2\\");
//    //rFileHandler.setCommunicator(&rcvr);
//    //rcvr.attachFileHandler(&rFileHandler);
//    //rcvr.listen();
//
//    //// MsgSender_Proc is your sender's server message handling
//    ////   If you don't have sender server file handling don't 
//    ////   attach a file handler
//    //Communicator sndr(sep);
//    //sndr.setFileSource(".\\debug\\toSend\\");
//    //MsgHandler<MsgSender_Proc> smsgHandler;
//    //sndr.attachMsgHandler(&smsgHandler);
//    //sndr.listen();
//
//    //// The MsgReceiver_Proc and FileReceiver_Proc
//    //// should connect when they have a reply, so
//    //// don't connect the receiver - that's done
//    //// by your server code (see above)
//
//    //if(!sndr.connect("127.0.0.1",2048))
//    //{
//    //  sout << "\n  failed to connect sndr\n\n";
//    //  return 1;
//    //}
//
//    //sndr.postMessage("first message");
//    //sndr.postMessage("second message");
//    //sndr.postMessage("third and longer message");
//    //sndr.postMessage("fourth and still longer and most verbose message");
//    //sndr.postFile("test.txt");
//    //sndr.postFile("adapters.h");
//    //sndr.postFile("BlockingQueue.obj");
//    //sndr.postFile("notepad.exe");
//    //sndr.postMessage("quit");
//
//    //sout << "\n\n  press key to exit:  ";
//    //sout.flush();
//    //_getche();
//    //sout << "\n\n";
//    //rcvr.disconnect();
//    ////sndr.disconnect();
//
//  }
//  catch(std::exception& ex)
//  {
//    sout << locker << "\n  " << ex.what() << "\n\n" << unlocker;
//  }
//}
