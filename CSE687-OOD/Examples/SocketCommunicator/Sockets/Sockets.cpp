/////////////////////////////////////////////////////////////////////
// Sockets.cpp - Provides basic network communication services     //
// ver 2.1                                                         //
// Language:      Visual C++, 2005                                 //
// Platform:      Dell Dimension 9150, Windows XP Pro, SP 2.0      //
// Application:   Utility for CSE687 and CSE775 projects           //
// Author:        Jim Fawcett, Syracuse University, CST 2-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////

#include "Sockets.h"
#include "../threads/locks.h"
#include <sstream>

#ifdef TRACING
  #include "..\threads\locks.h"
  #define TRACE(msg) sout << "\n  " << msg;
#else
  #define TRACE(msg) ;
#endif

bool SocketSystem::loaded = false;
int SocketSystem::count = 0;

//----< get socket error message string >----------------------------

std::string SocketSystem::GetLastMsg(bool WantSocketMsg) {

// ask system what type of error occurred

  DWORD errorCode;
  if(WantSocketMsg)
    errorCode = WSAGetLastError();
  else
    errorCode = GetLastError();
  if(errorCode == 0)
    return "no error";

// map errorCode into a system defined error string
    
  DWORD dwFlags = 
    FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER;
  LPCVOID lpSource = NULL;
  DWORD dwMessageID = errorCode;
  DWORD dwLanguageId = MAKELANGID(LANG_ENGLISH,SUBLANG_ENGLISH_US);
  LPSTR lpBuffer;
  DWORD nSize = 0;
  va_list *Arguments = NULL;

  FormatMessage(
    dwFlags,lpSource,dwMessageID,dwLanguageId, 
    (LPTSTR)&lpBuffer,nSize,Arguments
  );

  std::string _msg(lpBuffer);
  LocalFree(lpBuffer);
  return _msg;
}
//
//----< load WinSock Library >---------------------------------------

SocketSystem::SocketSystem()
{
  ++count;
  if(loaded == false)
  {
    TRACE("loading wsock32 library");
    WORD wVersionRequested = MAKEWORD(1,1); // requesting version 1.1
    WSAData wData;                          // startup data filled by WSAStartup
    int err = WSAStartup(wVersionRequested, &wData);
    if(err == SOCKET_ERROR)
      throw std::exception("initialization error: ");
    loaded = true;
  }
}
//----< destructor unloads socket library >--------------------------

SocketSystem::~SocketSystem()
{ 
  try {
    if(--count == 0)
    {
      TRACE("unloading wsock32 library");
      WSACleanup();
      loaded = false;
    }
  }
  catch(...) { /* don't allow exception to propagate on shutdown */}
}
//----< get host name >----------------------------------------------

std::string SocketSystem::getHostName()
{
  char buffer[256];
  gethostname(buffer,256);
  return buffer;
}
//
//----< get ip address of network machine >--------------------------

std::string SocketSystem::getIpFromName(const std::string& name)
{
  hostent* remoteHost = 0;
  SOCKADDR_IN tcpAddr;
  tcpAddr.sin_family = AF_INET;
  tcpAddr.sin_addr.s_addr = inet_addr(name.c_str());
  if(tcpAddr.sin_addr.s_addr == INADDR_NONE)
  {
    // name is not an ip address, so try to map name to address
    // via DNS

    hostent* remoteHost = gethostbyname(name.c_str());
    if(remoteHost == NULL)
      throw std::exception("invalid name");
    CopyMemory(
      &tcpAddr.sin_addr, 
      remoteHost->h_addr_list[0], 
      remoteHost->h_length
    );
  }
  return inet_ntoa(tcpAddr.sin_addr);
}
//----< get network name of machine from ip address >----------------

std::string SocketSystem::getNameFromIp(const std::string& ip)
{
  struct hostent* host = (hostent*)malloc(sizeof(struct hostent));
  struct in_addr *ipaddr = (in_addr*)malloc(sizeof(struct in_addr));
  ipaddr->s_addr = inet_addr(ip.c_str());
  host = gethostbyaddr((char*)ipaddr, sizeof(ipaddr), AF_INET);
  if(!host)
    throw std::exception("name resolution error: ");    
  return host->h_name;
}
//
//----< constructor creates TCP Stream socket >----------------------

