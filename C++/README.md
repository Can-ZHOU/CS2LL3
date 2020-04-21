## C++

### Key point
- 
```
#include <iostream> 
using namespace std;
```
- output:  
    ```cout <<```
- First steps with the debugger gdb:  
    ```g++ -g helloworld.cpp -o myprog```
- input:   
    ```cin >>```
- Strings and Files:
    ```c++
    /* open a stream to a file */
    /* read strings one by one */
    /* print the total */

    #include <string>
    #include <fstream>
    #include <iostream>
    using namespace std;

    main() {

        string word;
        ifstream myinput; /* creates a stream, not attached to anything */
        int i = 0;

        myinput.open("file_of_words"); /* attach stream to a file */

        while(myinput >> word) {
            i++;
        }

        cout << i << '\n';

    }
    ```
    - ifstream myinput; creates an stream object, for input from a file (ofstream for output, fstream for both).
    - myinput » word extracts from myinput into the variable word. Whitespace characters segment the stream, so repeatedly evaluating myinput » word extracts each successive word into the variable word.
- Separate Compilation and Linking
    - power_impl.cpp   
    ```C++
    int power(int base, int n);

    int power(int base, int n) {
        int i, p;

        p = 1;
        for (i = 1; i <= n; i = i + 1) {
            p = p * base;
        } 
        return p;
    }
    ```
    - power_use.cpp  
    ```C++
    #include <iostream>
    using namespace std;
    extern int power(int base, int n);

    main() {s
        int i;
        for (i = 0; i < 10; i = i + 1) {
            cout << i << " " << power(2,i) << " " << power(-3,i) << "\n";
        }
    }
    ```
    - one-liner:
    `g++ power_impl.cpp power_use.cpp -o my_power_prog`
    - compiled separately:
    ```
    g++ -c power_use.cpp
    g++ -c power_impl.cpp
    g++ power_impl.o power_use.o -o my_power_prog
    ```
- Reading single chars
    - not skip the white spaces    
        - `input.unsetf(ios::skipws);`
        - `input.get(c);`
- pass by reference
    - power(&reference), no need *;
- find char in string
    - `if(word.find('z') != string::npos)`
- vector
    ```
    vector<int> nums;
    nums.push_back(1);
    nums.size();
    ```
- Separate files and global scope 
    - function:  
    declaration for function in other file before using
    - Global Variables:  
    If file1 defines x, then file2 can access it by containing a similar declaration prefaced by the word `extern` (`extern int x;`). file2's declaration should not contain any initialisation for x. At most 1 file should put any initialisation into the declaration for x. 
    - Header Files and extern:  
    ```
    file1.cpp        file1.h           file2.cpp
    --------          -------          ---------
    nt x = 3;       extern int x;     #include "file1.h"
                     void f(int x);
    void f(int x) {                     main() {
       :                                  f(x);
       :                                  x++;
      }                                   :
                                        }
    ```
- Header files and class:
    - `#include "Person.h"`
    - `void Person::print(void)`
- Dynamic Memory Allocation:  
    - `new`
    - `delete`