/////////////////////////////////////////////////////////////////////
// Communicator.cpp - Uses sockets and blocks to send messages     //
// ver 2.7                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Precision 7500, Windows Vista, SP 1.0       //
// Application:   Utility for CSE687 Project #4                    //
// Author:        Jim Fawcett, Syracuse University, CST 2-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////

#include "..\sockets\sockets.h"
#include "..\threads\Threads.h"
#include "..\threads\locks.h"
#include "Communicator.h"
//#include "DemoForm.h"
#include <iostream>
#include <conio.h>

//----< initialization of static members >---------------------------

size_t Communicator::_BlkSize;

//Invoker<EndPoint> BlockProc::notify;

//----< acquire MsgHandler from ListenProc >-------------------------

void BlockProc::attachMsgHandler(IMsgHandler* pMsgHandler)
{
  lock.lock();
  _pMsgHandler = pMsgHandler;
  if(_pMsgHandler)
    _pMsgHandler->start();
  lock.unlock();
}
//----< acquire FileHandler from ListenProc >------------------------

void BlockProc::attachFileHandler(IFileHandler* pFileHandler)
{
  lock.lock();
  _pFileHandler = pFileHandler;
  if(_pFileHandler)
    _pFileHandler->start();
  lock.unlock();
}
//----< called by BlockProc::run() >---------------------------------

void BlockProc::handleMsgBlock(Block* pBlk)
{
  static std::string accumulate;
  if(pBlk->getState() == Block::address)  // set EndPoint
  {
    std::string ep = pBlk->toString();
    accumulate = ep + std::string("@");
  }
  else
  {
    // accumulate block data

    if(pBlk->sizeOfData() > 0)
      accumulate.append(pBlk->toString());
    
    // post block if end_message

    if(pBlk->getState() == Block::end_message)
    {
      lock.lock();
      _pMsgHandler->postMessage(accumulate);
      lock.unlock();
    }
  }
}
//----< called by BlockProc::run() >---------------------------------

void BlockProc::handleFileBlock(Block* pBlk)
{
  static std::string accumulate;
  if(pBlk->getState() == Block::address)
  {
    std::string ep = pBlk->toString();
    accumulate = ep + std::string("@");  // set EndPoint
  }
  else
  {
    if(accumulate[accumulate.size()-1] == '@')
    {
      // send EndPoint@filename
      accumulate.append(pBlk->toString());
      lock.lock();
      _pFileHandler->postFileName(accumulate);
      lock.unlock();
    }
    else
    {
      // send file blocks
      lock.lock();
      _pFileHandler->postFileBlock(pBlk);
      lock.unlock();
    }
  }
}
//----< Processing for client thread spawned by listener >-----------

void BlockProc::run()
{
  Socket sock = _socket;
  _clientId = "";

  Block::State state;
  Block* pBlock;
  do
  {
    // read block header from socket
    pBlock = new Block(BlockSize);
    bool goodHeader = sock.recv(pBlock->addrOfHeader(),pBlock->sizeOfHeader());
    
    // read block data from socket
    bool goodData = sock.recv(pBlock->addrOfData(),pBlock->sizeOfData());
    if(!goodHeader || !goodData)
      break;  // connection failed

    if(pBlock->getState() == Block::address)
    {
      _clientId = pBlock->toString();
    }
    if(pBlock->getType() == Block::message)
      handleMsgBlock(pBlock);
    else
      handleFileBlock(pBlock);

    state = pBlock->getState();
  } while(state != Block::end_dialog && state != Block::end_connection);
  sock.disconnect();
}
void listenProc::run()
{
  Socket handler;
  while(true)
  {
    handler = _pListener->waitForConnect();

    // create block processing function for thread and start thread

    BlockProc bp(handler);
    if(_pMsgHandler)
      bp.attachMsgHandler(_pMsgHandler->clone());
    if(_pFileHandler)
      bp.attachFileHandler(_pFileHandler->clone());
    tthread* pTthread = new tthread(bp);
    pTthread->start();
  }
}
//----< start listener on child thread >-----------------------------

bool Communicator::listen()
{
  listenProc* pLp = new listenProc(&_listener);
  pLp->attachMsgHandler(_pMsgHandler);
  pLp->attachFileHandler(_pFileHandler);
  tthread* pTthread = new tthread(*pLp);
  pTthread->start();
  return true;
}
//----< post message to connected socket >---------------------------

void Communicator::postMessage(const std::string& msg)
{
  size_t start = 0;
  size_t end = msg.size();

  // send start block

  Block* pBlock = this->startMsgBlock(_localEp, Block::message, _BlkSize);
  size_t incr = pBlock->sizeOfBlock() - pBlock->sizeOfHeader() - 1;
  incr = min(incr,end-start);
  this->postBlock(pBlock);
  delete pBlock;
  std::string temp;

  // send data blocks

  while(start < end)
  {
    temp = msg.substr(start, incr);
    start += incr;
    pBlock = this->midMsgBlock(Block::message,(byte_*)temp.c_str(),temp.size());
    this->postBlock(pBlock);
    delete pBlock;
  }
  // send end block

  pBlock = this->endMsgBlock(Block::message);
  this->postBlock(pBlock);
  delete pBlock;
}
//----< post file to connected socket >------------------------------

