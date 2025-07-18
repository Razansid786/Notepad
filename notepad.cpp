#include <iostream>
#include <conio.h>
#include <cstdlib>
#include <fstream>
#include <string>
using namespace std;


class doubly {
    struct Node {
        char data;
        Node* next;
        Node* prev;
        Node(char val, Node* nptr = nullptr, Node* pptr = nullptr ): data(val), next(nptr), prev(pptr) {}

    };
    Node* head, *tail, *cursor;
    int cursorIndex = 0;
public:
    doubly(): head(nullptr), tail(nullptr), cursor(nullptr) {}

    void initializeCursor() {
        Node* temp = new Node('|');
        cursor = temp;
    }

    void insertAtHead(const char val) {
        Node* temp = new Node(val);
        if (head == nullptr) {
            head = temp;
            tail = temp;
            tail->next = cursor;
            return;
        }
        temp->next = head;
        head->prev = temp;
        head = temp;
    }

    void print() {
        Node* temp = head;
        while (temp != nullptr)
        {
            cout << temp->data;
            temp = temp->next;
        }
    }

    void insertAtTail(const char val) {
        if (head == nullptr) {
            insertAtHead(val);
            return;
        }
        Node* temp = new Node(val);
        tail->next = temp;
        temp->prev = tail;
        tail = temp;
        tail->next = cursor;
        cursor->prev = tail;
    }

    void deleteAtHead() {
        if (head == nullptr || head->prev == cursor) {
            return;
        }
        Node* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
    }

    void deleteAtTail() {
        if (head == nullptr) {
            return;
        }
        Node* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            tail = tail->prev;
            cursor->prev = tail;
            tail->next = cursor;
        }
        delete temp;
    }

    void insertAtCursor(char val) {
        if (cursor->next == nullptr) {
            insertAtTail(val);
        }
        else if (cursor->prev != nullptr) {
            Node* temp = new Node(val);
            cursor->prev->next = temp;
            temp->next = cursor;
            temp->prev = cursor->prev;
            cursor->prev = temp;
        }
        else {
            insertAtHead(val);
        }
    }

    void deleteAtCursor() {
        
        if (cursor->prev == nullptr) {
        return;
        if (head == nullptr) {
            return;
        }
        deleteAtHead(); 
        } 
        else if (cursor->next == nullptr) { 
            deleteAtTail();
        } 
        else {
            
            Node* prevNode = cursor->prev;
            Node* newPrevNode = prevNode->prev;

            if (newPrevNode != nullptr) {  
                newPrevNode->next = cursor;
            } else {  
                head = cursor;
            }

            cursor->prev = newPrevNode;
            delete prevNode;
        }

    }

    void moveCursorLeft() {
        
        if (cursor->prev != nullptr) {  
            Node* prevNode = cursor->prev;
            Node* newPrevNode = prevNode->prev;

           
            prevNode->next = cursor->next;
            if (cursor->next != nullptr) {
                cursor->next->prev = prevNode;
            }

           
            cursor->next = prevNode;
            cursor->prev = newPrevNode;

            if (newPrevNode != nullptr) {
                newPrevNode->next = cursor;
            } else {
                head = cursor;  
            }

            prevNode->prev = cursor;
        }
    }

    void moveCursorRight(){

        if (cursor->next != nullptr) {
            Node* nextNode = cursor->next;
            Node* prevNode = cursor->prev;

            if (nextNode->next != nullptr) {
                nextNode->next->prev = cursor;
            }

            if (prevNode != nullptr) {
                prevNode->next = nextNode;
            } else {
                head = nextNode;
            }

            nextNode->prev = prevNode;
            cursor->prev = nextNode;
            cursor->next = nextNode->next;
            nextNode->next = cursor;
        }
    }

    
    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file" << endl;
            return;
        }

        Node* temp = head;
        while (temp != nullptr) {
            file << temp->data;
            temp = temp->next;
        }
        file.close();
    }

    void loadFromFile(string filename) {
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "Error opening file for reading" << endl;
            return;
        }

        cout << "Loading file contents...\n\n";

        char ch;

        while (file.get(ch)) {
            insertAtTail(ch);
        }
        file.close();
    }

    void run() {
        char choice;
        initializeCursor();
        cout << "Do you want to load a file? (y/n): ";
        cin >> choice;
        cin.ignore();
        if (choice == 'y' || choice == 'Y') {
            string filename;
            cout << "Enter filename to load: ";
            getline(cin, filename);
            loadFromFile(filename);
    }

        char input;
        while(true) {
            system("cls");
            print();
            cout<<endl<<"Cursor Index: "<<cursorIndex<<endl;
            input = getch();
            if (input == 27) {     //ESC
                break;
            }
            if (input == 13) {          //Enter
                string filename;
                cout << "Enter filename to save: ";
                cin >> filename;
                saveToFile(filename);
                return;
            }
            if (input == 224 || input == 0 ){   
                input = getch();
                switch (input) {
                    case 75:        
                        moveCursorLeft();
                        cursorIndex--;
                        break;
                    case 77:
                        moveCursorRight();
                        cursorIndex++;
                        break;
                }
            }
            else if (input == 8) {
                deleteAtCursor();
                cursorIndex--;
            }
            else {
                insertAtCursor(input);
                cursorIndex++;
            }
        }

    }
};

int main() {
    doubly s1;
    s1.run();
    return 0;
}