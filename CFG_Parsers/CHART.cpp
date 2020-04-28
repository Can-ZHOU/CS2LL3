#include "CHART.h"
#include <iostream>


CHART::CHART(string grammar) {
  /* make a grammar */
  g = Grammar(grammar);
  chart_debug = 1;
}

CHART::CHART() {

}

bool CHART::accept(vector<string> key) {
 input = key;
 do_table();
 return(is_there(0,input.size(),g.initial));
 
}


void CHART::do_table() {
  clear_table();
  initialize();
  display_row(1);
  for(unsigned int k = 2; k <= input.size(); k++) {
    do_line(k);

    display_row(k);
  }

}

/* make chart have the right dimensions 
 *  then fill in the length 1 row with info derived from words
 */
void CHART::initialize() {
  
  /*********************************************************/
  /* first make chart have right dimensions                */
  /* for input of size M need to have chart[i][k] be legal */
  /* for i = 0 to M-1  and  k = 1 to M                     */
  /*********************************************************/
  chart.resize(input.size());
  for(size_t i = 0; i < chart.size(); i++) {
    chart[i].resize(input.size()+1);
  }

  Rule r;
  Category e;

  /* put words and their categories in */
  for(unsigned int i = 0; i < input.size(); i++) {
    e.terminal = true;
    e.cat = input[i];
    add_edge(i,1,e);
    for(unsigned int p = 0; p < g.rules.size(); p++) {
      r = g.rules[p];
      if (r.dtrs.size() == 1 && are_equal(r.dtrs[0],e)) {
	add_edge(i,1,r.mother);
      }
      else {}
    }

  }

}

/*! \param k the length being considered
 *
 * this should fill in length k entries \n 
 * so from chart[0][k] .. chart[M-k][k] where M is input length 
 */
void CHART::do_line(int k) {
  for (unsigned int i = 0; i <= (input.size()-k); i++) {
  do_cell(i,k);

  }
}

/*! \param start the start position
 *  \param length the length
 *
 *  should put every category C into chart[start][length] \n
 *  which is implied by rules applied to existing entries \n 
 *  for shorter lengths k' at appropriate positions 
 */
void CHART::do_cell(int i, int k) {
  Rule r;
  Category A, B, C;
  for(int a = 1; a < k; a++) {
     
    /* for each rule C --> A, B
       if A is at (i,a) 
       B is at (i+a,k-a)
       then put C at (i,k) */
    for(unsigned int p=0; p < g.rules.size(); p++) {
      r = g.rules[p];
      if (r.dtrs.size() != 2) {
	continue;
      }
      else {
	A = r.dtrs[0];
	B = r.dtrs[1];
	C = r.mother;
	if (is_there(i,a,A)  && is_there(i+a,k-a,B)) {
	  add_edge(i,k,C);
	}
      }
    }
  }  

}

/*! \param i the start position of the constituent
 *  \param k the length of the constituent
 *  \param c the Category of the constituent 
 * 
 * should check if c is already stored in chart[i][k] \n
 * note intention is not to deduce that it should be there based on shorter edges \n
 * but to detect that its presence has already been deduced 
 */
bool CHART::is_there(int i, int k, Category c) {

  bool there = false;
  size_t max;  
  max = chart[i][k].size();

  for(size_t wh =0; wh < max; wh++) { // wh for 'which category'
    if(are_equal(chart[i][k][wh],c)) {
      there = true;
      break;
    }
  }
  return there;

}

/*! \param i a start position 
 *  \param k a length 
 *  \param c a Category
 *
 * add c to entries in chart[i][k] if its not there already 
 */
void CHART::add_edge(int i, int k, Category c) {
  if(is_there(i,k,c)) {
    return;
  }
  else{
    chart[i][k].push_back(c);
  }
}


void CHART::clear_table() {
  for(size_t i=0; i < chart.size(); i++) {
    for(size_t k=0; k < chart[i].size(); k++) {
      chart[i][k].clear(); // empty this position of any contents
    }
  }

}

/*! 
 * \param length a length of edge to display
 *
 * for each possible start which could contain entries of that length should display all of chart[start][length] 
 *
 * note the max possible start will be M - length if M is length of the input
 */
void CHART::display_row(int length) {
  if(chart_debug) {
    /* prints cells for given length */
    int maxstart; // max possible start for edge of this length 
    maxstart = input.size()-length;
    cout << "length " << length << " ************************\n";
    for (int i = 0; i <= maxstart; i++) {
      string prefix = "";
      for (int w = 0; w < i; w++) {
	prefix += "  "; //cout << "  ";
      }
      for (int c = 0; c < chart[i][length].size(); c++) {
        cout << prefix << i << ":";
        chart[i][length][c].print();
	if (c != (chart[i][length].size() - 1)) {
	  cout << endl;
	}
      }
      cout << "\n";
    }
  }
}

