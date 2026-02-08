// reversedStrings.cpp
#include <iostream>
#include <string>
using namespace std;

int main() {
    string input;
    string reversed = "";

    cout << "Enter a string: ";
    getline(cin, input);   // reads the whole line (even spaces)

    // Reverse the string using a loop
    for (int i = input.length() - 1; i >= 0; i--) {
        reversed += input[i];
    }

    cout << "Reversed string: " << reversed << endl;

    return 0;
}