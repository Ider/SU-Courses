/////////////////////////////////////////////////////////////////////
//  SemiExpression.cpp - Collects tokens for code analysis         //
//  ver 1.3                                                        //
//                                                                 //
//  Language:      Visual C++ 2008, SP1                            //
//  Platform:      Dell Precision T7400, Vista Ultimate SP1        //
//  Application:   Prototype for CSE687 Pr1, Sp09                  //
//  Author:        Jim Fawcett, CST 4-187, Syracuse University     //
//                 (315) 443-3948, jfawcett@twcny.rr.com           //
////////////////////////////////////////////////////////////////////

#include <algorithm>
#include "SemiExpression.h"

//----< construct SemiExp instance >---------------------------

SemiExp::SemiExp(Toker* pTokr) : pToker(pTokr), Verbose(false),
                                 commentIsSemiExp(false)
{
}
//----< destructor >-------------------------------------------

SemiExp::~SemiExp()
{
}
//----< is this a terminating token? >-------------------------

bool SemiExp::isTerminator(std::string tok)
{
  if(tok.length() == 0)
    return false;
  if(tok == "{" || tok == "}" || tok == ";")
    return true;
  if(tok == "\n")
  {
    int n = find("#");
    if(n < length())
      return true;
  }
  if(commentIsSemiExp && isComment(tok))
    return true;
  return false;
}
//
//----< collect a semi-expression >----------------------------

bool SemiExp::get()
{
  toks.clear();
  std::string tok;
  do
  {
    if(pToker->isFileEnd())
    {
      if(length() > 0)
        return true;
      return false;
    }
    tok = pToker->getTok();
    if(Verbose)
    {
      if(tok != "\n")
        std::cout << "\n--tok=" << tok << std::endl;
      else
        std::cout << "\n--tok=newline\n";
    }
    toks.push_back(tok);
  } while(!isTerminator(tok));
  return true;
}
//----< is this token a comment? >-----------------------------

bool SemiExp::isComment(const std::string& tok)
{
  if(tok.length() < 2) return false;
  if(tok[0] != '/') return false;
  if(tok[1] == '/' || tok[1] == '*') return true;
  return false;
}
//----< index operator >---------------------------------------

std::string& SemiExp::operator[](int n)
{
  if(n < 0 || toks.size() <= (size_t)n)
    throw std::exception("SemiExp index out of range");
  return toks[n];
}
//----< collect semi-expression as space-seperated string >----

std::string SemiExp::show()
{
  if(toks.size() == 0)
    return "";
  std::string temp(" ");
  for(size_t i=0; i<toks.size(); ++i)
    if(toks[i] != "\n")
      temp.append(" ").append(toks[i]);
  return temp;
}
//
//----< is tok found in semi-expression? >---------------------

int SemiExp::find(const std::string& tok)
{
  for(int i=0; i<length(); ++i)
    if(tok == toks[i])
      return i;
  return length();
}
//----< remove tok if found in semi-expression >---------------

bool SemiExp::remove(const std::string& tok)
{
  std::vector<std::string>::iterator it;
  it = std::find(toks.begin(),toks.end(),tok);
  if(it != toks.end())
  {
    toks.erase(it);
    return true;
  }
  return false;
}
//----< remove leading newlines >------------------------------

void SemiExp::trimFront()
{
  while(toks.size() > 0 && toks[0] == "\n")
    remove("\n");
}
//----< make tokens lowercase >--------------------------------

void SemiExp::toLower()
{
  for(int i=0; i<length(); ++i)
  {
    for(size_t j=0; j<(*this)[i].length(); ++j)
    {
      (*this)[i][j] = tolower((*this)[i][j]);
    }
  }
}

//----< test stub >--------------------------------------------

#ifdef TEST_SEMIEXPRESSION

int main(int argc, char* argv[])
{
  std::cout << "\n  Testing SemiExp class\n "
            << std::string(23,'=') << std::endl;
  
  std::cout << "\n  testing SemiExp::find()";
  std::cout << "\n -------------------------";
  SemiExp semi(0);
  semi.push_back("one");
  semi.push_back("two");
  semi.push_back("three");
  semi.push_back("four");
  std::cout << "\n" << semi.show();
  size_t pos = semi.find("two");
  std::cout << "\n  position of \"two\" is " << pos;
  pos = semi.find("foobar");
  std::cout << "\n  position of \"foobar\" is " << pos;
  std::cout << "\n\n";

  std::cout << "\n  Note that comments and quotes are returned as single tokens\n";

  if(argc < 2)
  {
    std::cout 
      << "\n  please enter name of file to process on command line\n\n";
    return 1;
  }

  for(int i=1; i<argc; ++i)
  {
    std::cout << "\n  Processing file " << argv[i];
    std::cout << "\n  " << std::string(16 + strlen(argv[i]),'-') << "\n\n";
    try
    {
  	  Toker toker(argv[i]);
      toker.returnComments();
      SemiExp se(&toker);
      se.makeCommentSemiExp();
//    se.verbose();                 // uncomment to show token details
      while(se.get())
        std::cout << se.show().c_str() << std::endl;
      std::cout << "\n";
    }
    catch(std::exception ex)
    {
      std::cout << "\n  " << ex.what() << "\n\n";
    }
  }
}

#endif
