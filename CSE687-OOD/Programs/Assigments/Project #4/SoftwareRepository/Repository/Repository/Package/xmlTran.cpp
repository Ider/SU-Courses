/////////////////////////////////////////////////////////////////////////
//  xmlTran.cpp  -  facility to create and parse xml strings           //
//  ver 1.3                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       Dell Dimension 9150, Windows XP Pro, SP2           //
//  Application:    CSE687 project help                                //
//  Author:         Jim Fawcett, CST 2-187, Syracuse University        //
//                  (315) 443-3948, jfawcett@twcny.rr.com              //
/////////////////////////////////////////////////////////////////////////

#include <algorithm>  // _MIN (Visual C++ does not conform to std::min)
#include "xmlTran.h"
using namespace std;

//----< build element start tag >----------------------------------------

strVal xmlElem::makeTag(conStrRef tagName, conStrRef attrib) {

  strVal tag = "<";
  tag += tagName;
  tag += attrib.size()>0?(" "+attrib):"";
  tag += '>';
  return tag;
}

//----< insert attribute expression string after tagName >---------------

void xmlElem::addAttrib(conStrRef attrib) {

  if(_elemStr.size() > 0) {
    string::size_type pos = _elemStr.find('>');
    if(pos < _elemStr.size())
      _elemStr.insert(pos,1,' ');
      _elemStr.insert(pos+1,attrib);
  }
}

//

//----< construct empty element >----------------------------------------

xmlElem::xmlElem() { }

//----< construct element with specified tag and body >------------------

xmlElem::xmlElem(conStrRef tag, conStrRef body) { 

  string temp;
  if(tag[0] != '<')
    temp = makeTag(tag);
  else
    temp = tag;
  _elemStr = temp + body;
  string end = "</";
  int i = 1;
  while(temp[i] != ' ' && temp[i] != '>')
    end += temp[i++];
  end += '>';
  _elemStr += end;
}

//----< revise tagName >-------------------------------------------------

void xmlElem::reviseTagName(conStrRef tagName) {

  xmlElem temp(tagName,body());
  temp.addAttrib(attribExpression());
  _elemStr = temp.elemStr();
}

//----< revise attribute expression >------------------------------------

void xmlElem::reviseAttrib(conStrRef attrib) {

  xmlElem temp(tagName(),body());
  temp.addAttrib(attrib);
  _elemStr = temp.elemStr();
}

//----< revise body >----------------------------------------------------

void xmlElem::reviseBody(conStrRef body) {

  xmlElem temp(tagName(),body);
  temp.addAttrib(attribExpression());
  _elemStr = temp.elemStr();
}

//

//----< extract tagName from element >-----------------------------------

strVal xmlElem::tagName() {
  
  string::size_type start = _elemStr.find('<');
  string::size_type end1  = _elemStr.find(' ');
  string::size_type end2  = _elemStr.find('>');
  string::size_type end   = std::min(end1,end2);
//  string::size_type end   = _MIN(end1,end2);
  if(start > _elemStr.size() || end > _elemStr.size() || end < start)
    return "";
  string::iterator iStart = _elemStr.begin()+start+1;
  string::iterator iEnd   = _elemStr.begin()+end;
  return string(iStart,iEnd); 
}

//----< extract attribute expression from element (may be empty) >-------

strVal xmlElem::attribExpression() {
  
  string::size_type start = _elemStr.find(' ');
  string::size_type end   = _elemStr.find('>');
  if(start > _elemStr.size() || end > _elemStr.size() || end < start)
    return "";
  string::iterator iStart = _elemStr.begin()+start+1;
  string::iterator iEnd   = _elemStr.begin()+end;
  return string(iStart,iEnd);
}

//----< extract body from element >--------------------------------------

strVal xmlElem::body() {
  
  string::size_type start = _elemStr.find('>');
  string::size_type end   = _elemStr.find_last_of('<');
  if(start > _elemStr.size() || end > _elemStr.size() || end < start)
    return "";
  string::iterator iStart = _elemStr.begin()+start+1;
  string::iterator iEnd   = _elemStr.begin()+end;
  return string(iStart,iEnd);
}

//

//----< return copy of internal XML string >-----------------------------

xmlElem::operator strVal () { return _elemStr; }

//----< return XML string and make it empty >----------------------------

strVal xmlElem::flush() {

  string temp = _elemStr;
  _elemStr = "";
  return temp;
}

//----< return reference to internal XML string >------------------------

strRef xmlElem::elemStr() { return _elemStr; }

//

//----< build XML string with indented format >--------------------------

