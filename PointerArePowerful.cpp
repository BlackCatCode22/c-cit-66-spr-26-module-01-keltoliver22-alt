#include <iostream>
using namespace std;

int main() {
    // Variable and pointer declaration
    int a = 10;
    int *p;

    // Pointing p to the address of a
    p = &a;

    // Printing the pointer's memory address
    cout << "Memory address of a: " << p << endl;

    // Printing the value of a by dereferencing p
    cout << "Original value of a (using p): " << *p << endl;

    // Changing the value through the pointer
    *p = 50;

    // Checking if a actually changed
    cout << "Updated value of a: " << a << endl;

    return 0;
}
