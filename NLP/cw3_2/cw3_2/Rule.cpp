/******** Rule.cpp ************************/
#include <string>
#include <vector>
#include <iostream>
#include "Rule.h"

using namespace std;

/*********************************************/
/* constructor, read the rule                */
/*********************************************/
Rule::Rule(string rule)
{
    string daughter;
    int i, start, len;

    i = rule.find(" --> ");       // i is first after mother
    start = i + 5;                // start is first of daughter
    len = i;                      // length of mother is i
    mother = rule.substr(0, len); // make string from mother

    while ((i = rule.find(",", start)) != string::npos)
    {
        len = i - start; // length of current daughter
        daughter = rule.substr(start, len);
        daughters.push_back(daughter);
        start = i + 1;
    }

    /* push last daughter */
    daughter = rule.substr(start);
    daughters.push_back(daughter);
}

/*********************************************/
/* display the rule                          */
/*********************************************/
void Rule::show()
{
    cout << mother << " --> " << endl;
    for (int i = 0; i < daughters.size(); i++)
    {
        cout << "     " << daughters[i] << endl;
    }
}