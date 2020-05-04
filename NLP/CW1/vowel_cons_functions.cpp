#include <string>
#include <iostream>
using namespace std;

bool is_vowel(char c);
bool is_cons(char c);

bool is_vowel(char c) {

  if (c == 'a') {
    return true;
  }
  else if (c == 'e') {
    return true;
  }
  else if (c == 'i') {
    return true;
  }
  else if (c == 'o') {
    return true;
  }
  else if (c == 'u') {
    return true;
  }
  else {
    return false;
  }

}


bool is_cons(char c) {
  if(is_vowel(c)) {
    return false;
  }
  else if(c >= 97 && c <= 122) {
    return true;
  }
  else {
    return false;
  }
}