strVal xmlElem::format() {

  enum moveType { left, right } lastMove = right;
  string temp = _elemStr;
  int level = 0;
  strPos pos = 0;
  strVal fmtStr;
  while((pos = temp.find('<',pos)) < temp.size()) {
    if(temp[pos+1] != '/') {
      level++;
      fmtStr = "\n";
      fmtStr += string(3*level,' ');
      pos = temp.find('>',pos);
      temp.insert(++pos,fmtStr);
      lastMove = right;
    }
    else {
      level--;
      fmtStr = "\n";
      fmtStr += string(3*level,' ');
      if(pos < temp.size())
        temp.insert(pos,fmtStr);
      pos = temp.find('>',pos);
      if(pos+2 < temp.size() && temp[pos+2] != '/')
        temp.insert(++pos,fmtStr);
      lastMove = left;
    }
  }
  return temp;
}

//

//----< default construction of xmlRep object >--------------------------

xmlRep::xmlRep() : current(0) { }

//----< construction of xmlRep object from XML string >------------------

xmlRep::xmlRep(conStrRef s) : _xmlStr(s), current(0) { }

//----< cast xmlRep to XML string >--------------------------------------

xmlRep::operator strVal () { return _xmlStr; }

//----< concatenate elem with the current xml representation >-----------

xmlRep& xmlRep::addSibling(xmlElem elem) { 
  
  _xmlStr += (strVal)elem; 
  return *this;
}

//----< wrap a set of siblings with parent tags >------------------------
  
xmlElem xmlRep::makeParent(conStrRef tag) {

  string temp = xmlElem::makeTag(tag);
  _xmlStr = temp + _xmlStr;
  temp.insert(1,1,'/');
  _xmlStr += temp;
  xmlElem elem;
  elem.elemStr() = _xmlStr;   // assign _xmlStr to xmlElem::_elemStr
  return elem;
}

//----< prepend a root element with the xml header >---------------------

void xmlRep::makeDoc() {

  string xmlTag = "<?xml version=\"1.0\" ?>";
  _xmlStr = xmlTag + _xmlStr;
}

//

//----< return XML string and empty repStr >-----------------------------

strVal xmlRep::flush() {

  strVal temp = _xmlStr;
  _xmlStr = "";
  current = 0;
  return temp;
}

//----< return reference to internal XML string >------------------------
  
strRef xmlRep::xmlStr() {

  return _xmlStr;
}

//----< set internal index to beginning of XML string >------------------

void xmlRep::front() { current = 0; }

//----< find 2nd or later tag in XML representation >--------------------

bool xmlRep::nextTag(strRef tag) {

  strPos pos = _xmlStr.find("<",current);
  if(pos >= _xmlStr.size())
    return false;
  if(_xmlStr.size() == pos+1)
    return false;
  while(_xmlStr[pos+1] == '?' || _xmlStr[pos+1] == '/')
    pos = _xmlStr.find("<",pos+1);
  if(pos >= _xmlStr.size())
    return false;
  if(_xmlStr.size() == pos+1)
    return false;
  string::iterator start = _xmlStr.begin() + pos + 1;
  string::iterator end = start;
  while(*end != '>' && *end != ' ')
    end++;
  tag = string(start,end);
  if(pos + static_cast<size_t>(end - start) <= current)
    current = pos + end - start;
  else
    return false;
  const char *debug = _xmlStr.c_str() + current + 1;
  return true;
}

//----< find 1st tag in XML representation >-----------------------------

bool xmlRep::firstTag(strRef tag) {

  front();
  return nextTag(tag);
}

//

//----< find 2nd or later tag >------------------------------------------

strPos xmlRep::findNextTag(strRef tag) {

  strPos pos = _xmlStr.find("<",current);
  if(pos >= _xmlStr.size())
    return _xmlStr.size();
  while(_xmlStr[pos+1] == '?' || _xmlStr[pos+1] == '/')
    pos = _xmlStr.find("<",pos+1);
  if(pos >= _xmlStr.size())
    return _xmlStr.size();
  current = pos + 1;
  string::iterator start = _xmlStr.begin() + pos + 1;
  string::iterator end = start;
  while(*end != '>' && *end != ' ')
    end++;
  tag = string(start,end);
  return pos;
}

//----< find 1st tag >---------------------------------------------------

strPos xmlRep::findFirstTag(strRef tag) {

  front();
  return findNextTag(tag);
}

//----< find an element, specified by its tag >--------------------------

bool xmlRep::find(strRef tag, xmlElem &elem) {
  strVal temp  = "<"+tag;
  strVal foundTag; 
  strPos start = -temp.size();
  do
  {  
	  start = _xmlStr.find(temp,start+temp.size());
	  if(start >= _xmlStr.size())
		  return false;
	  strPos end1  = _xmlStr.find(' ',start);
	  strPos end2  = _xmlStr.find('>',start);
	  strPos end   = std::min(end1,end2);
	  if(start > _xmlStr.size() || end > _xmlStr.size())
		  return false;
	  foundTag = _xmlStr.substr(start,end-start);
  }while(temp != foundTag);

  strPos end = findCloseTag(tag);
  if(end > _xmlStr.size())
    return false;
  if(end <= start)
    return false;
  strIter iStart = _xmlStr.begin() + start;
  strIter iEnd   = _xmlStr.begin() + end;
  
  elem.elemStr() = strVal(iStart,iEnd);
  return true;
}

