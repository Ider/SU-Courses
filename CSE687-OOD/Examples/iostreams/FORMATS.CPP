///////////////////////////////////////////////////////////
// formats.cpp                                           //
//   demonstrate ios formating                           //
//                                                       //
// Jim Fawcett, 24 Mar 96, modified 04 Mar 02            //
///////////////////////////////////////////////////////////

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

//----< display titles >---------------------------------------

void title(const char *t, char ul = '-', ostream &out = cout) {

  int len = strlen(t) + 2;
  string line(len,ul);
  if(ul == '=')
    out << "\n " << line;
  out << "\n  " << t
      << "\n " << line << endl;
}

//----< begin demonstration >----------------------------------

void main() {

  //////////////////////////////////////////
  title("Demonstrating ios formatting",'=');
  //////////////////////////////////////////

  title("formating integers");
  ////////////////////////////

  /////////////////////////////////////////////////////////////
  // flags:                                                  //
  //   skipws  showbase showpoint uppercase   showpos        //
  //  unitbuf     stdio                                      //
  /////////////////////////////////////////////////////////////
  //  basefield:                                             //
  //    dec       hex       oct                              //
  /////////////////////////////////////////////////////////////

  long save = cout.flags();    // save format state
  cout.setf(ios::showbase|ios::uppercase);
  cout << "  " << 59 << " in hexadecimal is "
       << hex  << 59 << dec << endl
       << "  " << 59 << " in octal is       "
       << oct  << 59 << dec << endl;
  cout.flags(save);            // restore original format state

//

  title("formating doubles");
  ///////////////////////////

  /////////////////////////////////////////////////////////////////
  // function:                                                   //
  //     width()     width(n)       fill()      fill(n)          //
  // precision() precision(n)                                    //
  /////////////////////////////////////////////////////////////////
  // floatfield:                                                 //
  //  scientific        fixed    automatic                       //
  /////////////////////////////////////////////////////////////////

  cout.precision(6);
  cout.setf(ios::right, ios::adjustfield);
  cout.setf(ios::scientific, ios::floatfield);
  cout.setf(ios::showpoint);
  double d = 9;
  int i;
  for(i=0; i<5; i++)
    cout << setw(14) << (d /= 3);
  cout << endl;
  cout.flags(save);

  title("adjust, fill, and width");
  /////////////////////////////////

  /////////////////////////////////////////////////////////////////
  // adjustfield:                                                //
  //        left        right     internal                       //
  /////////////////////////////////////////////////////////////////

  char *numbers[5] = { "zero", "one", "two", "three", "four" };
  int nums[5] = { 0, 1, 2, 3, 4 };
  cout.fill('.');
  for(i=0; i<5; i++) {
    cout.setf(ios::left, ios::adjustfield);
    cout << "  " << setw(30) << numbers[i];
    cout.setf(ios::right, ios::adjustfield);
    cout << setw(30) << nums[i] << endl;
  }
  cout.flags(save);

//

  title("stream manipulators");
  /////////////////////////////

  /////////////////////////////////////////////////////////////
  // manipulators:                                           //
  //   iostream.h -  dec, oct, hex, endl, ws, ends, flush,   //
  //   iomanip.h  -                                          //
  //     setfill(char), setw(int), setprecision(int),        //
  //     setiosflags(long), resetiosflags(long)              //
  /////////////////////////////////////////////////////////////

  cout << "  " << setprecision(5) << (d = 1.0/3.0) << endl;
  cout << "  " << setfill('.') << setw(20) << d << endl;
  cout << "  " << setiosflags(ios::left | ios::showpos)
       << setw(20) << d << endl;
  cout << "  " << resetiosflags(ios::left | ios::showpos)
        << d << endl;
  cout.flags(save);
  cout << endl;
}