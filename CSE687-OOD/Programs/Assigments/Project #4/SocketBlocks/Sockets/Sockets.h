#ifndef SOCKETS_H
#define SOCKETS_H
/////////////////////////////////////////////////////////////////////
// Sockets.h   -  Provides basic network communication services    //
// ver 2.0                                                         //
// Language:      Visual C++, 2005                                 //
// Platform:      Dell Dimension 9150, Windows XP Pro, SP 2.0      //
// Application:   Utility for CSE687 and CSE775 projects           //
// Author:        Jim Fawcett, Syracuse University, CST 2-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////
/*
   Module Operations:
   ==================
   This module provides network communication services, using 
   WinSock2, a nearly Berkley Sockets compliant implementation
   with extensions.  Three classes are provided:

   SocketSystem:
   -------------
   provides WinSock loading, unloading and a few program wide services.
   A recent change has ensured that the WinSock library is only loaded
   once, no matter how many times you construct SocketSystem objects.
   So now, the Socket class has a SocketSystem instance so you don't
   have to do an explicit creation of a SocketSystem object before
   creating a Socket.

   Socket:
   -------
   Provides connect request, string read, and string write service.
   
   SocketListener:
   ---------------
   Provides connection handling.
   
   Public Interface:
   =================
   SocketSystem sys;                          // load winsock lib
   SocketListener listener(2048);             // create listener
   Socket recvr = listener.waitForConnect();  // start listener listening
   Socket sendr;                              // create sending socket
   sender.connect("\\localhost",2048);        // request a connection
   const char* msg = "this is a message"; 
   sender.send(msg,strlen(msg)+1);            // send terminating null
   sender.send("quit",strlen("quit")+1);      // send another msg

   char* buffer[1024];                        // receive buffer
   recvr.recv(buffer,strlen(msg)+1);          // copy data when available
   std::cout << "\n  recvd: " << buffer;
   recvr.recv(buffer,strlen("quit")+1);       // get more data
   std::cout << "\n  recvd: " << buffer;

   recvr.disconnect();                        // graceful shutdown
   sender.disconnect();                       // graceful shutdown
*/
//
/*
   Build Process:
   ==============
   Required Files:
     Sockets.h, Sockets.cpp

   Compile Command:
   ================
   cl /EHsc /DTEST_SOCKETS Sockets.cpp wsock32.lib user32.lib

   Maintenance History:
   ====================
   ver 2.0 : 13 Apr 2010
   - made copy constructor and standard assignment operator private.
   - these operations can be made to work, but you need to duplicate
     the SOCKET handle to make the SOCKET object reference counting
     work as expected.  Not implemented yet.
   ver 1.9 : 05 May 2009
   - fixed bug, found by Phil Pratt-Szeliga, in 
     SocketListener::WaitForConnection() due to allowing a
     client handling thread to be created with an invalid socket.
     That was fixed in SocketListener::WaitForConnect().
   ver 1.8 : 04 Apr 08
   - discovered that WinSock connect function does not always return 
     appropriate error message on failure to connect (this is a new
     bug in WinSock, I believe) so added a remote port check, which
     returns -1 on failure to connect.
   ver 1.7 : 27 Mar 08
   - added throwing exception in socket.connect(...)
   ver 1.6 : -1 May 07
   - Estepan Meliksetian reported a problem with disconnect preventing a reconnect.
     This has been fixed by setting the socket s_ to INVALID_SOCKET in the disconnect
     function, and testing for INVALID_SOCKET in the connect function.
   ver 1.5 : 05 Apr 07
   - removed redundant Winsock socket initialization from Socket copy ctor.
     Bug reported by Vishal Chowdhary.
   ver 1.4 : 01 Apr 07
   - removed some commented code
   ver 1.3 : 27 Mar 07
   - added SocketSystem members to Socket and SocketListener
   ver 1.2 : 18 Feb 07
   - cosmetic changes
   ver 1.0 : 11 Feb 07
   - first release, a major rewrite of an earlier socket demo

*/
//
#include <string>
#include <winsock2.h>

/////////////////////////////////////////////////////////////////////
// SocketSystem class loads and unloads WinSock library
// and provides a few system services

class SocketSystem
{
public:
  SocketSystem();
  ~SocketSystem();
  std::string getHostName();
  std::string getNameFromIp(const std::string& ip);
  std::string getIpFromName(const std::string& name);
  std::string GetLastMsg(bool WantSocketMsg=true);

private:
  static bool loaded;
  static int count;
};

/////////////////////////////////////////////////////////////////////
// Socket class provides basic connect, read, and write operations

class Socket
{
public:
  Socket();
  //Socket(const Socket& sock);
  Socket(const std::string& url, int port);
  Socket(SOCKET s);
  ~Socket();
  //Socket& operator=(const Socket& sock);
  Socket& operator=(SOCKET sock);
  operator SOCKET ();
  bool connect(std::string url, int port, bool throwError=false);
  void disconnect();
  bool error() { return (s_ == SOCKET_ERROR); }
  bool send(const char* block, size_t len, bool throwError=false);
  bool recv(char* block, size_t len, bool throwError=false);
  std::string getRemoteIP();
  int getRemotePort();
  std::string getLocalIP();
  int getLocalPort();
  HANDLE getHandle() { return (HANDLE)s_; }
  long getSocketConnectionCount();

private:
  SOCKET s_;
  SocketSystem ss_;
  volatile long SocketConnectionCount;
};

inline long Socket::getSocketConnectionCount() 
{ 
  return SocketConnectionCount; 
}

/////////////////////////////////////////////////////////////////////
// SocketListener class waits for connections, then delivers
// connected socket

class SocketListener
{
public:
  SocketListener(int port);
  ~SocketListener();
  SOCKET waitForConnect();
  void stop();
  std::string getLocalIP();
  int getLocalPort();
  long getInvalidSocketCount();
private:
  SOCKADDR_IN tcpAddr;
  Socket s_;
  SocketSystem ss_;
  volatile long InvalidSocketCount;
};

inline long SocketListener::getInvalidSocketCount() 
{ 
  return InvalidSocketCount; 
}

#endif