//

//----< find the closing tag of a specified tag >------------------------

strPos xmlRep::findCloseTag(conStrRef tag) {

  string temp = "</"+ tag + ">";
  //temp += tag;

  strPos pos = _xmlStr.find(temp,current);
  return _xmlStr.find('>',pos) + 1;
}

//----< find 2nd or later element in XML representation >----------------

bool xmlRep::nextElem(xmlElem &elem) {

  strVal tag;
  strPos start = findNextTag(tag);
  if(start >= _xmlStr.size())
    return false;
  strPos end   = findCloseTag(tag);
  if(end > _xmlStr.size() || end < start)
    return false;
  strIter iStart = _xmlStr.begin() + start;
  strIter iEnd   = _xmlStr.begin() + end;
  strVal temp(iStart,iEnd);
  elem.elemStr() = temp;
  return true;
}

//----< find 1st element in XML representation >-------------------------

bool xmlRep::firstElem(xmlElem &elem) {

  front();
  return nextElem(elem);
}

//----< find a collection (vector) of all elements >---------------------

elemColl xmlRep::makeCollection() {

  elemColl elems;
  xmlElem elem;
  if(firstElem(elem))
    elems.push_back(elem);
  while(nextElem(elem))
    elems.push_back(elem);
  return elems;
}

//

//----< indent XML string according to the level of its elements >-------

strVal xmlRep::format() {

  enum moveType { left, right } lastMove = right;
  string temp = _xmlStr;
  int level = 0;
  strPos pos = 0;
  strVal fmtStr;
  while((pos = temp.find('<',pos)) < temp.size()) {
    if(temp[pos+1] != '/') {
      level++;
      fmtStr = "\n";
      fmtStr += string(3*level,' ');
      pos = temp.find('>',pos);
      temp.insert(++pos,fmtStr);
      lastMove = right;
    }
    else {
      level--;
      fmtStr = "\n";
      fmtStr += string(3*level,' ');
      if(pos < temp.size())
        temp.insert(pos,fmtStr);
      pos = temp.find('>',pos);
      if(pos+2 < temp.size() && temp[pos+2] != '/')
        temp.insert(++pos,fmtStr);
      lastMove = left;
    }
  }
  return temp;
}

//----< return xmlRep type, e.g., document, root, sibling, notXML >------

xmlType xmlRep::type() {

  throw "not implemented yet";
}

//

//----< test stub >------------------------------------------------------

#ifdef TEST_XMLTRAN

#include <iostream>
#include <iomanip>
using namespace std;

//----< create an indented string with an underline >--------------------

strVal subtitle(const string &msg, char underChar='-') {

  string under = string(msg.size()+2,underChar);
  string body = "\n   ";
  body += msg;
  body += "\n  ";
  body += under;
  body += '\n';
  return body;
}

//----< create a string with both over and under lines >-----------------

strVal title(const string &msg, char underChar='-') {

  string over = "\n";
  over += string(msg.size()+2,underChar);
  string under = string(msg.size()+2,underChar);
  string body = "\n ";
  body += msg;
  body += "\n";
  body += under;
  body += '\n';
  return over + body;
}

//

//----< entry point for test >-------------------------------------------

