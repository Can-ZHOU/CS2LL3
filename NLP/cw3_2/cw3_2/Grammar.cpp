/******** Grammar.cpp ************************/
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include "Grammar.h"

using namespace std;

/*********************************************/
/* constructor, read all rules in file       */
/*********************************************/
Grammar::Grammar(string filename)
{
    ifstream file;
    file.open(filename);

    string line;
    while (getline(file, line))
    {
        Rule rule(line);
        therules.push_back(rule);
    }
}


/*********************************************/
/* display therules                          */
/*********************************************/
void Grammar::show()
{
    cout << "number of rules was " << therules.size() << endl;

    for (int i = 0; i < therules.size(); i++)
    {
        // fancy print
        cout << therules[i].mother << " --> " << endl;
        for (int j = 0; j < therules[i].daughters.size(); j++)
        {
            cout << "     " << therules[i].daughters[j] << endl;
        }
    }
}