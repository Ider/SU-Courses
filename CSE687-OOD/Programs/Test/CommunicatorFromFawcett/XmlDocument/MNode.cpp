///////////////////////////////////////////////////////////////////////////
// MNode.h   -  M-ary node class to use in M-ary tree                    //
// ver 1.0                                                               //
// Language:    Visual C++, 2008                                         //
// Platform:    Dell Precision T7400, Win7 Professional                  //
// Application: CSE687 - Demo for Project #1, Spring 2010                //
// Author:      Jim Fawcett, Syracuse University, CST 4-187,             //
//              (315) 443-3948, jfawcett@twcny.rr.com                    //
///////////////////////////////////////////////////////////////////////////

#ifdef TEST_MNODE

#include "MNode.h"

using namespace TMTree;

typedef MNode<std::string> Node;

void walk(Node* pNode)
{
  pNode->clearMarks();
  std::cout << "\n  " << pNode->value().c_str();
  Node* pTemp;
  while(pTemp = pNode->nextUnmarkedChild())
    walk(pTemp);
  return;
}

void main()
{
  std::cout << "\n  Testing MNode<T> class";
  std::cout << "\n ========================\n";

  Node* pNode1 = new Node("root node");
  Node* pNode2 = new Node("first child of root");
  Node* pNode3 = new Node("second child of root");
  Node* pNode4 = new Node("grandchild of first child of root");
  
  pNode1->addChild(pNode2);
  pNode2->addChild(pNode4);
  pNode1->addChild(pNode3);
  walk(pNode1);
  std::cout << std::endl;

  Node* pNode5 = new Node(*pNode1);
  pNode5->value() = "copy of root node";
  walk(pNode5);
  std::cout << std::endl;

  *pNode5 = *pNode2;
  pNode5->value() = "assignment from first child";
  walk(pNode5);
  std::cout << std::endl;

  std::cout << "\n  removing first child from root";
  pNode1->removeChild(pNode2);
  walk(pNode1);

  std::cout << "\n\n";
}

#endif
