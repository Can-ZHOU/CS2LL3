#include "TDPARSE_BT_TREE.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>

BT_TREE_ITEM::BT_TREE_ITEM() {
  rulecount = 0;
  progress = 0;
  preorder_size = 0;  
}

BT_TREE_ITEM::~BT_TREE_ITEM() {

}

TDPARSE_BT_TREE::TDPARSE_BT_TREE(string grammar): TDPARSE(grammar) {
  backtrack_debug = 1;
  use_dot = 0;
}

TDPARSE_BT_TREE::TDPARSE_BT_TREE(){
  backtrack_debug = 0;
  use_dot = 0;
}

void TDPARSE_BT_TREE::initialize_bt(){
  history.clear();
}

void TDPARSE_BT_TREE::initialize_preorder(){
  preorder.clear();
}

// void TDPARSE_BT_TREE::display_config_bt(){
//   for(int i = history.size()-1; i < history.size(); i++) {
//     cout << "history item " << i << "***********************************\n";
//     history[i].pda.print();
//     cout << "input was \n";
//       for(int j = history[i].progress; j < input.size(); j++) {
// 	cout << input[j] << ' ';
//       }
//       cout << endl;
 
//       cout << "used rule ";
//       g.rules[history[i].rulecount].print();
//   }

// }

void TDPARSE_BT_TREE::display_config_bt(){
  unsigned int i;
  if(backtrack_debug == 1) {
    i = history.size()-1;
    cout << "BACKTRACKING to use of rule: ";
    g.rules[history[i].rulecount].print();

    cout << i << " WORDS: ";
    for(unsigned int j = history[i].progress; j < input.size(); j++) {
      cout << input[j] << ' ';
    }
    cout << "STACK: "; 
    history[i].pda.print();
    //cout << "number of rules stored was " << history[i].preorder_size << endl;
  }

}

void TDPARSE_BT_TREE::display_preorder() {
  //cout << "preorder size is :" << preorder.size() << endl;
  //cout << "preorder capacity is :" << preorder.capacity() << endl;
  for (unsigned int m = 0; m < preorder.size(); m++) {
   preorder[m].print();
  }

}



/* if do_all == 1 does all analyses */
/* otherwise does one analysis                  */
int TDPARSE_BT_TREE::parse_all(vector<string> key, bool do_all) {
  input = key;
  initialize();
  initialize_bt();
  initialize_preorder();
  int how_many = 0;
  bool more_solutions = false;
  do {
    if(parse_one() == true) {
      how_many++;
      Tree *t;
      t = build_tree();
      t->drawtree();
      if(use_dot == 1) {
        t->dot_tree();
      }
      delete t;
    

      if (do_all == false) {
	break;
      }

      if(history.size() > 0) {
	display_config_bt();
	rulecount = history[history.size()-1].rulecount + 1;
	pda = history[history.size()-1].pda;
	progress = history[history.size()-1].progress;
	preorder.resize(history[history.size()-1].preorder_size);
	history.pop_back();
	more_solutions = true;
      }
      else {
	more_solutions = false;
      }
    } 
    else { 
      break;
    }
  }
  while (more_solutions == true);


  return how_many;
}

bool TDPARSE_BT_TREE::parse_one() {

  bool accept;
  int type = 0;
  int backtracking = 0;
  Rule r;
  Rule pre_part;
  display_config();

  do {
    while(move(type)) {
      if(type == 1) {
        progress++;
        pre_part.mother = pda.top();
        pre_part.dtrs.clear();       
	preorder.push_back(pre_part);
 
        pda.pop();
        display_config();

        rulecount = 0;
      }
      else if(type == 2) {  
        r = g.rules[rulecount];         // r is 'm --> [w]'

	extend_history(rulecount);

        // add 'm --> [w]' to preroder
	preorder.push_back(r);
        // add '[w] --> []' to preorder
        pre_part.mother = r.dtrs[0];
        pre_part.dtrs.clear();
	preorder.push_back(pre_part);

	progress++;
	pda.pop();
	display_config();

	rulecount = 0;

      }
      else if(type == 3) {
	extend_history(rulecount);
        r = g.rules[rulecount];     // r is 'm --> d1,...,dN
	preorder.push_back(r);
	pda.pop(); /* pop mother */
	for (int j = r.dtrs.size(); j > 0; j--) {
	  pda.push(r.dtrs[j-1]);
	} /* push dtrs, starting with rightmost */
	display_config();

        rulecount = 0;
      }
      else {
	cout << "should never get here\n";
      }
    } // end of moves loop

    // now accept, backtrack or fail
    if (final_config() == true) {
      accept = true;
      break;
    }
    else if (history.size() > 0) {
      rulecount = history[history.size()-1].rulecount + 1;
      display_config_bt();
      pda = history[history.size()-1].pda;
      progress = history[history.size()-1].progress;
      preorder.resize(history[history.size()-1].preorder_size);
      history.pop_back();
      backtracking = 1;
    }
    else {
      backtracking = 0;
      accept = false;
    }
  }
  while(backtracking == 1);

  return accept;
}

