#include "BUPARSE.h"
#include <iostream>


BUPARSE::BUPARSE(string grammar){
  /* make a grammar */
  g = Grammar(grammar);
  /* set progress to 0 */
  progress = 0;
  stack_debug = 0;
pda.print_top_at_left = false;
}

BUPARSE::BUPARSE(){
pda.print_top_at_left = false;
}

/*! displays remaining words and current stack unless stack_debug is 0
 */ 
void BUPARSE::display_config() {
  if(stack_debug == 1) {
    cout << "STACK: ";
    pda.print();
    cout << "WORDS: ";
    for(unsigned int i = progress; i < input.size(); i++) {
      cout << input[i] + " ";
    }
    cout << endl;
  }
}

/*! set up for a fresh call to accept so the stack is emptied
 */
void BUPARSE::initialize() {
  /* empty the stack */
  while(pda.is_empty() != true) {
    pda.pop();
  }
  progress = 0;
  rulecount = 0;
}

/*! returns true if key can be parsed
 */
bool BUPARSE::accept(vector<string> key) {

  initialize();
  input = key;
  display_config();

  Rule r; // will be used in the reduce case
  Category c; // will be used in the shift case
  int move_type = 0; // classifies whether and what kind of a move can
                    // be made

  while ((move_type = move()) != 0) {
      if(move_type == 1) {
          r = g.rules[rulecount];
          /* INCOMPLETE */
	  /* pop the dtrs of r off the stack and push the mother */
	  
	  rulecount = 0;
	  display_config();
	}
      else if (move_type == 2) {
        /* INCOMPLETE */
	/* make a terminal category out of current word */
        /* push this on the stack */
	/* increment progress */

	  display_config();
      }
      else {
	cout << "should never reach this \n";
      }
    }

    return final_config();

}


/*! returns 0 if no move can be made
 * 
 * returns 1 if a reduction can be made
 *
 * returns 2 if a shift can be made
 *
 * rules searched linearly for possibility to reduce starting at
 * 0
 *
 * if a reduction can be made, rule choice recorded in rulecount
 */
int BUPARSE::move() {
  Rule r;
  /* INCOMPLETE */ 
  // CHECK FOR REDUCTION
  // with a loop thru all the rules 
  //   for each rule use top_match method of PDA to see if 
  //   dtrs D1,...,Dn are top most DN ... D1 of stack
  //   and if so set rulecount to indicate which rule 
  //   and return 1

  // if there is no reduction
  // CHECK FOR SHIFT
  // by seeing if there are still words which could be shifted
  // and if so return 2

  // else return 0



  return 0;

}

/*! checks if reached an accepting configuration which is one where all input
 *  has been processed and stack just contains the initial category
 */
bool BUPARSE::final_config() {
  Category c;
  if (pda.is_empty()) {
    return false;
  }
  else if (progress < input.size()) {
    return false;
  }
  else {
    c = pda.top();
    if (are_equal(c,g.initial) && pda.size() == 1) {
      return true;
    }
    else {
      return false;
    }
  }
}


