#include <iostream>
using namespace std;

// function to get an int from user
int getAnIntFromTheUser() {
    int num;
    cout << "Enter a number: ";
    cin >> num;
    return num;
}

// function to compare two ints
void compareTwoInts(int a, int b) {
    if (a > b) {
        cout << a << " is bigger than " << b << endl;
    } else if (b > a) {
        cout << b << " is bigger than " << a << endl;
    } else {
        cout << "Both numbers are the same." << endl;
    }
}

// function to add two ints
int sumTwoInts(int a, int b) {
    return a + b;
}

int main() {
    int num1 = getAnIntFromTheUser();
    int num2 = getAnIntFromTheUser();

    compareTwoInts(num1, num2);

    int sum = sumTwoInts(num1, num2);
    cout << "The sum is: " << sum << endl;

    return 0;
}