Socket::Socket() : SocketConnectionCount(0)
{
  s_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(s_ == INVALID_SOCKET)
    throw std::exception("invalid socket in constructor");
}
//----< constructor creates a copy of socket >-----------------------
//
//Socket::Socket(const Socket& sock) : s_(sock.s_), SocketConnectionCount(sock.SocketConnectionCount)
//{
//  TRACE("\n  copying socket");
//  DuplicateHandle(GetCurrentProcess(),sock.getHandle(),GetCurrentProcess(),(HANDLE*)&s_,0,false,DUPLICATE_SAME_ACCESS);
//}
//----< constructor creates connected TCP Stream socket >------------

Socket::Socket(const std::string& url, int port) : SocketConnectionCount(0)
{
  s_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  if(s_ == INVALID_SOCKET)
    throw std::exception("invalid socket in constructor");
  this->connect(url, port);
}
//----< promotes WinSock SOCKET handle to Socket object >------------

Socket::Socket(SOCKET s) : s_(s), SocketConnectionCount(0) {}

//----< destructor closes socket handle >----------------------------

Socket::~Socket()
{ 
  TRACE("destroying socket");
  disconnect();
}
//----< assignment >-------------------------------------------------
//
//Socket& Socket::operator=(const Socket& sock) : s_(sock)
//{
//  if(this != &sock)
//  {
//    DuplicateHandle(GetCurrentProcess(),sock.getHandle(),GetCurrentProcess(),(HANDLE*)&s_,0,false,DUPLICATE_SAME_ACCESS);
//    ss_ = sock.ss_;
//    SocketConnectionCount = sock.SocketConnectionCount;
//  }
//  return *this;
//}
//----< assignment >-------------------------------------------------

Socket& Socket::operator =(SOCKET sock)
{
  TRACE("\n  assigning from SOCKET");
  s_ = sock;
  SocketConnectionCount = 0;
  return *this;
}
//----< connects to IP address or network host >---------------------

bool Socket::connect(std::string url, int port, bool throwError)
{
  try {
    if(isalpha(url[0]))
      url = SocketSystem().getIpFromName(url);
  }
  catch(...)
  {
    if(throwError)
      throw std::exception(ss_.GetLastMsg(true).c_str());
    return false;
  }
  SOCKADDR_IN tcpAddr;
  tcpAddr.sin_family = AF_INET;
  tcpAddr.sin_addr.s_addr = inet_addr(url.c_str());
  tcpAddr.sin_port = htons(port);
  if(s_ == INVALID_SOCKET)
  {
    s_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  }
  int err = ::connect(s_, (sockaddr*)&tcpAddr, sizeof(tcpAddr));
  std::string rip = getRemoteIP();
  int rport = getRemotePort();

  // error return from connect does not appear to be reliable
  
  if(err == SOCKET_ERROR || rport == -1)
  {
    if(throwError)
      throw std::exception(ss_.GetLastMsg(true).c_str());
    return false;
  }
  InterlockedIncrement(&SocketConnectionCount);
  return true;
}
//
//----< disconnect socket >------------------------------------------

void Socket::disconnect()
{
  shutdown(s_, SD_BOTH); 
  closesocket(s_);
  s_ = INVALID_SOCKET;
}
//----< casts Socket to WinSock SOCKET handle >----------------------

Socket::operator SOCKET ()
{ 
  return s_; 
}
//----< send blocks until all characters are sent >------------------

bool Socket::send(const char* block, size_t len, bool throwError)
{
  size_t bytesSent;       // current number of bytes sent
  size_t blockIndx = 0;   // place in buffer to send next
  size_t count = 0;       // number of send failures

  const int sendRetries = 100;
  size_t blockLen = len;
  size_t bytesLeft = blockLen;
  while(bytesLeft > 0) {
    bytesSent = ::send(s_,&block[blockIndx],static_cast<int>(bytesLeft),0);
    if(bytesSent == SOCKET_ERROR)
    {
      ++count;
      //sout << "\n  sending retry";
      if(bytesSent == WSAECONNRESET)
      {
        if(throwError)
          throw std::exception("connection closed");
        else 
          return false;
      }
      if(count==sendRetries)
      {
        if(throwError)
          throw std::exception("send failed after 100 retries");
        else
          return false;
      }
      Sleep(50);
      bytesSent = 0;
    }
    //sout << "\n  sending succeeded";
    bytesLeft -= bytesSent;
    blockIndx += bytesSent;
  }
  return true;
}
//----< blocks until len characters have been sent >-----------------

