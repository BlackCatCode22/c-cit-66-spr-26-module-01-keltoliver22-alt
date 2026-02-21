#include <iostream>
using namespace std;

int main() {
    // Declare an integer variable 'a' and initialize it
    int a = 10;

    // Declare a pointer 'p' to an integer
    int *p;

    // Assign the address of 'a' to 'p'
    p = &a;

    // Print the address stored in 'p'
    cout << "Address in pointer p: " << p << endl;

    // Print the value of 'a' using the pointer p (dereferencing)
    cout << "Value of a using pointer p: " << *p << endl;

    //  Change the value of 'a' using pointer p
    *p = 20;

    // Print the new value of 'a' to verify the change
    cout << "New value of a: " << a << endl;

    return 0;
}