void Communicator::postFile(const std::string& filespec)
{
  std::string file = _path + filespec;
  std::filebuf readBuff;
  readBuff.open(file.c_str(), std::ios::in | std::ios::binary);
  if(!readBuff.is_open())
  {
    std::string msg = "\n  Can't open file \"";
    msg.append(file);
    msg.append("\" for reading\n");
    throw std::exception(msg.c_str());
  }

  // send start block

  Block* pBlock = this->startMsgBlock(_localEp, Block::file, _BlkSize);
  size_t incr = pBlock->sizeOfBlock() - pBlock->sizeOfHeader() - 1;
  this->postBlock(pBlock);
  delete pBlock;

  // send file name

  pBlock = this->midMsgBlock(Block::file,(byte_*)filespec.c_str(),filespec.size());
  std::string temp = pBlock->toString();
  sout << locker << "\n  " << temp.c_str() << unlocker;
  this->postBlock(pBlock);
  delete pBlock;

  // send data blocks

  byte_* pBuffer = new byte_[_BlkSize]; 
  while(true)
  {
    std::streamsize count = readBuff.sgetn(pBuffer,incr);
    /////////////////////////////////////////////////
    // let's you see text content while debugging
    // *(pBuffer + count) = (byte_)"\0";
    if(count == 0)
      break;
    pBlock = this->midMsgBlock(Block::file,pBuffer,count-1);
    this->postBlock(pBlock);
    delete pBlock;
  }
  // send end block

  pBlock = this->endMsgBlock(Block::file);
  this->postBlock(pBlock);
  delete pBlock;
  delete [] pBuffer;
  readBuff.close();
}
//----< attempt to send a block >------------------------------------

bool Communicator::postBlock(Block* pBlock)
{
  if(_connector.send(pBlock->addrOfHeader(),pBlock->sizeOfHeader()))
    return _connector.send(pBlock->addrOfData(),pBlock->sizeOfData());
  return false;
}
//----< create instance of Communicator >----------------------------

ICommunicator* ICommunicator::Create(EndPoint ep, size_t blkSize)
{
  return new Communicator(ep,blkSize);
}

#ifdef TEST_COMMUNICATOR

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
      lock.lock();
      EndPoint remoteEp = _pFileHandler->getEndPoint();
      if(pComm->connect(remoteEp.getIP(), remoteEp.getPort()))
      {
        pComm->postMessage(std::string("got file"));
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
  IFileHandler* _pFileHandler;
};

/////////////////////////////////////////////////////////////////////
// Thread Proc classes for sender

class MsgSender_Proc : public Thread_Processing<MsgSender_Proc>
{
public:
  MsgSender_Proc(IMsgHandler* pMsgHandler) : _pMsgHandler(pMsgHandler) {}
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
    // enter your server code here
    while(true)
    {
      sout << locker << "\n  sender received message: " 
           << (msg = pBQ->deQ()).c_str() << unlocker;
      if(msg == "quit")
        break;
    }
    // end of your code
    ///////////////////////////////////////////////////////
  }
private:
  IMsgHandler* _pMsgHandler;
};

class FileSender_Proc : public Thread_Processing<FileSender_Proc>
{
public:
  FileSender_Proc(IFileHandler* pFileHandler) : _pFileHandler(pFileHandler) {}
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
    // enter your server code here
    while(true)
    {
      sout << locker << "\n  sender received file: " 
           << (msg = pBQ->deQ()).c_str() << unlocker;
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
  sout << locker << "\n  Testing Socket Communicator "
                 << "\n =============================\n" << unlocker;

	//Application::EnableVisualStyles();
	//Application::SetCompatibleTextRenderingDefault(false); 

	//// Create the main window and run it
 // Application::Run(gcnew SocketComm::DemoForm());

  try
  {
    EndPoint rep("127.0.0.1",2048);
    EndPoint sep("127.0.0.1",2049);
    
    // MsgReceiver_Proc is your receiver's server message handling
    // FileReceiver_Proc is your receiver's server file handling
    Communicator rcvr(rep);
    MsgHandler<MsgReceiver_Proc> rMsgHandler;
    rMsgHandler.setCommunicator(&rcvr);
    rcvr.attachMsgHandler(&rMsgHandler);
    FileHandler<FileReceiver_Proc> rFileHandler;
    rFileHandler.setFileDestination(".\\debug\\received2\\");
    rFileHandler.setCommunicator(&rcvr);
    rcvr.attachFileHandler(&rFileHandler);
    rcvr.listen();

    // MsgSender_Proc is your sender's server message handling
    //   If you don't have sender server file handling don't 
    //   attach a file handler
    Communicator sndr(sep);
    sndr.setFileSource(".\\debug\\toSend\\");
    MsgHandler<MsgSender_Proc> smsgHandler;
    sndr.attachMsgHandler(&smsgHandler);
    sndr.listen();

    // The MsgReceiver_Proc and FileReceiver_Proc
    // should connect when they have a reply, so
    // don't connect the receiver - that's done
    // by your server code (see above)

    if(!sndr.connect("127.0.0.1",2048))
    {
      sout << "\n  failed to connect sndr\n\n";
      return 1;
    }

    sndr.postMessage("first message");
    sndr.postMessage("second message");
    sndr.postMessage("third and longer message");
    sndr.postMessage("fourth and still longer and most verbose message");
    sndr.postFile("test.txt");
    sndr.postFile("adapters.h");
    sndr.postFile("BlockingQueue.obj");
    sndr.postFile("notepad.exe");
    sndr.postMessage("quit");

    sout << locker << "\n  Socket connection count = " 
         << sndr.getSocketConnectionCount() << unlocker;
    sout << locker << "\n  Invalid Socket count = " 
         << rcvr.getInvalidSocketCount() << unlocker;

    sout << "\n\n  press key to exit:  ";
    sout.flush();
    _getche();
    sout << "\n\n";
//    rcvr.disconnect();
    sndr.disconnect();

  }
  catch(std::exception& ex)
  {
    sout << locker << "\n  " << ex.what() << "\n\n" << unlocker;
  }
}

#endif

