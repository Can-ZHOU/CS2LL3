#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

void fancy_print(vector<string> r);

main(int argc, char *argv[])
{
    // open indicated file
    // get lines making vectors from rules

    char *fname;
    ifstream file;
    fname = argv[1]; // filename is first command line argument

    file.open(fname);

    string line;
    int nrules = 0;
    //vector<string> rule;
    vector<vector<string>> the_rules; //vector of string vectors
    size_t i, start, len;             // len is number of characters in a category
    string category;

    while (getline(file, line))
    {

        vector<string> rule;

        i = line.find(" --> ");         // i is first after mother
        start = i + 5;                  // start is first of daughter
        len = i;                        // length of mother is i
        category = line.substr(0, len); // make string from mother

        rule.push_back(category); // mother of rule gets pushed

        /* push all daughters up to last comma */
        while ((i = line.find(",", start)) != string::npos)
        {
            len = i - start; // length of current daughter
            category = line.substr(start, len);
            rule.push_back(category);
            start = i + 1;
        }

        /* push last dtr */

        category = line.substr(start);
        rule.push_back(category);
        fancy_print(rule);
        nrules++;
        the_rules.push_back(rule); // add rules into the_rules vector
    }
    cout << "number of rules was " << nrules << endl;

    int n;

    do
    {
        cout << "rules with how many dtrs? (enter 0 to quit program)" << endl;
        cin >> n;

        /* find all rules which have required dtrs. */
        for (int i = 0; i < the_rules.size(); i++)
        {
            if (the_rules[i].size() == n + 1)
            {
                fancy_print(the_rules[i]);
            }
        }
    } while (n != 0);
}

void fancy_print(vector<string> r)
{
    cout << r[0];
    cout << " --> " << endl;
    for (unsigned int i = 1; i < r.size(); i++)
    {
        cout << "     " << r[i] << endl;
    }
}
