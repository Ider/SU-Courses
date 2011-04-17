/////////////////////////////////////////////////////////////////////
// BlockHandler.cpp - Manages blocks used by sockets to send data  //
// ver 1.3                                                         //
// Language:      Visual C++, 2005                                 //
// Platform:      Dell Dimension 9150, Windows XP Pro, SP 2.0      //
// Application:   Utility for CSE687 and CSE775 projects           //
// Author:        Jim Fawcett, Syracuse University, CST 2-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////

#include <stdexcept>
#include <iostream>
#include "BlockHandler.h"
#include "..\threads\locks.h"

//----< create block - may throw bad_alloc or invalid_argument >-----

Block::Block(size_t blockSize)
{
  pBuffer = new byte_[blockSize];
  _headerLen = sizeOfType() + sizeOfLen() + sizeOfState();
  _buffLen = blockSize - _headerLen;
  if(_buffLen <= 0)
    throw(std::invalid_argument("no buffer in Block Ctor"));
  setType(message);
  setState(partial_message);
  sizeOfData(0);
}
//----< copy block >-------------------------------------------------

Block::Block(const Block& blk) 
     : _headerLen(blk._headerLen),_buffLen(blk._buffLen)
{
  pBuffer = new byte_[blk.sizeOfBlock()];
  memcpy(pBuffer,blk.pBuffer,blk.sizeOfBlock());
  sizeOfData(blk.sizeOfData());
  setType(blk.getType());
  setState(blk.getState());
}
//----< cleanup buffer >---------------------------------------------

Block::~Block()
{
  delete [] pBuffer;
}
//
//----< assignment >-------------------------------------------------

Block& Block::operator =(const Block& blk)
{
  if(&blk == this)
    return *this;
  sizeOfData(blk.sizeOfData());
  setType(blk.getType());
  setState(blk.getState());
  if(_buffLen >= blk.sizeOfData())
  {
    // blk's data fits in this block's buffer area

    memcpy(addrOfData(),blk.addrOfData(),blk.sizeOfData());
  }
  else
  { 
    // this block is too small, so resize, e.g.,
    // make block size just big enough to hold blk's data

    delete [] pBuffer;
    pBuffer = new byte_[sizeOfHeader() + blk.sizeOfData()];
    _buffLen = blk.sizeOfData();
    sizeOfData(blk.sizeOfData());
    memcpy(addrOfBlock(),blk.addrOfBlock(),sizeOfBlock());
  }
  return *this;
}
//
//----< retrieve data as string >------------------------------------

std::string Block::toString()
{
  std::string temp;
  size_t len = sizeOfData()-1;
  byte_* pData = addrOfData();
  for(size_t i = 0; i<len; ++i)
    temp += (char)(*(pData+i));
  return temp;
}
//----< build a Block >----------------------------------------------

Block Block::makeBlock(size_t BlockSize, Type type, State state, byte_* pData, size_t DataSize)
{
  Block temp(BlockSize);
  temp.setType(type);
  temp.setState(state);
  temp.copyDataToBlock(pData, DataSize);
  return temp;
}
//----< build a Block on heap >--------------------------------------

Block* Block::makeHeapBlock(size_t BlockSize, Type type, State state, byte_* pData, size_t DataSize)
{
  Block* pBlock = new Block(BlockSize);
  pBlock->setType(type);
  pBlock->setState(state);
  pBlock->copyDataToBlock(pData, DataSize);
  return pBlock;
}
//
//---< extract data from Block >-------------------------------------

void Block::copyDataFromBlock(byte_* pDst, size_t dstLen) const
{
  if(sizeOfData() == 0)
    return;
  memcpy(pDst,addrOfData(),minSize(dstLen,sizeOfData()));
}
//----< copies data into Block >-------------------------------------

void Block::copyDataToBlock(const byte_* pSrc, size_t srcLen)
{
  if(pSrc == 0)
    return;
//  sout << locker << "\n  srcLen = " << srcLen << locker;
//  sout << locker << "\n  _buffLen = " << _buffLen << locker;
  if(srcLen > _buffLen)
    throw(std::invalid_argument("data size to big for block capacity"));
  memcpy(addrOfData(),pSrc,srcLen);
  sizeOfData(srcLen);
}
//----< convert type to C-style string >-----------------------------

const char* Block::convertType() const
{
  Type _type = getType();
  switch(_type)
  {
  case message:
    return "message";
  case file:
    return "file";
  default:
    return "invalid type";
  }
}
//----< convert state to C-style string >----------------------------

