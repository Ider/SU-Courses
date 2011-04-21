#ifndef BLOCKHANDLER_H
#define BLOCKHANDLER_H
/////////////////////////////////////////////////////////////////////
// BlockHandler.h - Manages blocks used by sockets to send data    //
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
   This module is intended to work with the SocketCommunicator module.
   It provides packaging for raw bytes that sockets know how to send.
   Blocks are composed of header and data sections.  Headers are
   fixed size, and hold the size of their data buffer and an enumeration
   that describes the current communication state.

   Public Interface:
   =================
   enum State { 
     partial_message,   // this block is part of a continuing message
     end_message,       // last block in message
     end_dialog,        // will start listening
     end_connection     // closing connection
   };
   Block blk(1024);                   // create Block of total size 1024 bytes
   blk.copyDataToBlock(&src,size);        // copy data to Block
   blk.copyDataFromBlock(&dest,size);     // extract data from Block
   State blk.getState();              // get communication state
   blk.setState(state);               // change communication state
   size_t dataLen = blk.sizeOfData(); // get data size
   blk.sizeOfData(53);                // data buffer resize (within capacity)
   blk.showBlockStats();              // show block statistics
*/
//
/*
   Build Process:
   ==============
   Required Files:
     BlockHandler.h, BlockHandler.cpp, locks.h, locks.cpp

   Compile Command:
   ================
   cl /EHsc /DTEST_BLOCKHANDLER BlockHandler.cpp locks.cpp

   Maintenance History:
   ====================
   ver 1.3 : 16 Apr 2009
   - added enum Type { message, file }; and adjusted member functions accordingly
   ver 1.2 : 24 Mar 2007
   - removed private members _dataLen and _state, use extracted information
     in their place
   ver 1.1 : 18 Feb 2007
   - added locking of std::cout with sout wrapper
   ver 1.0 : 11 Feb 2007
   - first release

   Design Note:
   ============
   Block layout in memory:

   [ dataLen | type | state |  data ...   | unused ]
   <------ headerLen ------><-- dataLen -->
                            <------ buffLen ------>
   <------ blockSize = headerLen + buffLen ------->

   To Do:
   ======
   Remove _dataLen and and _state parameters.  Read and write length and state
   directly from block storage using techniques of fixLen and fixState.
*/
//
#include <sstream>
#include <string>

typedef char byte_;

class Block
{
public:
  enum Type
  {
    message,
    file
  };
  enum State
  { 
    address,            // data is source EndPoint
    partial_message,    // block is part of continuing message
    end_message,        // last block in message
    end_dialog,         // will start listening
    end_connection      // closing connection
  };
  Block(size_t blockSize);
  Block(const Block& blk);
  ~Block();
  Block& operator=(const Block& blk);
  static Block makeBlock(
                 size_t BlockSize, Type type, State state, byte_* data, size_t DataSize
               );
  static Block* makeHeapBlock(
                  size_t BlockSize, Type type, State state, byte_* data, size_t DataSize
                );

    // copyDataToBlock copies min(srcLen,_bufferLen)
    // copyDataFromBlock copies min(srcLen,_dataLen)

  void copyDataToBlock(const byte_* pSrc, size_t srcLen);
  void copyDataFromBlock(byte_* pDst, size_t dstLen) const;
  std::string toString();
  Type getType() const;
  void setType(Type type);
  State getState() const;
  void setState(State state);
  
    // converts Type and State to C-strings

  const char* convertType() const;
  const char* convertState() const;

  void showBlockStats(const std::string& s = "");

    // low-level block layout analysis

  byte_* addrOfLen() const;
  size_t sizeOfLen() const;
  byte_* addrOfType() const;
  size_t sizeOfType() const;
  byte_* addrOfState() const;
  size_t sizeOfState() const;
  byte_* addrOfData() const;
  size_t sizeOfData() const;
  void sizeOfData(size_t dataSize);
  byte_* addrOfBlock() const;
  size_t sizeOfBlock() const;
  byte_* addrOfHeader() const;
  size_t sizeOfHeader() const;
private:
  size_t minSize(size_t left, size_t right) const;
  size_t _headerLen;
  size_t _buffLen;
  byte_* pBuffer;
};
//
//----< public helper >----------------------------------------------

template <typename T> std::string toString(const T& t)
{
  std::ostringstream temp;
  temp << t;
  return temp.str();
}

//----< private helper >---------------------------------------------

inline size_t Block::minSize(size_t left, size_t right) const
{
  return ( left < right ? left : right );
}

//----< read and write type >----------------------------------------

inline Block::Type Block::getType() const
{
  return *reinterpret_cast<Type*>(addrOfType());
}

inline void Block::setType(Type type)
{
  Type& temp = *reinterpret_cast<Type*>(addrOfType());
  temp = type;
}
//----< read and write state >---------------------------------------

inline Block::State Block::getState() const
{ 
  return *reinterpret_cast<State*>(addrOfState());
}

inline void Block::setState(State state)
{ 
  State& temp = *reinterpret_cast<State*>(addrOfState());
  temp = state;
}

//----< analyze and modify block's layout in memory >----------------

inline byte_* Block::addrOfLen() const { return pBuffer; }
inline size_t Block::sizeOfLen() const { return sizeof(size_t); }

inline byte_* Block::addrOfType() const { return pBuffer + sizeOfLen(); }
inline size_t Block::sizeOfType() const { return sizeof(Type); }

inline byte_* Block::addrOfState() const { return pBuffer + sizeOfLen() + sizeOfType(); }
inline size_t Block::sizeOfState() const { return sizeof(State); }

inline byte_* Block::addrOfHeader() const { return pBuffer; }
inline size_t Block::sizeOfHeader() const
{ 
  return sizeOfLen() + sizeOfType() + sizeOfState(); 
}

inline byte_* Block::addrOfData() const 
{ 
  return pBuffer + sizeOfHeader(); 
}
inline size_t Block::sizeOfData() const
{ 
  return *reinterpret_cast<size_t*>(addrOfLen());
}

inline void   Block::sizeOfData(size_t dataSize)
{ 
  size_t& temp = *reinterpret_cast<size_t*>(addrOfLen());
  temp = minSize(dataSize,_buffLen); 
}

inline byte_* Block::addrOfBlock() const { return pBuffer; }
inline size_t Block::sizeOfBlock() const { return _headerLen + _buffLen; }

#endif