bool TDPARSE_BT_TREE::move(int& type) {
  Rule r;
  unsigned int j;

  if (pda.is_empty() == 1 || progress == input.size()) {
    return false;
  }

  /* CHECK IF TOP OF STACK = CURRENT WORD */
  if ((pda.top().terminal) && (pda.top().cat == input[progress])) {
    type = 1; /* word match */
    return true;
  }

  for(j = rulecount; j < g.nrules; j++) {
    r = g.rules[j];
    if (are_equal(pda.top(),r.mother)) {
      /* TRY LEAF CANCELLATION */
      if (r.dtrs.size() == 1 && r.dtrs[0].terminal) {
	if (r.dtrs[0].cat == input[progress]) { 
	  rulecount = j;
	  type = 2; /* terminal production */
	  return true;
	}
	else {
	  continue;
	}
      }
      else { /* DO LEFT EXPANSION */
	rulecount = j;
	type = 3; /* left expansions */
	return true;
      }
    }
  }

    return false;



}

void TDPARSE_BT_TREE::extend_history(unsigned int i) {


  Rule used, other;
  int later = 0;
  /* check if there are later choices */
  used = g.rules[i];
  for (unsigned int j = i+1; j < g.nrules; j++) {
    other = g.rules[j];
    /* if other rule has same mother as rule used */
    if (other.mother.cat == used.mother.cat) {
      /* if other and used rule are terminal, ignore */
      if ((used.dtrs.size() == 1) && (used.dtrs[0].terminal)
	  && (other.dtrs.size() == 1) && (other.dtrs[0].terminal)) {}
      else {
	later = 1;
	break;
      }
    }
  }
  
  if(later == 1) {
    BT_TREE_ITEM b;
    b.pda = pda;
    b.progress = progress;
    /* record rule number about to be used */
    b.rulecount = i;
    b.preorder_size = preorder.size();
    history.push_back(b);
  }
}

/* each member of preorder corresponds to pop from the stack      */
/* for non-terminals should be followed by pushes of the dtrs     */
/* so interpreting the preorder    this way, push and pop from a  */
/* stack of trees starting with a tree for the initial category   */
/* you could do this in the parse method itself and work all      */
/* the time with a stack of trees, but under backtracking         */
/* would have to ensure that trees allocated down a blind alley   */
/* doing the tree allocation once the parse is completed is       */
/* to program                                                     */

Tree *TDPARSE_BT_TREE::build_tree() {

  vector<Tree *> trees;
  Tree *t_ptr, *t_ptr1, *whole_tree_ptr;

  Rule r; // use to track thru preorder
          // note for parts of preorder corresponding to words
          // the 'Rule' will be somewhat fake: [w] --> []

  whole_tree_ptr = new Tree(g.initial);
  trees.push_back(whole_tree_ptr);
  for (unsigned int i=0; i < preorder.size(); i++) {
    r = preorder[i];
    t_ptr = trees.back();
    trees.pop_back();
    if(r.dtrs.size()==0) { }
    else {
      t_ptr->dtrs.resize(r.dtrs.size());

      for (unsigned int j = 0; j < r.dtrs.size(); j++) {
	t_ptr1 = new Tree(r.dtrs[j]);
	t_ptr->dtrs[j] = t_ptr1;
      }
      for (int k = r.dtrs.size()-1; k >= 0; k--) {
      
	trees.push_back(t_ptr->dtrs[k]);

      }
    }
  }
  return whole_tree_ptr;
}








