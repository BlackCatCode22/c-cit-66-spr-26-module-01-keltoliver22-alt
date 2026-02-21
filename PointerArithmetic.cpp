#include <iostream>
using namespace std;

int main() {
    // 1. Create an array of 5 integers
    int arr[5] = {1, 2, 3, 4, 5};

    // 2. Initialize pointer 'p' to the start of the array
    // Note: 'arr' itself is essentially the address of arr[0]
    int *p = arr;

    // 3. Use a loop to traverse the array using pointer arithmetic
    for (int i = 0; i < 5; ++i) {
        // (p + i) calculates the address of the i-th element
        cout << "Address of arr[" << i << "]: " << (p + i) << endl;

        // *(p + i) dereferences that specific address to get the value
        cout << "Value of arr[" << i << "]: " << *(p + i) << endl;
    }

    return 0;
}
