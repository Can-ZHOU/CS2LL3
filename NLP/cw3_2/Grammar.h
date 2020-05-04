/******** Grammar.h ************************/
#include <string>
#include <vector>
#include "Rule.h"

using namespace std;

class Grammar
{
  public:
    Grammar(string filename);
    vector<Rule> therules;
    void show();
};