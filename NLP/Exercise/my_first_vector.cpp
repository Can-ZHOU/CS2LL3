#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<int> veci;
    veci.push_back(1);
    cout<<veci[0]<<endl;

    vector<int> nums(3);
    nums[0] = 3;
    nums[1] = 2;
    nums[2] = 1;
    cout<<nums[0]<<'\n'<<nums[1]<<'\n'<<nums[2]<<endl;

    vector<string> vecs = {"a", "bc", "def"};
    for(int i=0; i<vecs.size(); i++) {
        cout<<vecs[i];
    }
    cout<<'\n';
}