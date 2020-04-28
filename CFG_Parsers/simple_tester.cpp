#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>


#include "TDPARSE_BT_TREE.h"
//#include "BUPARSE_BT_TREE.h"
//#include "CHART_WITH_TREES.h"

using namespace std;

vector<string> words;

void tokenize(string line) {
  /* empty the words vector */
  for(int i = words.size(); i > 0; i--) {
    words.pop_back();
  }

  /* update the words vector from line */
  string::iterator word_itr, space_itr;

  word_itr = line.begin();             /* word_itr is beginning of line */
  space_itr = find(word_itr,line.end(),' '); /* find space */
 
  while(space_itr != line.end()) {
    words.push_back(string(word_itr,space_itr));

    word_itr = space_itr+1;
    space_itr = find(word_itr,line.end(),' '); /* find space */

  }

  words.push_back(string(word_itr,space_itr)); 

}


int main(int argc, char *argv[]) {

  string gname,s;
  if(argc != 2) {
    cout << "usage: simple_tester GRAMMAR\n";
    cout << "where GRAMMAR is the filename of a grammar\n";
  exit(0);
  }

  gname = string(argv[1]);


  TDPARSE_BT_TREE parser(gname);
  // BUPARSE_BT_TREE parser(gname);
  //  CHART_WITH_TREES parser(gname);
  // NOTE: adjust above declaration for various other tree-enabled parser classes
  // also adjust corresponding 'include' at top
 
  parser.g.print();

   while(cout << "enter the string to be checked "
 	&& getline(cin,s)) {
     tokenize(s); 
     cout << "input is " << s << endl;
     cout << parser.parse_all(words,true) << endl;
     //cout << parser.parse_all(words,true) << endl;
   }
  return 0;

}




