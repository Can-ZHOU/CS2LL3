#include "TDPARSE.h"
#include <iostream>

TDPARSE::TDPARSE(string grammar){
  /* make a grammar */
  g = Grammar(grammar);
  /* set progress to 0 */
  progress = 0;
  stack_debug = 1;
}

TDPARSE::TDPARSE(){}

/*! displays remaining words and current stack unless stack_debug is 0
 */
void TDPARSE::display_config() {
  if(stack_debug == 1) {
    cout << "WORDS: ";
    for(unsigned int i = progress; i < input.size(); i++) {
      cout << input[i] + " ";
    }
    cout << " STACK: ";
    pda.print();
  }
}

/*! resets pda and progress to initial values for a fresh top-down parse 
 *  so pda set to contain just initial category
 */
void TDPARSE::initialize() {
  /* empty the stack */
  while(pda.is_empty() != 1) {
    pda.pop();
  }
  /* push initial category */
  pda.push(g.initial);

  progress = 0;
  rulecount = 0;
}

/*! returns true if key can be parsed
 */
bool TDPARSE::accept(vector<string> key) {

  initialize();
  input = key;
  display_config();

  Rule r; // will be used in the left expansion case
  int move_type = 0; // classifies whether and what kind of a move can
                     // be made

  while((move_type = move()) != 0) {
      if(move_type == 1 || move_type == 2) {
        progress++;
        pda.pop();
        display_config();
      }
      else if(move_type == 3) {
	  pda.pop(); /* pop top of stack */
          r = g.rules[rulecount];
	  for (int j = r.dtrs.size(); j > 0; j--) {
	    pda.push(r.dtrs[j-1]);
	  } /* push dtrs, starting with rightmost */
          display_config();
      }
  }

  return final_config();

}


/*! returns 0 if no move can be made
 *
 * returns  1 if top of stack = current word
 *
 * returns  2 leaf cancellation using a rule C --> [w]
 *
 * returns  3 left expansion 
 *
 * rules searched linearly looking for leaf cancel or left expansion with 
 * search always from 0
 *
 * when left expansion is applied, rulecount records which rule  
 */
int TDPARSE::move() {
  Rule r;

  if (pda.is_empty() || progress == input.size()) {
    return 0;
  }

  /* CHECK IF TOP OF STACK = CURRENT WORD */
  if ((pda.top().terminal) && (pda.top().cat == input[progress])) {
    /* word match */
    return 1;
  }

  for(unsigned int j = 0; j < g.nrules; j++) {
    r = g.rules[j];
    if (are_equal(pda.top(),r.mother)) {
      /* TRY LEAF CANCELLATION */
      if (r.dtrs.size() == 1 && r.dtrs[0].terminal) {
	if (r.dtrs[0].cat == input[progress]) { 
	  return 2; /* terminal production */
	}
	else {
	  continue;
	}
      }
      else { /* DO LEFT EXPANSION */
	rulecount = j;
	return 3; /* left expansions */
      }
    }
  }
  // reach here if none of the rules permit a leaf-cancel
  // or left expansion
    return 0;

}

/*! tests if parser reached state which indicates acceptance
 *  so all input used up and stack reduced to empty 
 */
bool TDPARSE::final_config() {
  if (progress == input.size() && pda.is_empty()) {
    return true;
  }
  else {
    return false;
  }
}