bool Socket::recv(char* block, size_t len, bool throwError)
{
  const size_t recvRetries = 100;
  size_t bytesRecvd, bytesLeft = len;
  size_t blockIndx = 0, count = 0;
  while(bytesLeft > 0) {
    bytesRecvd = ::recv(s_,&block[blockIndx],static_cast<int>(bytesLeft),0);
    if(bytesRecvd == 0)
    {
      if(throwError)
        throw(std::exception("remote connection closed"));
      return false;
    }
    if(bytesRecvd == SOCKET_ERROR) {
      ++count;
      if(bytesRecvd == WSAECONNRESET)
      {
        if(throwError)
          throw(std::exception("connection closed"));
        else
          return false;
      }
      if(count==recvRetries)
      {
        if(throwError)
          throw(std::exception("recv failed after 100 retries"));
        else
          return false;
      }
      Sleep(50);
    }
    bytesLeft -= bytesRecvd;
    blockIndx += bytesRecvd;
  }
  return true;
}
//
//----< get local ip address >---------------------------------------

std::string Socket::getLocalIP()
{
  struct sockaddr name;
  int len = sizeof(name);
  hostent* local = gethostbyname("");
  return inet_ntoa(*(struct in_addr*)*local->h_addr_list);
}
//----< get local port >---------------------------------------------

int Socket::getLocalPort()
{
  struct sockaddr name;
  int len = sizeof(name);
  int status = getsockname(s_,&name,&len);
  if(status == 0)
  {
    struct sockaddr_in* pLocal = reinterpret_cast<sockaddr_in*>(&name);
    return htons(pLocal->sin_port);
  }
  return -1;
}
//----< get remote ip address >--------------------------------------

std::string Socket::getRemoteIP()
{
  struct sockaddr name;
  int len = sizeof(name);
  int status = getpeername(s_,&name,&len);
  if(status == 0)
  {
    struct sockaddr_in* pRemote = reinterpret_cast<sockaddr_in*>(&name);
    return inet_ntoa(pRemote->sin_addr);
  }
  return "";
}
//----< get remote port >--------------------------------------------

int Socket::getRemotePort()
{
  struct sockaddr name;
  int len = sizeof(name);
  int status = getpeername(s_,&name,&len);
  if(status == 0)
  {
    struct sockaddr_in* pRemote = reinterpret_cast<sockaddr_in*>(&name);
    return htons(pRemote->sin_port);
  }
  return -1;
}
//
//----< starts listener socket listening for connections >-----------

SocketListener::SocketListener(int port) : InvalidSocketCount(0)
{
  tcpAddr.sin_family = AF_INET;   // TCP/IP
  tcpAddr.sin_port = htons(port); // listening port
  tcpAddr.sin_addr.s_addr = INADDR_ANY;
                                  // listen over every network interface
  int err = bind(s_, (SOCKADDR*)&tcpAddr, sizeof(tcpAddr));

  if(err == SOCKET_ERROR)
  {
    throw std::exception("binding error type:");
  }

  /////////////////////////////////////////////////////////////////
  // listen for incoming connection requests

  int backLog = 10;
  err = listen(s_, backLog);

  if(err == SOCKET_ERROR)
    throw std::exception("listen mode error");
}
//----< destructor closes socket >-----------------------------------

SocketListener::~SocketListener()
{
  try {
    TRACE("\n  destroying SocketListener");
    shutdown(s_, SD_BOTH);
    closesocket(s_);
  }
  catch(...) { /* don't let exception propagate on shutdown */}
}
//----< blocks until a connection request has been received >--------

SOCKET SocketListener::waitForConnect()
{
  const long MaxCount = 20;
  InvalidSocketCount = 0;
  TRACE("listener waiting for connection request");
  int size = sizeof(tcpAddr);
  SOCKET toClient;
  do {
    toClient = accept(s_, (SOCKADDR*)&tcpAddr, &size); 
    ++InvalidSocketCount;
    if(InvalidSocketCount >= 20)
      throw std::exception("invalid socket connection");
  } while (toClient == INVALID_SOCKET);
  TRACE("\n  connection establishted");
  return toClient;
}
//
//----< shuts down listerner >---------------------------------------

