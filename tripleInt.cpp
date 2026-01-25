#include <iostream>
using namespace std;

int main() {
    int userNumber;

    cout << "Enter an integer: ";
    cin >> userNumber;

    int tripled = userNumber * 3;

    cout << "Tripled value: " << tripled << endl;

    return 0;
}