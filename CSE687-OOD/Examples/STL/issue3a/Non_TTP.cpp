///////////////////////////////////////////////////////////////////
//  Non_TTP.cpp - Issue #3a : without template template paramter //
//                                                               //
//  Jim Fawcett, CSE687 - Object Oriented Design, Spring 2005    //
///////////////////////////////////////////////////////////////////

/////////////////////////////////////////
// Clone : a specific creational policy

template <class T>
class Clone
{
public:
  void AcceptPrototype(T& t)
  {
    Prototype_ = t;
  }
  T* Make()
  {
    return new T(Prototype_); // make copy
  }
protected:
  ~Clone() {}  // non-virtual
private:
  T Prototype_;
};

/////////////////////////////////////////
// Created : type of the created ones

class CreatedType { };

/////////////////////////////////////////
// Creator : the policy-based maker

template <class Created, class CreationPolicy>
class Creator : public CreationPolicy
{
public:
  Created* Make()
  {
    return CreationPolicy::Make();
  }
  // other members
};


void main()
{
  CreatedType thePrototype;
  Creator< CreatedType, Clone<CreatedType> > cloner;  // ugh!
  cloner.AcceptPrototype(thePrototype);
  CreatedType aCopy = *cloner.Make();
}
