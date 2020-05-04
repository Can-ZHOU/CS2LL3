#include "trees.h"

int main() {
  Tree *t0;
  Category c0;
  c0 = Category("[0]");
  t0 = new Tree(c0);

  Tree *t1;
  Category c1;
  c1 = Category("[1]");
  t1 = new Tree(c1);

  Tree *t2;
  Category c2;
  c2 = Category("[2]");
  t2 = new Tree(c2);


  Tree *t3;
  Category c3;
  c3 = Category("3");
  t3 = new Tree(c3);

  t3->dtrs.push_back(t0);
  t3->dtrs.push_back(t1);
  t3->dtrs.push_back(t2);

  t3->dot_tree();

  delete t3;
}
