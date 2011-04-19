#ifndef IXMLDOCUMENT_H
#define IXMLDOCUMENT_H
///////////////////////////////////////////////////////////////////////////
//  IXmlDocument.h - Provides interfaces IXmlDocument, IXmlNode,         //
//  ver 1.0          and factories XmlDocumentFactory and XmlNodeFactory //
//                                                                       //
//  Language:      Visual C++ 2008, SP1                                  //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1              //
//  Application:   Prototype for CSE687 Pr1, Sp09                        //
//  Author:        Jim Fawcett, CST 4-187, Syracuse University           //
//                 (315) 443-3948, jfawcett@twcny.rr.com                 //
///////////////////////////////////////////////////////////////////////////
/*
 * Note:  Interfaces are bases used in XmlDocument.h and XmlNode.h.
 *        The factories are defined in XmlDocumentFactories.cpp
 */
#include <string>
#include <vector>

namespace XmlProcessing
{
  struct IXmlNode
  {
    enum XmlNodeType { Element, ProcInstr, Comment, Text };
    typedef std::pair<std::string,std::string> attributeItem;
    //static IXmlNode* CreateNode(XmlNodeType type);
    virtual ~IXmlNode() {};
    // Compiler generated copy and assignment are correct for XmlNode.
    virtual IXmlNode* clone()=0;
    virtual std::string& value()=0;
    virtual std::string ToString()=0;
    virtual std::string ToEndString()=0;
    // interface for children
    virtual void addChild(IXmlNode* pXmlNode)=0;
    virtual bool removeChild(IXmlNode* pXmlNode)=0;
    virtual size_t numChildren()=0;
    virtual std::vector<IXmlNode*>& getChildren()=0;
    virtual IXmlNode* nextUnmarkedChild()=0;
    virtual void clearMarks()=0;
    // interface for attributes
    virtual void addAttribute(const std::string& name, const std::string& value)=0;
    virtual attributeItem attribute(size_t index)=0;
    virtual std::vector<IXmlNode::attributeItem>& getAttributes()=0;
    virtual bool removeAttribute(const std::string& name, const std::string& value)=0;
    virtual size_t numAttributes()=0;
  };

  struct XmlNodeFactory
  {
    IXmlNode* CreateXmlNode(IXmlNode::XmlNodeType type, const std::string& tag);
  };

  struct IXmlDocument
  {
    enum findType { tag, attribName, attribValue };
    virtual ~IXmlDocument() {}
    virtual void addDocElement()=0;
    virtual void addDocDeclaration()=0;
    virtual bool& verbose()=0;
    virtual void loadFile(const std::string& filename)=0;
    virtual void loadString(const std::string& xmlStr)=0;
    virtual void clear()=0;
    virtual std::vector<IXmlNode*> findElements(const std::string& arg, findType ft)=0;
    virtual IXmlNode* findElement(const std::string& arg, findType ft, IXmlNode* pNode=0)=0;
    virtual IXmlNode* insertElement(IXmlNode* pParent, IXmlNode* pNewChild)=0;
    virtual IXmlNode* deleteElement(IXmlNode* pParent, IXmlNode* pChild)=0;
    virtual std::string ToString(bool format=true)=0;
    virtual bool ToFile(const std::string& fileName)=0;
  };

  struct XmlDocumentFactory
  {
    IXmlDocument* CreateXmlDocument();
  };
}

#endif
