#include "trees.h"

// makes a tree with 2 nodes
// top node is green, labeled with t
// bottom node is red, labeled with o
// implementation in this file
Tree *make_green_red(void);

// takes an input tree t_in
// returns a tree with a top node, which is green, labeled with t
// and which has 3 daughter trees
// the middle daughter tree is t_in
// the left and right daughter trees are 2 node green-then-red trees
// implementation not in this file
Tree *add_to_tree(Tree *t1);

// implementation of make_green_red
Tree *make_green_red() {

  Category l("[o]");
  Tree *red;
  red = new Tree(l);

  Category i("t");
  Tree *green;
  green = new Tree(i);

  green->dtrs.push_back(red);
  
  return green; // note this effectively returns the top node of a 2 node tree

}


main() {
  Tree *t0;

  Category i;
  i = Category("t");

  // a one node green tree
  t0 = new Tree(i);
  t0->dot_tree();

  // a 2 node green-red tree
  t0 = make_green_red();
  t0->dot_tree();


  // make a large tree by 
  // starting with a one node green tree
  // then repeatedly give the tree so far to add_to_tree to 
  // make it bigger 
  // finally show it
 
  // then use add_to_tree to 
  t0 = new Tree(i);

  // then recursively build on top
  t0 = add_to_tree(t0);
  t0 = add_to_tree(t0);
  t0 = add_to_tree(t0);
  t0 = add_to_tree(t0);

  t0->dot_tree();
  

}