void SocketListener::stop()
{
  TRACE("shutting down listener in SocketListerer");
  shutdown(s_,SD_BOTH);
  closesocket(s_);
}
//----< get local ip address >---------------------------------------

std::string SocketListener::getLocalIP()
{
  return s_.getLocalIP();
}
//----< get local port number >--------------------------------------

int SocketListener::getLocalPort()
{
  return s_.getLocalPort();
}
//
//----< test stub >--------------------------------------------------

#ifdef TEST_SOCKETS
#include <iostream>

void main()
{
  std::cout << "\n  Testing Socket, SocketListener, and SocketSystem classes";
  std::cout << "\n ==========================================================\n";
  try
  {
    SocketSystem su;
    std::string host = su.getHostName();
    std::cout << "\n  host machine name:           " << host.c_str();
    std::string ip = su.getIpFromName(host);
    std::cout << "\n  IP Address of machine:       " << ip.c_str();
    std::string name = su.getNameFromIp(ip);
    std::cout << "\n  DNS name of machine from ip: " << name.c_str() << '\n';
  
    std::cout << "\n  connecting to listener";
    std::cout << "\n ------------------------";
    SocketListener listener(2048);
    Socket sendr;
//  if(!sendr.connect("127.0.0.1",2048))  // this works too
    if(!sendr.connect(name,2048))  // can use ip addr, e.g., 127.0.0.1
    {
      std::cout << "\n connection failed\n\n";
      return;
    }
    Socket recvr = listener.waitForConnect();
    std::cout << "\n  remote ip is: " << recvr.getRemoteIP();
    std::cout << ", remote port is: " << recvr.getRemotePort();
    std::cout << "\n  local ip is:  " << recvr.getLocalIP();
    std::cout << ", local port is: " << recvr.getLocalPort() << '\n';

    std::cout << "\n  sending from connector to listener";
    std::cout << "\n ------------------------------------";

    // sending
    const char* msg1 = "this is a message";
    sendr.send(msg1,strlen(msg1)+1);

    const char* msg2 = "and a final message";
    sendr.send(msg2,strlen(msg2)+1);

    sendr.send("quit",strlen("quit")+1);

//
    // receiving
    std::cout.flush();
    const int BufLen = 256;
    char buffer[BufLen];
    recvr.recv(buffer,strlen(msg1)+1);
    std::cout << "\n  listener received: " << buffer;

    recvr.recv(buffer,strlen(msg2)+1);
    std::cout << "\n  listener received: " << buffer;

    recvr.recv(buffer,strlen("quit")+1);
    std::cout << "\n  listener received: " << buffer;
    std::cout << "\n";

    std::cout << "\n  Breaking connection\n";
    recvr.disconnect();
    sendr.disconnect();

    std::cout << "\n  Establishing new connection\n";
    if(!sendr.connect(name,2048))
    {
      throw std::exception("\n  sender reconnect failed");
    }
    recvr = listener.waitForConnect();
    msg1 = "another message after reconnecting";
    std::cout << "\n  sender sending: " << msg1;
    sendr.send(msg1,strlen(msg1)+1);
    recvr.recv(buffer,strlen(msg1)+1);
    std::cout << "\n  listener received: " << buffer;
    std::cout << "\n";

    // demonstrating full duplex operation
    std::cout << "\n  sending from listener back to connector";
    std::cout << "\n -----------------------------------------";

    // sending
    msg1 = "sending message back";
    recvr.send(msg1,strlen(msg1)+1);
    recvr.send("quit",strlen("quit")+1);

    // receiving
    sendr.recv(buffer,strlen(msg1)+1);
    std::cout << "\n  connector received: " << buffer;
    sendr.recv(buffer,strlen("quit")+1);
    std::cout << "\n  connecter received: " << buffer;
    sendr.disconnect();
    recvr.disconnect();
    std::cout << "\n\n";
  }
  catch(std::exception& e)
  {
    std::cout << "\n  " << e.what() << "\n\n";
  }
}

#endif
