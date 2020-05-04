#include "rules.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include "trees.h"
using namespace std;

Tree * Passify(Tree *T1) {
    Tree * passify_tree = new Tree(T1->mother);

    // add DET
    passify_tree->dtrs.push_back(T1->dtrs[0]);
    // add N
    passify_tree->dtrs.push_back(T1->dtrs[1]);
    // add [which]
    passify_tree->dtrs.push_back(T1->dtrs[2]);

    // create new tree for TV-PASS
    Category tvPass("TV-PASS");
    Tree * TV_PASS = new Tree(tvPass);

    // add [was] to TV-PASS
    Category c_was("[was]");
    Tree * was = new Tree(c_was);
    TV_PASS->dtrs.push_back(was);
    // add TV to TV-PASS
    TV_PASS->dtrs.push_back(T1->dtrs[4]);

    // add TV-PASS
    passify_tree->dtrs.push_back(TV_PASS);

    // add [by]
    Category c_by("[by]");
    Tree * by = new Tree(c_by);
    passify_tree->dtrs.push_back(by);

    // add NP
    passify_tree->dtrs.push_back(T1->dtrs[3]);

    return passify_tree;
}

int main() {
    Tree *t0, *t1, *t2, *t3, *t4, *t5;
    Category c0;
    c0 = Category("NP");
    t0 = new Tree(c0);

    Category c1("DET");
    Category c2("N");
    Category c3("[Which]");
    Category c4("NP");
    Category c5("TV");

    t1 = new Tree(c1);
    t2 = new Tree(c2);
    t3 = new Tree(c3);
    t4 = new Tree(c4);
    t5 = new Tree(c5);

    t0->dtrs.push_back(t1);
    t0->dtrs.push_back(t2);
    t0->dtrs.push_back(t3);
    t0->dtrs.push_back(t4);
    t0->dtrs.push_back(t5);

    t0->drawtree();

    cout << endl;

    Tree * test = Passify(t0);

    test->drawtree();

}