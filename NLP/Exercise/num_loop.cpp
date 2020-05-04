#include <iostream>
using namespace std;

int main() {
    float sum, input;
    sum=0;

    while (1) {
        cout<<"enter a number:";
        cin>>input;
        sum += input;
        if (sum>10*input) {
            break;
        } else {
            cout<<"running total is: "<<sum<<endl;
        }
    }
    
}