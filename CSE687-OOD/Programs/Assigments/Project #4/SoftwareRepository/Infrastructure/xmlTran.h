#ifndef XMLTRAN_H
#define XMLTRAN_H
/////////////////////////////////////////////////////////////////////////
//  xmlTran.h    -  facility to create and parse xml strings           //
//  ver 1.3                                                            //
//  Language:       Visual C++, ver 6.0                                //
//  Platform:       Dell Dimension 9150, Windows XP Pro, SP2           //
//  Application:    CSE687 project help                                //
//  Author:         Jim Fawcett, CST 2-187, Syracuse University        //
//                  (315) 443-3948, jfawcett@twcny.rr.com              //
/////////////////////////////////////////////////////////////////////////
/*
    Module Operations
    =================
    xmlElem elem                          // create empty element
    xmlElem elem("tag","a body");         // create element
    elem.addAttrib("attrib=\"1\"");       // add an attribute expression
    elem.reviseBody("a new body");        // modify element body
    elem.reviseAttrib("new_attrib=\"1\"");// modify element attrib
    elem.reviseTagName("newTagName");     // modify element name
    strVal tag = xmlElem::makeTag("tagName","attrib=\"1\""); // create tag
    strVal str = elem.tagName();          // retrieve tag name
    strVal str = elem.attribExpression(); // retrieve attribute expression
    strVal str = elem.body();             // retrieve body
    strVal str = elem.flush();            // return XML string then empty it
    strRef str = elem.elemStr();          // return reference to XML string
    strVal str = (strVal)elem;            // cast elem to string value
    strVal str = elem.format();           // create indented display string
    cout << elem << endl;                 // display element string

    xmlRep rep;                           // create empty rep element
    xmlRep rep(xmlString);                // wrap rep around XML string
    xmlElem elem = rep.makeParent(tag);   // wrap and return as xmlElem
    rep.addSibling(el1).addSibling(el2);  // concatenate xmlElems, store
    rep.makeDoc();                        // prepend XML banner tag
    if(rep.find(tag,elemRef))  { ... }    // if find tag extract into elem
    if(rep.firstTag(tagRef))   { ... }    // if find a first tag extract it
    while(rep.nextTag(tagRef)) { ... }    // if find another tag extract it
    strPos pos = rep.findFirstTag(tagRef);// return position of first tag
    strPos pos = rep.findNextTag(tagRef); // return position of tag, extract
    strPos pos = rep.findCloseTag(tag);   // find "/tag" which closes "tag"
    if(rep.firstElem(elemRef))   { ... }  // extract first XML element
    while(rep.nextElem(elemRef)) { ... }  // extract succeeding XML elements
    elemColl coll = rep.makeCollection(); // return vector of all xmlElems
    strVal str = rep.flush();             // return XML string, then empty
    strRef str = rep.xmlStr();            // return reference to XML string
    strVal str = (strVal)rep;             // cast rep to XML string
    strVal str = rep.format();            // return indented XML string
    xmlType  t = rep.type();              // --- not implemented yet ---
    cout << rep << endl;                  // display XML string
*/
//
///////////////////////////////////////////////////////////////////////////
//  Build Process                                                        //
///////////////////////////////////////////////////////////////////////////
//  Required Files:                                                      //
//    xmlTran.h, xmlTran.cpp                                             //
//                                                                       //
//  Compiler Command:                                                    //
//    cl /GX /DTEST_XMLTRAN xmlTran.cpp                                  //
//                                                                       //
///////////////////////////////////////////////////////////////////////////
/*
    Maintenance History
    ===================
    ver 1.3 : 22 Feb 06
      - fixed bug in nextTag() that caused crash when searching for tag
        that did not exist
    ver 1.2 : 10 Nov 01
      - fixed bug in xmlElem constructor that put attributes into end tag
    ver 1.1 : 22 Sep 01
      - fixed bug in findCloseTag, e.g., search should start at current
        position, not at beginning.  The changed line is shown below.
        strPos pos = _xmlStr.find(temp,current);
        Bug analyzed and reported by Arjun Nautiyal - Thanks Arjun
    ver 1.0 : 19 Sep 01
      - first release
*/

#include <string>
#include <vector>
#include <iostream>

typedef const std::string& conStrRef;
typedef std::string& strRef;
typedef std::string strVal;
typedef std::string::size_type strPos;
typedef std::string::iterator  strIter;

class xmlElem {

  public:
    xmlElem();
    xmlElem(conStrRef tag, conStrRef body);
    void reviseBody(conStrRef body);
    void reviseAttrib(conStrRef attrib);
    void reviseTagName(conStrRef tagName);
    static strVal makeTag(conStrRef tagName, conStrRef attrib="");
    void addAttrib(conStrRef attrib);
    operator strVal ();
    strVal tagName();
    strVal attribExpression();
    strVal body();
    strVal flush();
    strRef elemStr();
    strVal format();

  protected:
    strVal _elemStr;
};

inline std::ostream& operator<<(std::ostream& out, xmlElem &el) {

  out << strVal(el);
  return out;
}
 
//

typedef std::vector<xmlElem> elemColl;

enum xmlType { notXML=0, sibling=1, root=2, document=3 };

class xmlRep {

  public:
    xmlRep();
    xmlRep(conStrRef s);
    operator strVal ();
    xmlType type();
    xmlElem makeParent(conStrRef tag);
    xmlRep& addSibling(xmlElem elem);
    void makeDoc();
    strVal flush();
    strRef xmlStr();
    bool find(strRef tag, xmlElem &elem);
    bool firstTag(strRef tag);
    bool nextTag(strRef tag);
    strPos findFirstTag(strRef tag);
    strPos findNextTag(strRef tag);
    strPos findCloseTag(conStrRef tag);
    bool firstElem(xmlElem &elem);
    bool nextElem(xmlElem &elem);
    elemColl makeCollection();
    strVal format();
    void front();

protected:
    strVal _xmlStr;
    strPos current;
};

inline std::ostream& operator<<(std::ostream& out, xmlRep &rep) {

  out << strVal(rep).c_str();
  return out;
}

#endif
