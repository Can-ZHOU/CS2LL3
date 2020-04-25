#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    vector<string> Tuple;
    vector<vector<string>> tuples;
    Tuple = {"Tom", "Harry"};
    for(int i=0; i<Tuple.size(); i++) {
        cout<<Tuple[i]<<" ";
    }
    cout<<endl;
    tuples.push_back(Tuple);
    tuples.push_back(Tuple);
    tuples.push_back(Tuple);
    tuples.push_back(Tuple);
    tuples.push_back(Tuple);
    for(int i=0; i<tuples.size(); i++) {
        reverse(tuples[i].begin(), tuples[i].end());
        cout<<"hi"<<endl;
    }
    for(int i=0; i<tuples.size(); i++) {
        for(int j=0; j<tuples[i].size(); j++) {
            cout<<tuples[i][j]<<" ";
        }
        cout<<endl;
    }
}