void main() {

//------------------------------------------------------
  cout << title("Testing XML Creation and Parsing",'=');
//------------------------------------------------------

  cout << subtitle("test xml element construction and de-construction");
//-------------------------------------------------------------------------
  string tag = xmlElem::makeTag("myTag1");
  xmlElem el1(tag,"this is the body of myTag1");
  cout << el1 << endl;
  cout << "tag:    " << el1.tagName() << endl;
  cout << "attrib: " << el1.attribExpression() << endl;
  cout << "body:   " << el1.body() << endl;

  cout << "\n";
  xmlElem el2("myTag2","body of myTag2");
  el2.addAttrib("attrib = \"0\"");
  cout << el2 << endl;
  cout << "tag:    " << el2.tagName() << endl;
  cout << "attrib: " << el2.attribExpression() << endl;
  cout << "body:   " << el2.body() << endl;

//

//-------------------------------------------
  cout << title("testing xmlElem revisions");
//-------------------------------------------

  cout << subtitle("test tag revision");
//--------------------------------------
  el2.reviseTagName("myNewTag2");
  cout << el2 << endl;

  cout << subtitle("test attrib revision");
//-----------------------------------------
  el2.reviseAttrib("newAttrib=\"1\"");
  cout << el2 << endl;

  cout << subtitle("test body revision");
//---------------------------------------
  el2.reviseBody("new body for myTag2");
  cout << el2 << endl;

  cout << subtitle("test revision of empty element");
  xmlElem el3;
  el3.reviseTagName("wasEmpty");
  cout << "revised tagName:  " << el3 << endl;

  xmlElem el4;
  el4.reviseAttrib("attrib=\"wasEmpty\"");
  cout << "revised attrib:   " << el4 << endl;

  xmlElem el5;
  el5.reviseBody("this body wasEmpty");
  cout << "revised body:     " << el5 << endl;

//--------------------------------------------
  cout << title("test formatting of xmlElem");
//--------------------------------------------
  cout << el2.format() << '\f' << endl;

//

//-------------------------------------------------
  cout << title("testing creation of XML strings");
//-------------------------------------------------

  cout << subtitle("test addSibling:");
//-------------------------------------
  xmlRep rep1;
  rep1.addSibling(el1).addSibling(el2);
  el2.reviseBody("this element has same tag as previous");
  rep1.addSibling(el2);
  cout << rep1 << endl;

  cout << subtitle("test creation of parent:");
//---------------------------------------------
  rep1.makeParent("parent");
  cout << rep1 << endl;
  
  cout << subtitle("test creation of document:");
//-----------------------------------------------
  rep1.makeDoc();
  cout << rep1 << endl;

//

//-------------------------------------------
  cout << title("test finding XML elements");
//-------------------------------------------

  cout << subtitle("test find(tag,elem)");
//----------------------------------------
  xmlElem newEl;
  tag = "myTag1";
  if(rep1.find(tag,newEl))
    cout << newEl.format() << "\n\n";
  else
    cout << "could not find " << tag << "\n\n";

  tag = "myNewTag2";
  if(rep1.find(tag,newEl))
    cout << newEl.format() << "\n\n";
  else
    cout << "could not find " << tag << "\n\n";

  tag = "parent";
  if(rep1.find(tag,newEl))
    cout << newEl.format() << "\n\n";
  else
    cout << "could not find " << tag << "\n\n";

  tag = "notExist";
  if(rep1.find(tag,newEl))
    cout << newEl.format() << "\f\n";
  else
    cout << "could not find " << tag << "\f\n";

  cout << subtitle("test bool nextTag(strRef tag)");
//--------------------------------------------------
  rep1.firstTag(tag);
  cout << tag << endl;
  while(rep1.nextTag(tag))
    cout << tag << endl;

//

  cout << subtitle("test strPos findNextTag(strRef tag)");
//--------------------------------------------------------
  strPos pos = rep1.findFirstTag(tag);
  cout << "pos: " << setw(2) << pos << ", tag: " << tag << endl;
  pos = rep1.findCloseTag(tag);
  cout << "pos: " << setw(2) << pos << ", closing tag" << endl;
  while((pos = rep1.findNextTag(tag)) < rep1.xmlStr().size()) {
    cout << "pos: " << setw(2) << pos << ", tag: " << tag << endl;
    pos = rep1.findCloseTag(tag);
    cout << "pos: " << setw(2) << pos << ", closing tag" << endl;
  }

  cout << subtitle("test bool nextElem(xmlElem &elem)");
//------------------------------------------------------
  if(rep1.firstElem(newEl))
    cout << newEl.format() << "\n\n";
  while(rep1.nextElem(newEl))
    cout << newEl.format() << "\n\n";

//--------------------------------------------
  cout << title("test formatting XML string");
//--------------------------------------------
  cout << rep1.format().c_str() << '\f' << endl;

//-------------------------------------------------
  cout << title("test makeCollection of elements");
//-------------------------------------------------
  elemColl collection = rep1.makeCollection();
  for(size_t i=0; i<collection.size(); i++)
    cout << collection[i] << endl;

//

//----------------------------------------------------------------
  cout << title("test creation of relatively complex XML string");
//----------------------------------------------------------------

  xmlElem title("title","Exec");
  xmlElem respon("responsiblities:","To Be Determined");
  xmlElem collab("collaborators:","To Be Determined");
  xmlRep temp;
  temp.addSibling(title).addSibling(respon).addSibling(collab);
  xmlElem crc1 = temp.makeParent("crc");

  title.reviseBody("CRCProc");
  temp.flush();
  temp.addSibling(title).addSibling(respon).addSibling(collab);
  xmlElem crc2 = temp.makeParent("crc");

  xmlRep crcColl;
  crcColl.addSibling(crc1).addSibling(crc2);
  crcColl.makeParent("CRC_Collection");
  crcColl.makeDoc();
  cout << crcColl.format() << endl;
  
  cout << "\n\n";
}

#endif

