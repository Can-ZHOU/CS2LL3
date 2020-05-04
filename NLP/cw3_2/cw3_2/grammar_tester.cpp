#include "Grammar.h"
#include <iostream>
#include <stdlib.h>

using namespace std;

main(int argc, char *argv[]) {

  if(argc != 2) { 
    cout << "need to give a filename for the grammar\n";
    exit(1);
  }
  
  
  Grammar g(argv[1]);

  g.show();

}