const char* Block::convertState() const
{
  State _state = getState();
  switch(_state)
  {
  case address:
    return "address";
  case partial_message:
    return "partial_message";
  case end_message:
    return "end_message";
  case end_dialog:
    return "end_dialog";
  case end_connection:
    return "end_connection";
  default :
    return "invalid state";
  }
}
//----< show block parts >-------------------------------------------

void Block::showBlockStats(const std::string& s)
{
  sout << locker;
  sout << "\n  Block Statistics " << s << ":";
  sout << "\n  block type:\t" << convertType();
  sout << "\n  block state:\t" << convertState();
  sout << "\n  block size:\t" << (sizeOfHeader() + _buffLen);
  sout << "\n  header size:\t" << sizeOfHeader();
  sout << "\n  data size:\t" << sizeOfData();
  if(0 < sizeOfData() && sizeOfData() < 40)
    sout << "\n  data:\t\t" << addrOfData();
  sout << "\n" << unlocker;
}
//
//----< test stub >--------------------------------------------------

#ifdef TEST_BLOCKHANDLER

#include <iostream>

void main()
{
  sout << locker << "\n  Testing BlockHandler class "
                 << "\n ============================\n" << unlocker;

  try
  {
    std::cout << "\n  Test Creating Default Block ";
    std::cout << "\n -----------------------------\n";

    Block blk(1024);
    blk.showBlockStats();
    std::cout << "\n  size of Len:   " << blk.sizeOfLen();
    std::cout << "\n  size of Type:  " << blk.sizeOfType();
    std::cout << "\n  size of State: " << blk.sizeOfState();
    std::cout << "\n";

    std::cout << "\n  Testing copyDataToBlock ";
    std::cout << "\n -------------------------\n";

    const char* msg = "a block's message";
    blk.copyDataToBlock(msg,strlen(msg)+1); //copy terminating null
    blk.setType(Block::file);
    blk.setState(Block::end_message);
    blk.showBlockStats();

    std::cout << "\n  Testing copyDataFromBlock ";
    std::cout << "\n ---------------------------\n";

    char *bmsg = new char[blk.sizeOfData()]; 
    blk.copyDataFromBlock(bmsg,blk.sizeOfData());
    std::cout << "\n  blk data:\t" << bmsg << "\n";

    std::cout << "\n  Testing BlockHandler copy ctor ";
    std::cout << "\n --------------------------------\n";

    Block blkCopy = blk;
    blkCopy.showBlockStats();

    bmsg = new char[blkCopy.sizeOfData()]; 
    blkCopy.copyDataFromBlock(bmsg,blkCopy.sizeOfData());
    std::cout << "\n  blkCopy data:\t" << bmsg << "\n";
//
    std::cout << "\n  Testing BlockHandler assignment ";
    std::cout << "\n ---------------------------------\n";

    Block blkAsn(2048);
    blkAsn = blkCopy;
    blkAsn.showBlockStats();

    std::cout << "\n  Testing copyDataFromBlock ";
    std::cout << "\n ---------------------------\n";

    bmsg = new char[blkAsn.sizeOfData()]; 
    blkAsn.copyDataFromBlock(bmsg,blkAsn.sizeOfData());
    std::cout << "\n  blkAsn data:\t" << bmsg << "\n";

    std::cout << "\n";

    std::cout << "\n  Test Creating Tiny Block ";
    std::cout << "\n --------------------------\n";

    Block tinyBlk(16);
    tinyBlk = blkAsn;
    tinyBlk.showBlockStats();

    std::cout << "\n  Testing copyDataFromBlock ";
    std::cout << "\n ---------------------------\n";

    bmsg = new char[tinyBlk.sizeOfData()]; 
    tinyBlk.copyDataFromBlock(bmsg,tinyBlk.sizeOfData());
    std::cout << "\n  tinyBlk data:\t" << bmsg << "\n";

    std::cout << "\n";

    std::cout << "\n  Test resetting data size ";
    std::cout << "\n --------------------------\n";

    tinyBlk.sizeOfData(9);
    tinyBlk.showBlockStats();

    size_t debug = tinyBlk.sizeOfData();
    bmsg = new char[tinyBlk.sizeOfData()+1]; 
    tinyBlk.copyDataFromBlock(bmsg,tinyBlk.sizeOfData());
    // replace truncated terminating null
    bmsg[tinyBlk.sizeOfData()] = '\0';
    std::cout << "\n  tinyBlk data:\t" << bmsg << "\n";

    std::cout << "\n";
  }
  catch(std::exception& ex)
  {
    std::cout << "\n  " << ex.what() << "\n\n";
  }
}

#endif
