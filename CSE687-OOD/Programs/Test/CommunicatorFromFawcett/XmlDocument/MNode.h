#ifndef MNODE_H
#define MNode_H
///////////////////////////////////////////////////////////////////////////
// MNode.h   -  M-ary node class to use in M-ary tree                    //
// ver 1.0                                                               //
// Language:    Visual C++, 2008                                         //
// Platform:    Dell Precision T7400, Win7 Professional                  //
// Application: CSE687 - Demo for Project #1, Spring 2010                //
// Author:      Jim Fawcett, Syracuse University, CST 4-187,             //
//              (315) 443-3948, jfawcett@twcny.rr.com                    //
///////////////////////////////////////////////////////////////////////////
/*
 * Module Operations:
 * ==================
 * Provides a template-based M-ary Node class that holds a finite number
 * of child nodes.  
 * 
 * Required Files:
 * ===============
 * MNode.h, MNode.cpp
 *
 * Build Process:
 * ==============
 * cl /D:TEST_MNODE MNode.cpp
 * 
 * Maintenance History:
 * ====================
 * ver 1.0 : 27 Feb 10
 * - first release
 */


#include <iostream>
#include <vector>

namespace TMTree
{
  /////////////////////////////////////////////////////////////////////////
  // MNode<T> class

  template <typename T>
  class MNode
  {
  public:
    MNode(const T& val);
    MNode(const MNode<T>& node);
    ~MNode();
    MNode<T>* clone();
    MNode<T>& operator=(const MNode<T>& node);
    T& value();
    void addChild(MNode<T>* pNode);
    bool removeChild(MNode<T>* pChild);
    size_t numChildren();
    MNode<T>* nextUnmarkedChild();
    void clearMarks();
    std::string ToString();
  private:
    T val_;
    std::vector<MNode<T>*> children;
    size_t visitIndex;
  };
  //----< return text >----------------------------------------------------

  template <typename T>
  T& MNode<T>::value() { return val_; }

  //----< promotion constructor >------------------------------------------

  template <typename T>
  MNode<T>::MNode(const T& t) : val_(t), visitIndex(0) {}

  //----< destructor >-------------------------------------------------------

  template <typename T>
  MNode<T>::~MNode()
  {
    for(size_t i=0; i<children.size(); ++i)
    {
      delete children[i];
    }
  }
  //----< return copy of self without children >---------------------------

  template <typename T>
  MNode<T>* MNode<T>::clone()
  {
    MNode<T>* pNode = new MNode<T>(value());
    for(size_t i=0; i<children.size(); ++i)
      pNode->addChild(children[i]->clone());
    return pNode;
  }
  //----< copy constructor >-----------------------------------------------

  template <typename T>
  MNode<T>::MNode(const MNode<T>& node) : val_(node.val_)
  {
    for(size_t i=0; i<node.children.size(); ++i)
      children.push_back(node.children[i]->clone());
  }
  //----< assignment operator >----------------------------------------------

  template <typename T>
  MNode<T>& MNode<T>::operator =(const MNode<T>& el)
  {
    if(&el == this) return *this;
    for(size_t i=0; i<children.size(); ++i)
      delete children[i];
    children.clear();
    for(size_t i=0; i<el.children.size(); ++i)
      addChild(el.children[i]->clone());
    return *this;
  }
  //----< add child node >---------------------------------------------------

  template <typename T>
  void MNode<T>::addChild(MNode<T>* pMNode)
  {
    if(pMNode == this)
      throw std::exception("attempting to make node a child of itself!");
    children.push_back(pMNode);
  }
  //----< return number of children >----------------------------------------

  template <typename T>
  size_t MNode<T>::numChildren() { return children.size(); }

  //----< remove child node - returns false on failure, else true >----------

  template <typename T>
  bool MNode<T>::removeChild(MNode<T>* pMNode)
  {
    std::vector< MNode<T>* >::iterator iter = children.begin();
    for(iter=children.begin(); iter!=children.end(); ++iter)
    {
      if(pMNode == *iter)
      {
        delete pMNode;
        children.erase(iter);
        return true;
      }
    }
    return false;
  }
  //----< return pointer to next unvisited child or null >-----------------

  template <typename T>
  MNode<T>* MNode<T>::nextUnmarkedChild()
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

  template <typename T>
  void MNode<T>::clearMarks()
  {
    visitIndex = 0;
  }
  //----< serialize content to string representation of node >-------------

  template <typename T>
  std::string MNode<T>::ToString()
  {
    std::ostringstream temp;
    temp << "<" << value() << ">";
    return temp.str();
  }
}
#endif
