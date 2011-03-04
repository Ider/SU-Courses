///////////////////////////////////////////////////////////////////
//  Non_TTP.cpp - Issue #3a : without template template paramter //
//                                                               //
//  Jim Fawcett, CSE687 - Object Oriented Design, Spring 2005    //
///////////////////////////////////////////////////////////////////

#include <iostream>

/////////////////////////////////////////
// Clone : a specific creational policy

template <class T>
class Clone
{
public:
  void AcceptPrototype(T& t)
  {
    std::cout << "\n  Creator accepting prototype instance";
    Prototype_ = t;
  }
  T* Make()
  {
    std::cout << "\n  Creator making clone of prototype";
    return new T(Prototype_); // make copy
  }
protected:
  ~Clone() {}  // non-virtual
private:
  T Prototype_;
};

/////////////////////////////////////////
// Created : type of the created ones

class CreatedType
{
public:
  CreatedType()
  {
    std::cout << "\n  I've been created";
  }
  CreatedType(const CreatedType& ct)
  {
    std::cout << "\n  I've been created as a copy";
  }
};

/////////////////////////////////////////
// Creator : the policy-based maker

template <class Created, class CreationPolicy>
class Creator : public CreationPolicy
{
public:
  Created* Make()
  {
    std::cout << "\n  creating a replicant";
    return CreationPolicy::Make();
  }
  // other members
};
//
void main()
{
  std::cout << "\n  Demonstrating need for Template Template parameters";
  std::cout << "\n =====================================================\n";

  CreatedType thePrototype;

  Creator< CreatedType, Clone<CreatedType> > cloner;  // ugh!
  
  cloner.AcceptPrototype(thePrototype);
  CreatedType aCopy = *cloner.Make();
  std::cout << "\n\n";
}
