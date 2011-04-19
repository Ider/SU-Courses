///////////////////////////////////////////////////////////////////////////
// Nodes.cpp - demonstrate how to define a template node class           //
// ver 3.1                                                               //
// Language:    Visual C++, 2008                                         //
// Platform:    Dell Precision T7400, Vista Ultimate, SP1                //
// Application: CSE382 - Algorithms and Data Structures Demo, Fall 2008  //
// Author:      Jim Fawcett, Syracuse University, CST 4-187,             //
//              (315) 443-3948, jfawcett@twcny.rr.com                    //
///////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <stack>
#include <cctype>
#include "XmlNodes.h"

using namespace XmlProcessing;

//----< declare static instance in XmlNode >-------------------------------

bool XmlNode::verbose_ = false;
bool XmlNode::onStack_ = false;
std::vector<IXmlNode*> XmlNode::emptyChildren;
std::vector<IXmlNode::attributeItem> XmlNode::emptyAttributes;

//----< return default string representation of template type >------------

std::string XmlNode::ToString()
{
  std::ostringstream temp;
  temp << "<" << tag << ">";
  return temp.str();
}
//----< serialize node contents to string representation >-----------------

std::string XmlTextNode::ToString()
{
  std::string temp = value().substr(1,value().size()-2);  // remove enQuotes
  return temp;
}
//----< serialize node contents to string representation >-----------------

std::string XmlCommentNode::ToString()
{
  std::ostringstream temp;
  temp << "<!-- " << value() << " -->";
  return temp.str();
}
//----< copy constructor >-------------------------------------------------

XmlElementNode::XmlElementNode(const XmlElementNode& node) : XmlProcInstrNode(node)
{
  for(size_t i=0; i<node.children.size(); ++i)
    children.push_back(node.children[i]->clone());
}
//----< destructor >-------------------------------------------------------

XmlElementNode::~XmlElementNode()
{
  for(size_t i=0; i<children.size(); ++i)
  {
    if(!onStack())
      delete children[i];
  }
}
//----< return copy of self without children >---------------------------

IXmlNode* XmlElementNode::clone()
{
  XmlElementNode* pNode = new XmlElementNode(value());
  pNode->attributes = attributes;
  for(size_t i=0; i<children.size(); ++i)
    pNode->addChild(children[i]->clone());
  return pNode;
}
//----< assignment operator >----------------------------------------------

XmlElementNode& XmlElementNode::operator =(const XmlElementNode& el)
{
  if(&el == this) return *this;
  attributes = el.attributes;
  for(size_t i=0; i<children.size(); ++i)
    if(!onStack()) delete children[i];
  children.clear();
  for(size_t i=0; i<el.children.size(); ++i)
    addChild(el.children[i]->clone());
  return *this;
}
//----< add child node >---------------------------------------------------

void XmlElementNode::addChild(IXmlNode* pXmlNode)
{
  if(pXmlNode == this)
    throw std::exception("attempting to make node a child of itself!");
  children.push_back(pXmlNode);
}
//----< return number of children >----------------------------------------

size_t XmlElementNode::numChildren() { return children.size(); }

//----< remove child node - returns false on failure, else true >----------

bool XmlElementNode::removeChild(IXmlNode* pXmlNode)
{
  std::vector<IXmlNode*>::iterator iter = children.begin();
  for(iter=children.begin(); iter!=children.end(); ++iter)
  {
    if(pXmlNode == *iter)
    {
      if(!onStack()) delete pXmlNode;
      children.erase(iter);
      return true;
    }
  }
  return false;
}
//----< return pointer to next unvisited child or null >-----------------

IXmlNode* XmlElementNode::nextUnmarkedChild()
{
  if(children.size() == 0)
    return 0;
  if(visitIndex < children.size())
  {
    return children[visitIndex++];
  }
  return 0;
}
//----< "mark" all children as unvisited >-------------------------------

void XmlElementNode::clearMarks()
{
  visitIndex = 0;
}
//----< serialize content to string representation of node >---------------

std::string XmlElementNode::ToString()
{
  std::ostringstream temp;
  temp << "<" << value();
  for(size_t i=0; i<attributes.size(); ++i)
  {
    temp << " " << attributes[i].first.c_str() << "=";
    if(attributes[i].second[0] == '"')
      temp << attributes[i].second.c_str();
    else
      temp << "\"" << attributes[i].second.c_str() << "\"";
  }
  if(children.size() > 0)
    temp << ">";
  else
    temp << "/>";
  return temp.str();
}
//----< add name : value pair to attribute collection >--------------------

void XmlProcInstrNode::addAttribute(const std::string& name, const std::string& value)
{
  std::pair<std::string, std::string> attr;
  
  // Note: invalid name may be caused by values that are not quoted.
  // That causes tokenizer to possibly parition into parts, as in 1.0.
  // Parsing then thinks these are addition attributes but the names
  // are blank.

  if(name.size() == 0 || !isalpha(name[0]))
    throw std::exception("invalid attribute");
  attr.first = name;
  if(value[0] == '"' || value[0] == '\'')
    attr.second = value.substr(1,value.size()-2);
  else
    attr.second = value;
  attributes.push_back(attr);
}
//----< remove attribute >-------------------------------------------------

bool XmlProcInstrNode::removeAttribute(const std::string& name, const std::string& value)
{
  std::vector<XmlNode::attributeItem>::iterator iter;
  for(iter=attributes.begin(); iter!=attributes.end(); ++iter)
  {
    if(iter->first == name && iter->second == value)
    {
      attributes.erase(iter);
      return true;
    }
  }
  return false;
}
//----< return attributeItem >---------------------------------------------

