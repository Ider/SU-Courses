/////////////////////////////////////////////////////////////////////
//  locks.cpp     - classes supporting synchronization of shared   //
//  ver 1.4         objects                                        //
//                                                                 //
//  Language:       Visual C++, ver 7.1, SP 2                      //
//  Platform:       Dell Dimension 8300, Win XP, SP2               //
//  Application:    CSE687 - Object Oriented Design                //
//  Author:         Jim Fawcett, CST 2-187, Syracuse Univ          //
//                  (315) 443-3948, jfawcett@twcny.rr.com          //
//                                                                 //
/////////////////////////////////////////////////////////////////////


#include "locks.h"


//----< globally available output stream >---------------------------

syncOut sout(std::cout);  // globally available sout object
                          // mimics cout

#ifdef TEST_LOCKS

#include "threads.h"
#include <string>
#include <sstream>
using namespace std;

//----< helper conversion function >---------------------------------

template <typename T>
std::string ToString(const T& t)
{
  std::ostringstream converter;
  converter << t;
  return converter.str();
}

//
/////////////////////////////////////////////////////////////////////
// thread processing that shares a locked string

class sharedString1 : public processing
{
public:
  sharedString1() : myCount(++count) {}
  processing* clone() { return new sharedString1(*this); }
  void run()
  {
    const string blanks(41,' ');
    for(int i=0; i<10; ++i)
    {
      gl.lock();
      if(shared.length() > 10)
      {
        cout << "\n  " << blanks;
        shared = "";
      }
      shared += ToString(myCount);
      cout << "\n  " << shared;
      gl.unlock();
    }
  }
private:
  static int count;
  int myCount;
  static std::string shared;
  GLock<1> gl;
};

int sharedString1::count = 0;
std::string sharedString1::shared = "";

//
/////////////////////////////////////////////////////////////////////
// thread processing that shares a string using lockingPtr

class sharedString2 : public processing
{
public:
  sharedString2() : myCount(++count) {}
  processing* clone() { return new sharedString2(*this); }
  void addString(const std::string& str)
  {
    shared += str;
  }
  void clearString()
  {
    shared = "";
  }
  void run()
  {
    const string blanks(41,' ');
    for(int i=0; i<10; ++i)
    {
      if(shared.length() > 10)
      {
        sout << locker << "\n  " << blanks << unlocker;
        lockingPtr< sharedString2, GLock<1> >(*this,gl)->clearString();
      }
      lockingPtr< sharedString2, GLock<1> >(*this,gl)
        ->addString(ToString(myCount));
      sout << locker << "\n  " << shared << unlocker;
    }
  }
private:
  static int count;
  int myCount;
  static std::string shared;
  GLock<1> gl;
};

int sharedString2::count = 0;
std::string sharedString2::shared = "";

//
//----< test stub >--------------------------------------------------

void main() {

  cout << "\n  Demonstrating locks and lockingPtr classes   "
       << "\n ============================================\n";

  cout.flush();
  sout << locker
       <<"\n  Demonstrating string sharing between threads "
       << "\n ---------------------------------------------\n"
       << unlocker;

  // Create processing objects, defined above,
  // then create and start threads.

  std::cout << "\n  using Glock<1> for synchronization";
  sharedString1 ss1, ss2;
  thread t5(&ss1);
  thread t6(&ss2);
  t5.start();
  t6.start();
  t5.wait();
  t6.wait();
  std::cout << "\n\n";

  std::cout << "\n  using lockingPtr for synchronization";
  sharedString2 ss3, ss4;
  thread t7(&ss3);
  thread t8(&ss4);
  t7.start();
  t8.start();
  t7.wait();
  t8.wait();
  std::cout << "\n\n";
}

#endif
