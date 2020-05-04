/******** Rule.h ************************/
#include <string>
#include <vector>
using namespace std;

class Rule
{
  public:
    string mother;
    vector<string> daughters;
    Rule(string rule);
    void show();
};