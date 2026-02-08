#include <iostream>
using namespace std;

int main() {

    int a, b, c;
    int biggest;

    cout << "Type first number: ";
    cin >> a;
    cout << "Type second number: ";
    cin >> b;
    cout << "Type third number: ";
    cin >> c;

    // find the largest using nested ifs
    if(a > b){
        if(a > c){
            biggest = a;
        }
        else{
            biggest = c;
        }
    }
    else{
        if(b > c){
            biggest = b;
        }
        else{
            biggest = c;
        }
    }

    cout << "Biggest number is " << biggest << endl;

    return 0;
}