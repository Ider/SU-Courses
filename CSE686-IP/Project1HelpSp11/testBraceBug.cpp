// testBraceBug.cpp

/* ver 1.3 - braces in quotes and comments caused increment bracecount
 * ver 1.4 - eliminated by adding:
 *           enum state { default_state, comment_state, quote_state }
 *           and incrementing only if in default_state
 */

#include <string>
using namespace std;

void test()
{
  std::string tok;
  char ch = 'a';

  if(tok == "{")
    ;
  if(ch == '{')
    ;
  // {{{
  /* }} */
  // the end
}