XmlNode::attributeItem XmlProcInstrNode::attribute(size_t index)
{
  if(0<= index && index < attributes.size())
    return attributes[index];
  else
    throw std::exception("attribute index out of bounds");
}
//----< return number of attributes >--------------------------------------

size_t XmlProcInstrNode::numAttributes() { return attributes.size(); }

//----< serialize node contents to string representation >-----------------

std::string XmlProcInstrNode::ToString()
{
  std::ostringstream temp;
  temp << "<?" << value();
  for(size_t i=0; i<attributes.size(); ++i)
  {
    temp << " " << attributes[i].first.c_str() << "=";
    if(attributes[i].second[0] == '"')
      temp << attributes[i].second.c_str();
    else
      temp << "\"" << attributes[i].second.c_str() << "\"";
  }
  temp << "?>";
  return temp.str();
}

#ifdef TEST_XMLNODES

//----< this test function is how tree does depth first search >-----------

void WalkTree(XmlNode* pXmlNode)
{
  std::cout << "\n  " << pXmlNode->ToString();
  pXmlNode->clearMarks();
  XmlNode* pTemp;
  while(pTemp = pXmlNode->nextUnmarkedChild())
  {
    WalkTree(pTemp);
  }
  std::string end = pXmlNode->ToEndString();
  if(end.size() > 0)
    std::cout << "\n  " << end;
}
//----< test stub demonstration >------------------------------------------

void main()
{
  std::cout << "\n  XmlNode class demonstration";
  std::cout << "\n ==============================\n";

  std::cout << "\n  This demo uses a stack to order and link nodes, as they are created in";
  std::cout << "\n  depth-first order.  This builds a tree structure of nodes which is the";
  std::cout << "\n  product popped off the stack at the end.\n";

  std::cout << "\n  Note that this is exactly what happens when you assemble parts from";
  std::cout << "\n  XmlElementParts to build the internal tree for an XmlDocument instance.\n";
  
  std::cout << "\n  As the last step in parsing, you pull a fully formed parse tree (in linked";
  std::cout << "\n  nodes form) from the top of the stack on its final pop.  Now you just bind";
  std::cout << "\n  the top node to your tree root for subsequent processing.\n";

  XmlNode::verbose() = true;
  XmlNode::onStack() = true;

  std::stack<XmlNode*> NodeStack;

  XmlElementNode docElement("docElement");
  NodeStack.push(&docElement);

  XmlProcInstrNode pnode("xml");
  pnode.addAttribute("version","1.0");
  NodeStack.top()->addChild(&pnode);

  XmlCommentNode cnode("This is some not very illuminating comment.");
  NodeStack.top()->addChild(&cnode);

  XmlElementNode root("root");
  root.addAttribute("attName","attValue");
  NodeStack.top()->addChild(&root);
  NodeStack.push(&root);                                          // &root on stack top
  
  XmlElementNode child1("child1");
  XmlTextNode tnode("text of child1");
  child1.addChild(&tnode);
  NodeStack.top()->addChild(&child1);                             // child1 added to root
  NodeStack.push(&child1);                                        // &child1 pushed to stack top

  XmlElementNode grandchild11("grandchild11");
  NodeStack.top()->addChild(&grandchild11);                       // grandchild11 added to child1
  NodeStack.pop();                                                // stack popped to reveal &root

  XmlElementNode child2("child2");
  NodeStack.top()->addChild(&child2);                             // child2 added to root
  NodeStack.push(&child2);                                        // &child2 pushed to stack top

  XmlElementNode grandchild21("grandchild21");
  NodeStack.top()->addChild(&grandchild21);                       // grandchild21 added to child2
  NodeStack.push(&grandchild21);                                  // &grandchild21 pushed to stack top

  XmlElementNode greatgrandchild211("greatgrandchild211");
  NodeStack.top()->addChild(&greatgrandchild211);                 // greadgrandchild211 added to grandchild21
  NodeStack.pop();                                                // stack popped to reveal &child2

  XmlElementNode grandchild22("grandchild22");
  NodeStack.top()->addChild(&grandchild22);                       // grandchild22 added to child2
  NodeStack.pop();                                                // stack popped to reveal &root

  XmlElementNode child3("child3");
  NodeStack.top()->addChild(&child3);                             // child3 added to root
  
  XmlNode* pRoot = NodeStack.top();                               // &root popped from stack
  NodeStack.pop();

  XmlNode* pDocElement = NodeStack.top();
  WalkTree(pDocElement);

  std::cout << "\n\n  removing first child";
  root.removeChild(&child1);

  WalkTree(pDocElement);

  std::cout << "\n";
  std::cout << "\n  root.ToString() = " << root.ToString().c_str();
  std::cout << "\n  root.Type() = " << root.Type().c_str();
  std::cout << "\n";

  std::cout << "\n  pnode.ToString() = " << pnode.ToString().c_str();
  std::cout << "\n  pnode.Type() = " << pnode.Type().c_str();
  std::cout << "\n";

  std::cout << "\n  cnode.ToString() = " << cnode.ToString().c_str();
  std::cout << "\n  cnode.Type() = " << cnode.Type().c_str();
  std::cout << "\n";

  std::cout << "\n  tnode.ToString() = " << tnode.ToString().c_str();
  std::cout << "\n  tnode.Type() = " << tnode.Type().c_str();
  std::cout << "\n\n";

  std::cout << "\n  making copy of child3:";
  XmlElementNode test1 = child3;
  WalkTree(&test1);
  std::cout << std::endl;

  std::cout << "\n  making copy of child1:";
  XmlElementNode test2 = child1;
  WalkTree(&test2);
  std::cout << std::endl;

  std::cout << "\n  assigning value of root:";
  XmlElementNode node("newRoot");
  node = root;
  WalkTree(&root);
  std::cout << "\n\n";
}
#endif
