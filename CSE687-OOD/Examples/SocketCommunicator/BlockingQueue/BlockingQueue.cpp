/////////////////////////////////////////////////////////////////////
//  blockingQueue.cpp - queue that blocks on deQ of empty queue    //
//  ver 1.2                                                        //
//  Language:       Visual C++, ver 7.1, SP 2                      //
//  Platform:       Dell Dimension 8300, Win XP Pro, SP2           //
//  Application:    CSE687 - Object Oriented Design                //
//  Author:         Jim Fawcett, CST 2-187, Syracuse Univ          //
//                  (315) 443-3948, jfawcett@twcny.rr.com          //
//                                                                 //
/////////////////////////////////////////////////////////////////////

#ifdef TEST_BLOCKINGQUEUE

#include "blockingQueue.h"
#include "..\threads\threads.h"
#include "..\threads\locks.h"
#include <sstream>
using namespace std;

/////////////////////////////////////////////////////////////////////
// Check thread module test stub for tests of blocking queue with
// threads.

class threadproc : public Thread_Processing<threadproc>
{
public:
  threadproc(BQueue<std::string>& Q) : _Q(Q) {}
  void run()
  {
    sout << "\n  starting child thread";
    std::string msg;
    do
    {
      msg = _Q.deQ();
      sout << locker << "\n  received msg: " << msg << unlocker;
    } while(msg != "quit");
  }
private:
  BQueue<std::string>& _Q;  // note reference
};

class globalLineFeed
{
public:
  ~globalLineFeed() { std::cout << "\n\n"; }
} globalInstance;

void main() {

  cout << "\n  Demonstrating basic Queue operations with the BlockingQueue<T> class "
       << "\n ======================================================================\n";

  BQueue<int> intQ;
  intQ.enQ(1);
  intQ.enQ(2);
  intQ.enQ(3);

  BQueue<int> intQ2 = intQ;
  cout << "\n  copy construction: intQ2.size() = " << intQ2.size();
  intQ2.clear();
  cout << "\n  after intQ2.clear(), intQ2.size() = " << intQ2.size();

  BQueue<int> intQ3;
  intQ3 = intQ;
  cout << "\n  after assignment: intQ3.size() = " << intQ3.size();

  cout << "\n  intQ3 contents: " 
       << intQ3.deQ() << "," << intQ3.deQ() << "," << intQ3.deQ() << "\n\n";

  cout << "\n  Demonstrating BlockingQueue<T> message handling "
       << "\n =================================================\n";

  BQueue<std::string> sQ;
  threadproc tp(sQ);
  thread th(tp);
  th.start();
  std::string msg;
  ostringstream out;

  for(int i=0; i<20; ++i)
  {
    out.str("");
    out << i;
    msg = std::string("msg #") + out.str() + std::string(" - a message");
    sout << locker << "\n  sending msg \"" << msg << "\"" << unlocker;
    sQ.enQ(msg);
  }
  msg = std::string("quit");
  sout << locker << "\n  sending msg \"" << msg << "\"" << unlocker;
  sQ.enQ(msg);
  th.wait();
}

#endif

