#include <string>
#include <iostream>
using namespace std;


int main() {

  string s;
  cout << "enter a word\n";
  cin >> s;
  for(int i=0; i < s.size(); i++) {
    char c;
    c = s[i];
    cout << c << " ";

  }
    cout << endl;

}

