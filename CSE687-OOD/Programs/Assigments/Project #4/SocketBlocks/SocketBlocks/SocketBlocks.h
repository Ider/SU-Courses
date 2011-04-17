#ifndef SOCKETBLOCKS_H
#define SOCKETBLOCKS_H
/////////////////////////////////////////////////////////////////////
// SocketBlocks.h - Uses sockets and blocks to send messages       //
// ver 1.3                                                         //
// Language:      Visual C++, 2005                                 //
// Platform:      Dell Dimension 9150, Windows XP Pro, SP 2.0      //
// Application:   Utility for CSE687 and CSE775 projects           //
// Author:        Jim Fawcett, Syracuse University, CST 2-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////
/*
   Module Operations:
   ==================
   This module a SocketBlocks class that provides means to send a
   message, as a series of blocks.  It accumulates, at the receiver,
   the message by extracting and concatenating data from each block,
   as it arrives.

   Public Interface:
   =================
   SocketSystem sys;                          // load winsock lib
   SocketBlocks comm;                         // create communicator
   Socket sendr;                              // create sending socket
   sender.connect("localhost",2048);          // request a connection
   SocketListener listener(2048);             // create listener
   Socket recvr = listener.waitForConnect();  // start listener listening

   Block srcBlk(1024);                        // create and send block
   const char* msg = "this is a message"; 
   srcBlk.copyDataToBlock(msg.c_str(),msg.size()+1);
   sender.send(
     srcBlk.addrOfBlock(),
     srcBlk.sizeOfHeader() + srcBlk.sizeOfData()
   );

   receiver.recv(dstBlk.addrOfHeader(),dstBlk.sizeOfHeader());
   receiver.recv(dstBlk.addrOfData(),dstBlk.sizeOfData());
   comm.accumulateData(dstBlk);

   // after more blocks

   size_t len = comm.getDataSize();
   byte_* pString = comm.getDataAsString();

   recvr.disconnect();                        // graceful shutdown
   sender.disconnect();                       // graceful shutdown
*/
//
/*
   Build Process:
   ==============
   Required Files:
     SocketBlocks.h, SocketBlocks.cpp, Sockets.h, Sockets.cpp,
     BlockHandler.h, BlockHandler.cpp, locks.h, locks.cpp

   Compile Command:
   ================
   cl /EHsc /DTEST_SOCKETS SocketBlocks.cpp Sockets.cpp BlockHandler.cpp \
                           locks.cpp wsock32.lib user32.lib

   Maintenance History:
   ====================
   ver 1.3 : 27 Mar 07
   - fixed another bug in AccumulateData by replacing 1 with i in the 
     next to last statement.  Again spotted by Estepan.
   ver 1.2 : 26 Mar 07
   - fixed BuffSize bug in AccumulateData, found by Avinash Bhat and 
     Estepan Melikasetian
   ver 1.1 : 24 Mar 07
   - removed fixups required in earlier version of BlockHandler
   ver 1.0 : 11 Feb 07
   - first release
     This is a major rewrite of an earlier socket demo

*/
//

#include "..\BlockHandler\BlockHandler.h"

class SocketBlocks
{
public:
  SocketBlocks(size_t buffSize = 512) 
    : buffer(new byte_[buffSize]), BuffSize(buffSize), dataLen(0) {}
  ~SocketBlocks() { delete [] buffer; }
  void accumulateData(const Block& blk);
  byte_* getData();
  size_t getDataSize();
  void clearData();
  byte_* getDataAsString();
private:
  byte_* buffer;    // place to accumulate block data
  size_t dataLen;   // size of data in current block
  size_t BuffSize;  // block body size
};

#endif
