#ifndef XMLNodes_H
#define XMLNodes_H
///////////////////////////////////////////////////////////////////////////
// XmlNodes.h - Nodes that represent parts of an XML document            //
// ver 3.1                                                               //
// Language:    Visual C++, 2008                                         //
// Platform:    Dell Precision T7400, Vista Ultimate, SP1                //
// Application: CSE687 - Demo for Project #1, Spring 2009                //
// Author:      Jim Fawcett, Syracuse University, CST 4-187,             //
//              (315) 443-3948, jfawcett@twcny.rr.com                    //
///////////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * Provides an XmlNode class that holds a finite number of pointers
 * to child nodes, and a visitation predicate. 
 *
 * Note: if you accidentally attempt to make a node a child of itself,
 * than addChild(pChild) throws an exception.
 * 
 * Build Process:
 * ==============
 * cl /D:TEST_XMLNODES XmlNodes.cpp
 * 
 * Maintenance History:
 * ====================
 * ver 3.1 : 06 Apr 11
 * - Changed XmlNodes code use the IXmlNode interface
 * ver 3.0 : 25 Apr 10
 * - Extracted interface IXmlNode in IXmlDocument.h
 * - Provided XmlNodeFactory in XmlDocumentFactories.cpp
 * - small refactoring and code changes to support use of interface.
 * ver 2.3 : 18 Mar 10
 * - added check in XmlProcInstrNode::addAttribute(...) for invalid attribute
 * ver 2.2 : 14 Mar 10
 * - Changed XmlElementNode::ToString() and XmlElementNode::ToEndString()
 *   to keep self-closing tags self-closed.  Version 2.1 expanded them to
 *   correct but not self-closed elements.
 * ver 2.1 : 27 Feb 10
 * - added several new member functions needed to satisfy requirements of
 *   Project #1.
 * ver 2.0 : 12 Feb 10
 * - created XmlNode Hierarchy:
 *   XmlNode, XmlTextNode, XmlCommentNode, XmlProcInstrNode, XmlElementNode
 * - added functionality specific to each type
 * - added copy construction and assignment
 * ver 1.0 : 31 Jan 10
 * - first release
 */

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include "IXmlDocument.h"

namespace XmlProcessing
{
  /////////////////////////////////////////////////////////////////////////
  // Base XmlNode class

  class XmlNode : public IXmlNode
  {
  public:
    //typedef std::pair<std::string,std::string> attributeItem;
    XmlNode(const std::string& t);
    virtual ~XmlNode();
    // Compiler generated copy and assignment are correct for XmlNode.
    virtual IXmlNode* clone();
    std::string& value();
    virtual std::string ToString();
    virtual std::string ToEndString();
    virtual std::string Type();
    static bool& verbose();
    static bool& onStack();
    // interface for children
    virtual void addChild(IXmlNode* pXmlNode);
    virtual bool removeChild(IXmlNode* pXmlNode);
    virtual size_t numChildren();
    virtual std::vector<IXmlNode*>& getChildren();
    virtual IXmlNode* nextUnmarkedChild();
    virtual void clearMarks();
    // interface for attributes
    virtual void addAttribute(const std::string& name, const std::string& value);
    virtual attributeItem attribute(size_t index);
    virtual std::vector<XmlNode::attributeItem>& getAttributes();
    virtual bool removeAttribute(const std::string& name, const std::string& value);
    virtual size_t numAttributes();
  protected:
    std::string tag;
    std::string type;
    static bool verbose_;
    static bool onStack_;
    static std::vector<IXmlNode*> emptyChildren;
    static std::vector<attributeItem> emptyAttributes;
  };

  //----< make copy of self >----------------------------------------------

  inline IXmlNode* XmlNode::clone() { return new XmlNode(*this); }

  //----< construct accepts value, can be used as void ctor >--------------

  inline XmlNode::XmlNode(const std::string& t) : tag(t), type("XmlNode") {};

  //----< destructor has optional display >--------------------------------

  inline XmlNode::~XmlNode()
  {
    if(verbose())
      std::cout << "\n -- destroying " << value();
  }
  //----< set verbose to true or false >-----------------------------------

  inline bool& XmlNode::verbose() { return verbose_; }

  //----< set onStack to true or false: affects destruction >--------------

  inline bool& XmlNode::onStack() { return onStack_; }

  //----< return instance of template type >-------------------------------

  inline std::string& XmlNode::value() { return tag; }

  //----< return type name >-----------------------------------------------

  inline std::string XmlNode::Type() { return type; }

  //----< add child node is empty operation >------------------------------

  inline void XmlNode::addChild(IXmlNode* pXmlNode) {}

  //----< remove child node is empty operation >---------------------------

  inline bool XmlNode::removeChild(IXmlNode* pXmlNode) { return false; }

  //----< return number of children, always zero >-------------------------

  inline size_t XmlNode::numChildren() { return 0; }

  //----< return vector of children >--------------------------------------

  inline std::vector<IXmlNode*>& XmlNode::getChildren() { return emptyChildren; }

  //----< get next unmarked child is empty operation >---------------------

  inline IXmlNode* XmlNode::nextUnmarkedChild() { return 0; }

  //----< clear marks on children is empty operation >---------------------

