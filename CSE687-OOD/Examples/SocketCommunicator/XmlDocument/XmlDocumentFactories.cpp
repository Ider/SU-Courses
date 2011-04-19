///////////////////////////////////////////////////////////////////////////
//  XmlDocumentFactories.cpp -                                           //
//  ver 1.0     Provides factories XmlDocumentFactory and XmlNodeFactory //
//                                                                       //
//  Language:      Visual C++ 2008, SP1                                  //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1              //
//  Application:   Prototype for CSE687 Pr1, Sp09                        //
//  Author:        Jim Fawcett, CST 4-187, Syracuse University           //
//                 (315) 443-3948, jfawcett@twcny.rr.com                 //
///////////////////////////////////////////////////////////////////////////

#include "XmlNodes.h"
#include "XmlDocument.h"

using namespace XmlProcessing;

IXmlNode* XmlNodeFactory::CreateXmlNode(IXmlNode::XmlNodeType type, const std::string& tag)
{
  if(type == IXmlNode::Element)
    return new XmlElementNode(tag);
  if(type == IXmlNode::ProcInstr)
    return new XmlProcInstrNode(tag);
  if(type == IXmlNode::Text)
    return new XmlTextNode(tag);
  if(type == IXmlNode::Comment)
    return new XmlCommentNode(tag);
  return 0;
}

IXmlDocument* XmlDocumentFactory::CreateXmlDocument()
{
  IXmlDocument* pDoc = new XmlDocument();
  pDoc->addDocElement();
  return pDoc;
}
