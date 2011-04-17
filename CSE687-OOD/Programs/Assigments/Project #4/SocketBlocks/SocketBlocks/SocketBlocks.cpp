/////////////////////////////////////////////////////////////////////
// SocketBlocks.cpp - Uses sockets and blocks to send messages     //
// ver 1.3                                                         //
// Language:      Visual C++, 2005                                 //
// Platform:      Dell Dimension 9150, Windows XP Pro, SP 2.0      //
// Application:   Utility for CSE687 and CSE775 projects           //
// Author:        Jim Fawcett, Syracuse University, CST 2-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////

#include "..\sockets\sockets.h"
#include "..\blockhandler\BlockHandler.h"
#include "..\threads\locks.h"
#include "SocketBlocks.h"
#include <iostream>

//----< add block's data to buffer, resize if necessary >------------

void SocketBlocks::accumulateData(const Block& blk)
{
  byte_* pData = blk.addrOfData();
  size_t len = blk.sizeOfData();
  for(size_t i=0; i<len; ++i)
  {
    if(dataLen < BuffSize)  // enough room
      *(buffer + dataLen++) = *(pData + i);
    else
    {                       // not enough room
      byte_* temp = new byte_ [2*BuffSize];
      for(size_t j=0; j<BuffSize; ++j)
        *(temp+j) = *(buffer+j);
      delete [] buffer;
      buffer = temp;
      *(buffer + dataLen++) = *(pData + i);
      BuffSize = 2*BuffSize;
    }
  }
}
//----< manage SocketBlocks data buffer >----------------------------

byte_* SocketBlocks::getData() { return buffer; }

void SocketBlocks::clearData() { dataLen = 0; }

size_t SocketBlocks::getDataSize() { return dataLen; }

byte_* SocketBlocks::getDataAsString()
{
  if(dataLen < 1)
    return 0;
  for(size_t i=0; i<dataLen-1; ++i)
    if(*(buffer+i) == '\0')
      *(buffer+i) = ' ';
  return buffer;
}
//
//----< test stub >--------------------------------------------------

#ifdef TEST_SOCKETBLOCKS

void main()
{
  std::cout << "\n  Testing SocketBlocks ";
  std::cout << "\n ======================\n";
  try
  {
    SocketSystem ss;
    SocketBlocks comm;
    SocketListener listener(1024);
    Socket sender;

    // We're not using threads here, so sender has to try to connect
    // before starting the listener, else the program will block
    // forever.

//  if(!sender.connect("127.0.0.1",1024))  also works
    if(!sender.connect("localhost",1024))
    {
      sout << "\n  connection failed\n\n";
      return;
    }
    Socket receiver = listener.waitForConnect();

    std::cout << "\n  Sending Blocks ";
    std::cout << "\n ----------------\n";
    
    Block srcBlk(512);
    std::string msg = std::string("message block #") + toString(0);
    srcBlk.copyDataToBlock(msg.c_str(),msg.size()+1);
    srcBlk.showBlockStats();

    const int NumBlocks = 6;
    for(int i=0; i<NumBlocks; ++i)
    {
      std::string msg = std::string("message block #") + toString(i);
      srcBlk.copyDataToBlock(msg.c_str(),msg.size()+1);
      if(i == NumBlocks-1)
        srcBlk.setState(Block::end_message);
      sender.send(srcBlk.addrOfBlock(),srcBlk.sizeOfHeader() + srcBlk.sizeOfData());
      std::cout << "\n  sent State:  " << srcBlk.convertState();
      std::cout << "\n  sent data:   " << srcBlk.addrOfData();
      std::cout << "\n";
    }
    srcBlk.showBlockStats();
//
    std::cout << "\n  Receiving Blocks ";
    std::cout << "\n ------------------\n";

    Block dstBlk(512);
    do
    {
      receiver.recv(dstBlk.addrOfHeader(),dstBlk.sizeOfHeader());
      std::cout << "\n  recvd State: " << dstBlk.convertState();
      receiver.recv(dstBlk.addrOfData(),dstBlk.sizeOfData());
      byte_ buffer[512];
      dstBlk.copyDataFromBlock(buffer,512);
      std::cout << "\n  recvd data:  " << buffer;
      std::cout << "\n";
      comm.accumulateData(dstBlk);
    } while(dstBlk.getState() != Block::end_message);

    std::cout << "\n  Accumulated Block Data is a message ";
    std::cout << "\n -------------------------------------\n";

    std::cout << "\n  message = " << comm.getDataAsString();
    std::cout << "\n\n";

    receiver.disconnect();
    sender.disconnect();
  }
  catch(std::exception& ex)
  {
    std::cout << "\n  " << ex.what() << "\n\n";
  }
}

#endif
