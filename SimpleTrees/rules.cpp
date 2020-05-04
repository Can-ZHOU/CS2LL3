#include "rules.h"
#include <fstream>
#include <algorithm>
#include <iostream>

/*! \param c string describing a category
 *
 * if c = [w] it is taken to be a terminal category and part between 
 * [ ] is the actually category name
 *
 * otherwise whole string is taken as category name
 */
Category::Category(string c) {

  if (c[0] == '[') {
    cat = c.substr(1,c.length() - 2); /* location of ] */
    terminal = true;
  }
  else {
    cat = c;
    terminal = false;
  }

}


Category::Category() {
#if DEBUG 
  cout << "calling void Category constructor\n";
#endif
}

Category::~Category() {
#if DEBUG
  cout << "calling category destructor\n";
#endif
}


void Category::print() {
  if (terminal) {
    cout << '[' + cat + ']';
  }
  else {
    cout << cat << ' ';
  }
}

/*! \param r is string describing a rule
 *
 * r is of form 'm --> d1,...,dn'
 *
 * where m and the di are strings describing categories
 */
Rule::Rule(string r) {
  size_t i, start, len;
  
  i = r.find(" --> ");
  start = i + 5;
  mother = Category(r.substr(0,i));

  /* push all daughters up to last comma */
  while((i = r.find(",",start)) != string::npos) {
    len = i-start;     // length of current daughter 
    dtrs.push_back(Category(r.substr(start,len)));
    start = i + 1;
  }

  /* push last dtr */

  dtrs.push_back(Category(r.substr(start)));


}

Rule::Rule() {
#if DEBUG
  cout << "calling void Rule constructor\n";
#endif
}

Rule::~Rule() {
#if DEBUG
  cout << "calling Rule destructor\n";
#endif
}

void Rule::print() {
  mother.print(); 
  cout << " --> ";
  if(dtrs.size() == 0) { cout << "[]\n"; }
  else {
  for (int i=0; i<dtrs.size()-1; i++) {
    dtrs[i].print();
    cout << ",";
  }
  dtrs.back().print();
  cout << endl;
  }
}


