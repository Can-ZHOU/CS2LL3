#include <fstream>
#include <iostream>
using namespace std;

main() {
  int nbracks = 0;
  char c;
  ifstream myfile;
  myfile.open("testfile");
  myfile.unsetf(ios::skipws);

  while(myfile >> c) {
    if (c == '(') {
      nbracks++;
    }
    else if (c == ')') {
      nbracks--;
    }
    else if (nbracks == 0) {
      cout << c;
    }
  }

}