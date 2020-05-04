#include <string>
#include <vector>
#include <iostream>
#include <fstream>
using namespace std;

bool is_an_email(string s);

main() {

  string filename;
  cout << "which file\n";
  cin >> filename;
  
  ifstream f;
  f.open(filename);
  if(!f) { cout << "could not open\n"; return 0; }

  // // block to test is_an_email
  // // you might want to un-comment this to test your function before
  // // proceeding
  // vector<string> emails = {"amy@blah", "@blah", "blah@"};
  // for(int i=0; i < emails.size(); i++) {
  //   cout << emails[i] << ": ";
  //   if(is_an_email(emails[i])) { cout << "yep\n";}
  //   else { cout << "nope\n";}
  // }

  // ADD FURTHER CODE HERE
  // make a vector of all the file's contents and then process that
  
  // DESIRED BEHAVIOUR: if run on top_secret_file should see
  
  // lisa@simpsons.sit.com
  // joey@friends.sit.com
  // homer@simpsons.sit.com
  // marge@simpsons.sit.com
  // bart@simpsons.sit.com
  // maggie@simpsons.sit.com
  // rachel@friends.sit.com
  // ross@friends.sit.com
  // chandler@friends.sit.com
  // monica@friends.sit.com

  int is_top_secret = 0;
  string word;

  vector<string> emails;

  /* go through the whole file*/
  while(f >> word) {
    if(word == "TOP-SECRET") {
      is_top_secret = 1;
    }

    if(is_an_email(word)) {
      emails.push_back(word);
    }
  }

  /* the part I commented below is for outputing
   the emails into an aptly named file in /tmp */
  if(is_top_secret) {
    // ofstream outFile("/tmp/"+filename);
    for(int i=0; i<emails.size(); i++) {
      cout<< emails[i] <<endl;
      // outFile<< emails[i] <<'\n';
    }
    // outFile.close();
  }

}
  

// COMPLETE THE FUNCTION is_an_email(string s) 
// it should check that
// s contains @ somewhere,
//  but not right at start
//  and not right at end
// ie.
//  amy@blah -> true
//  @blah    -> false
//  blah@    -> false
bool is_an_email(string s) {
  size_t len = s.find('@');

  if(len == string::npos) {
    return false;
  } else if(len==0 || len==s.size()-1) {
    return false;
  } else {
    return true;
  }
}

