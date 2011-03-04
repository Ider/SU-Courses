/////////////////////////////////////////////////////////////////
//  TTP.cpp - Issue #3b : template template parameters         //
//                                                             //
//  Jim Fawcett, CSE687 - Object Oriented Design, Spring 2005  //
/////////////////////////////////////////////////////////////////

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
    return new T(Prototype_);
  }
protected:
  ~Clone() {};  // non-virtual
private:
  T Prototype_;
};

/////////////////////////////////////////
// CreatedType : type of the created ones

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

template <class Created, template <class Created> class CreationPolicy>  // TTP
class Creator : public CreationPolicy<Created>
{
public:
  Created* Make()
  {
    std::cout << "\n  creating a replicant";
    return CreationPolicy<Created>::Make();
  }
  // other members
};
//
/////////////////////////////////////////
// Note: Now, Creator's first type argument
//       and the policy's argument do not
//       have to be the same.

void main()
{
  std::cout << "\n  Demonstrating Template Template parameters";
  std::cout << "\n ============================================\n";

  CreatedType thePrototype;

  Creator< CreatedType, Clone > cloner;  // aaahhh!
  
  cloner.AcceptPrototype(thePrototype);
  CreatedType aCopy = *cloner.Make();
  std::cout << "\n\n";
}
