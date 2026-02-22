#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

// Inserts a node at the end of the list
void insertEnd(Node** head, int newData) {
    Node* newNode = new Node();
    newNode->data = newData;
    newNode->next = nullptr;
    if (*head == nullptr) {
        *head = newNode;
    } else {
        Node* last = *head;
        while (last->next != nullptr) {
            last = last->next;
        }
        last->next = newNode;
    }
}

// Implement deleteNode function
void deleteNode(Node** head, int key) {
    Node* temp = *head;
    Node* prev = nullptr;

    // Case 1: If the head node itself holds the value to be deleted
    if (temp != nullptr && temp->data == key) {
        *head = temp->next; // Changed head
        delete temp;        // Free memory
        return;
    }

    // Case 2: Search for the value to be deleted, keep track of previous node
    while (temp != nullptr && temp->data != key) {
        prev = temp;
        temp = temp->next;
    }

    // Case 3: Value was not found in the list
    if (temp == nullptr) return;

    // Unlink the node from linked list
    prev->next = temp->next;

    // Free memory
    delete temp;
}

// Displays all nodes in the list
void displayList(Node* node) {
    while (node != nullptr) {
        cout << node->data << " ";
        node = node->next;
    }
    cout << endl;
}

int main() {
    Node* head = nullptr;

    // Adding nodes
    insertEnd(&head, 1);
    insertEnd(&head, 2);
    insertEnd(&head, 3);

    cout << "Original list: ";
    displayList(head);

    // Deleting a node
    cout << "Deleting node with value 2..." << endl;
    deleteNode(&head, 2);

    cout << "Updated list: ";
    displayList(head);

    return 0;
}
