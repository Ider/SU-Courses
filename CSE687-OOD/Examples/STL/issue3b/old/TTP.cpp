/////////////////////////////////////////////////////////////////
//  TTP.cpp - Issue #3 : template template parameters          //
//                                                             //
//  Jim Fawcett, CSE687 - Object Oriented Design, Spring 2005  //
/////////////////////////////////////////////////////////////////

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
  ~Clone() {};  // non-virtual
private:
  T Prototype_;
};

/////////////////////////////////////////
// CreatedType : type of the created ones

class CreatedType { };

/////////////////////////////////////////
// Creator : the policy-based maker

template <class Created, template <class Created> class CreationPolicy>  // TTP
class Creator : public CreationPolicy<Created>
{
public:
  Created* Make()
  {
    return CreationPolicy<Created>::Make();
  }
  // other members
};

/////////////////////////////////////////
// Note: Now, Creator's first type argument
//       and the policy's argument do not
//       have to be the same.

void main()
{
  CreatedType thePrototype;
  Creator< CreatedType, Clone > cloner;
  cloner.AcceptPrototype(thePrototype);
  CreatedType aCopy = *cloner.Make();
}
