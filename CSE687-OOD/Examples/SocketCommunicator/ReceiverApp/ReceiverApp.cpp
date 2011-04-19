/////////////////////////////////////////////////////////////////////
// ReceiverApp.cpp - Demonstrates simple use of SocketCommunicator //
//                     Receives messages from SenderApp            //
// ver 1.1                                                         //
// Language:      Visual C++, 2008                                 //
// Platform:      Dell Dimension T7400, Win 7 Pro                  //
// Application:   Utility for CSE687 projects, Spring 2010         //
// Author:        Jim Fawcett, Syracuse University, CST 4-187      //
//                (315) 443-3948, jfawcett@twcny.rr.com            //
/////////////////////////////////////////////////////////////////////
/*
  Note:
  - This end starts receiving then when done starts sending.
  - Since we are running Sender and Receiver on same thread, we must 
    first do all our receiving then do all our sending.
  - There would be no such constraint if we ran sender and receiver on
    separate threads.
  - That is what you should do in Project #4.

  Maintenance History:
  ====================
  ver 1.1 : 17 Apr 11
  - added a Sender section to demonstrate two-way communication
  ver 1.0 : 16 Apr 10
  - first release
*/

#include "..\Communicator\comm.h"
#include <iostream>
#include <conio.h>

void main()
{
  std::cout << "\n  Starting ReceiverApp";
  std::cout << "\n ======================\n";

  /////////////////////////////////////////////////////////////
  // If another listener is using the port you specify, below,
  // the rcvr constructor will throw an exception, naming a
  // "bind error".

  try
  {
    Receiver rcvr(8000);
    Message msg;
    do
    {
      msg = rcvr.GetMsg();
      std::cout << "\n  Getting msg: " << msg.body();
    } while(msg.body() != "quit");

    std::cout << "\n\n  shutting down ReceiverApp Receiver";

    ///////////////////////////////////////////////////////////
    // The following lines prompt for shutdown:
       //std::cout << "\n  press key to exit: ";
       //std::cout.flush();
       //_getche();  // from conio.h
  }
  catch(std::exception& ex)
  {
    std::cout << "\n\n  " << ex.what();
  }

  std::cout << "\n  Starting sender";
  Sender sndr;
  int tryCount = 0, MaxTries = 5;
  std::string ip = "localhost";
  int port = 8010;
  while(++tryCount < MaxTries)
  {
    if(sndr.connect(EndPoint(ip,port)))
      break;
    Sleep(100);
    std::cout << "\n  failed attempt to connect to endpoint(" << ip.c_str() << ", " << port << ")";
  }
  if(tryCount < MaxTries)
  {
    std::string text = "Received your messages";
    Message msg;
    msg.body() = text;
    std::cout << "\n  Posting msg: " << msg.body();
    sndr.PostMsg(msg);
    /////////////////////////////////////////////////////////////
    // done msg shuts down Sender thread after it empties queue
    // quit msg shuts down both the Sender and Receiver threads

    Message endmsg("quit");
    sndr.PostMsg(endmsg);
    std::cout << "\n  Posted msg: " << endmsg.body();
    sndr.wait();
    std::cout << "\n\n  Shutting down ReceiverApp";
  }
  std::cout << "\n\n";
}