///////////////////////////////////////////////////////////////////////////
// MTree.cpp  -  Holds information extracted from Xml string or file   //
// ver 2.1                                                               //
// Language:    Visual C++, 2008                                         //
// Platform:    Dell Precision T7400, Vista Ultimate, SP1                //
// Application: CSE687 - Demo for Project #1, Spring 2010                //
// Author:      Jim Fawcett, Syracuse University, CST 4-187,             //
//              (315) 443-3948, jfawcett@twcny.rr.com                    //
///////////////////////////////////////////////////////////////////////////

//----< test stub >------------------------------------------------------

#ifdef TEST_MTREE

#include <string>
#include "MTree.h"
#include "MNode.h"

using namespace TMTree;

void main()
{
  std::cout << "\n  MTree class demonstration";
  std::cout << "\n =============================\n";

  typedef MNode<std::string> Node;

  Node* pRoot = new Node("Root");
  Node* pChild1 = new Node("Child1");
  Node* pChild2 = new Node("Child2");
  Node* pGrandchild11 = new Node("Grandchild11");
  Node* pGrandchild21 = new Node("Grandchild21");
  Node* pGrandchild22 = new Node("Grandchild22");
  Node* pGreatgrandchild211 = new Node("Greatgrandchild211");
  Node* pChild3 = new Node("Child3");

  pChild1->addChild(pGrandchild11);
  pGrandchild21->addChild(pGreatgrandchild211);
  pChild2->addChild(pGrandchild21);
  pChild2->addChild(pGrandchild22);
  pRoot->addChild(pChild1);
  pRoot->addChild(pChild2);
  pRoot->addChild(pChild3);

  class newOper : public Operation<Node>
  {
  public:
    bool operator()(Node* pNode)
    {
      std::cout << "\n -- " << pNode->ToString();
      return false;
    }
  };

  MTree<Node> tree(new newOper);
  tree.makeRoot(pRoot);
  tree.verbose() = true;

  tree.walk(pRoot);

  std::cout << std::endl;

  std::string val = "Greatgrandchild211";
  Node* pFound = tree.finder(val);
  if(pFound)
    std::cout << "\n  found \"" << pFound->value() << "\"";
  else
    std::cout << "\n  couldn't find \"" << val << "\"";

  val = "Child1";
  pFound = tree.finder(val);
  if(pFound)
    std::cout << "\n  found \"" << pFound->value() << "\"";
  else
    std::cout << "\n  couldn't find \"" << val << "\"";

  val = "FooBar";
  pFound = tree.finder(val);
  if(pFound)
    std::cout << "\n  found \"" << pFound->value() << "\"";
  else
    std::cout << "\n  couldn't find \"" << val << "\"";

  std::cout << "\n\n  removing first child";
  pRoot->removeChild(pChild1);

  tree.walk();

  std::cout << "\n\n  making copy of tree:";
  MTree<Node> test = tree;
  test.verbose() = true;
  test.walk();
  std::cout << std::endl;

  std::cout << "\n  assigning state of tree:";
  MTree<Node> test2;
  test2 = tree;
  test2.walk();
  std::cout << "\n";
}
#endif

