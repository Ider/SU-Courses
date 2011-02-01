///////////////////////////////////////////////////////////////
//  algo1.cpp - demonstrate fill algorithms on several       //
//              types of containers                          //
//                                                           //
//  Jim Fawcett, 4/5/98                                      //
///////////////////////////////////////////////////////////////

#include <iostream>
#include <algorithm>    // fill, fill_n, copy
#include <iterator>     // ostream_iterator
#include <list>
#include <string>

using namespace std;

void main() {

  /////////////////////////////////////////////////////
  // container is char array, iterator is char *ptr  //
  /////////////////////////////////////////////////////

  char buffer[70], *buffit = buffer;
  fill(buffit, buffit+70, '\0');
  *buffit++ = ' ';
  *buffit++ = ' ';
  fill_n(buffit, 10, 'z');
  buffit = buffer;
  cout << buffer << endl;

  //////////////////////////////////////////////////////
  //  container is a list of strings,                 //
  //    iterators from container and                  //
  //    stream iterator from <iterator>               //
  //////////////////////////////////////////////////////

  list<string> aList;
    // inserting elements on list
  fill_n(inserter(aList, aList.begin()), 10, "a string\n");
    // now overwrite list elements
  list<string>::iterator temp = aList.begin();
  temp++; temp++; temp++;
  fill(temp,aList.end(), "  overwritten with new string\n");
    // use stream iterator for copy to cout
  ostream_iterator<string> outString(cout);
  copy(aList.begin(), aList.end(), outString);

}