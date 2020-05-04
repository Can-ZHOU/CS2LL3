2
(a)
grammar:
s --> [a],s,[b]
s --> [a],[b]
initial(s)
tree: ...

(b)
```C++
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
    TV_PASS->dtrs.push_back(new Tree(c_was));
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
```

(c)
added rules:
np --> det,n,relpro,s/np
relpro --> [that]
s/np --> vp
s/np --> np,vp/np
vp/np --> tv
vp/np --> [put],np,[on]
vp/np --> [forced],np,[to],vp/np
trees:....

(d)
```C++
vector<Rule> gap_version(Rule r) {
    vector<Rule> rules;
    for(int i=0; i<r.dtrs.size(); i++) {
        if(r.dtrs[i].cat == "np") {
            Rule new_r = r;
            string str = r.mother.cat + "/np";
            Category new_mother(str);
            new_r.mother = new_mother;
            for(int j=i; j<new_r.dtrs.size()-1; j++) {
                Category tmp = new_r.dtrs[j];
                new_r.dtrs[j] = new_r.dtrs[j+1];
                new_r.dtrs[j+1] = tmp;
            }
            new_r.dtrs.pop_back();
            rules.push_back(new_r);
        }
    }
    return rules;
}
```