#include <iostream>
#include <string>
using namespace std;

int main() {
    string name;

    cout << "Hello! What is your name? ";
    getline(cin, name);

    cout << "Hello, " << name << "! Nice to meet you." << endl;

    return 0;
}