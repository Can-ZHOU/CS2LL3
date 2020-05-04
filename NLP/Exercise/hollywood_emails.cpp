#include <string>
#include <iostream>
#include <fstream>
using namespace std;

int main() {
    ifstream myFile;
    myFile.open("email.txt");

    string email;
    while(myFile >> email) {
        size_t at_pos;
        at_pos = email.find('@');
        size_t len;

        len = at_pos;
        string login = email.substr(0, len);
        if(len!=0) {
            cout<< login << endl;
        }
    }
}