  inline void XmlNode::clearMarks() {}

  //----< add attribute does nothing >-------------------------------------

  inline void XmlNode::addAttribute(const std::string& name, const std::string& value) {}

  //----< remove attribute does nothing >----------------------------------

  inline bool XmlNode::removeAttribute(const std::string& name, const std::string& value)
  {
    return false;
  }
  //----< return number of attributes, always zero >-----------------------

  inline size_t XmlNode::numAttributes() { return 0; }

  //----< return vector of attributeItems >--------------------------------

  inline std::vector<XmlNode::attributeItem>& XmlNode::getAttributes() 
  { 
    return emptyAttributes; 
  }
  //----< return attributeItem gets default pair >-------------------------

  inline XmlNode::attributeItem XmlNode::attribute(size_t index) 
  { 
    return XmlNode::attributeItem(); 
  }
  //----< make end element string, empty for all except XmlElementNode >---

  inline std::string XmlNode::ToEndString() { return ""; };

  /////////////////////////////////////////////////////////////////////////
  // XmlText Node Type

  class XmlTextNode : public XmlNode
  {
  public:
    XmlTextNode(const std::string& bodyText);
    virtual IXmlNode* clone();
    // Compiler generated copy and assignment are correct for XmlTextNode.
    virtual std::string ToString();
  };
  //----< constructor >----------------------------------------------------

  inline XmlTextNode::XmlTextNode(const std::string& bodyText)  : XmlNode(bodyText)
  { 
    if(value().size()>0 && value()[0] != '"')
      value() = std::string("\"") + value() + "\"";
    type = "XmlTextNode";
  }
  //----< make copy of self >----------------------------------------------

  inline IXmlNode* XmlTextNode::clone() { return new XmlTextNode(*this); }

  /////////////////////////////////////////////////////////////////////////
  // XmlComment Node Type

  class XmlCommentNode : public XmlNode
  {
  public:
    XmlCommentNode(const std::string& commentText);
    virtual IXmlNode* clone();
    // Compiler generated copy and assignment are correct for XmlCommentNode.
    virtual std::string ToString();
  };
  //----< constructor >----------------------------------------------------

  inline XmlCommentNode::XmlCommentNode(const std::string& commentText)  : XmlNode(commentText)
  { 
    type = "XmlCommentNode";
  }
  //----< make copy of self >----------------------------------------------

  inline IXmlNode* XmlCommentNode::clone() { return new XmlCommentNode(*this); }

  /////////////////////////////////////////////////////////////////////////
  // XmlProcessingInstruction Node Type

  class XmlProcInstrNode : public XmlNode
  {
  public:
    XmlProcInstrNode(const std::string& tag);
    virtual IXmlNode* clone();
    // Compiler generated copy and assignment are correct for XmlProcInstrNode.
    virtual void addAttribute(const std::string& name, const std::string& value);
    virtual attributeItem attribute(size_t index);
    virtual size_t numAttributes();
    virtual std::vector<XmlNode::attributeItem>& getAttributes();
    virtual bool removeAttribute(const std::string& name, const std::string& value);
    virtual std::string ToString();
  protected:
    //std::vector< std::pair<std::string, std::string> > attributes;
    std::vector<XmlNode::attributeItem> attributes;
  };
  //----< constructor >----------------------------------------------------

  inline XmlProcInstrNode::XmlProcInstrNode(const std::string& tag)  : XmlNode(tag)
  { 
    type = "XmlProcInstrNode";
  }
  //----< return vector of attributeItems >--------------------------------

  inline std::vector<XmlNode::attributeItem>& XmlProcInstrNode::getAttributes() 
  { 
    return attributes; 
  }
  //----< make copy of self >----------------------------------------------

  inline IXmlNode* XmlProcInstrNode::clone() { return new XmlProcInstrNode(*this); }

  /////////////////////////////////////////////////////////////////////////
  // XmlElement Node Type

  class XmlElementNode : public XmlProcInstrNode
  {
  public:
    XmlElementNode(const std::string& tag);
    XmlElementNode(const XmlElementNode& node);
    ~XmlElementNode();
    virtual IXmlNode* clone();
    XmlElementNode& operator=(const XmlElementNode& node);
    virtual void addChild(IXmlNode* pXmlNode);
    virtual bool removeChild(IXmlNode* pXmlNode);
    virtual size_t numChildren();
    virtual std::vector<IXmlNode*>& getChildren();
    virtual IXmlNode* nextUnmarkedChild();
    virtual void clearMarks();
    virtual std::string ToString();
    virtual std::string ToEndString();
  private:
    std::vector< IXmlNode* > children;
    size_t visitIndex;
  };
  //----< constructor >----------------------------------------------------

  inline XmlElementNode::XmlElementNode(const std::string& val)  : XmlProcInstrNode(val)
  { 
    type = "XmlElementNode";
  }
  //----< return closing tag >---------------------------------------------

  inline std::string XmlElementNode::ToEndString()
  {
    if(children.size() == 0)
      return "";
    std::string temp = "</";
    temp += value();
    temp += ">";
    return temp;
  }
  //----< return vector of child nodes >-----------------------------------

  inline std::vector<IXmlNode*>& XmlElementNode::getChildren() { return children; }
}
#endif
