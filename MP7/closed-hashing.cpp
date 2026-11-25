//Hash Table implemented as Closed Hashing with Linear collision resolution
 
#include <iostream>
using namespace std;
 
#define SIZE 10
#define EMPTY -1
#define DELETED -2
 
class HashTable {
private:
    int table[SIZE];
 
    int hashFunction(int key) {
        return key % SIZE;
    }
 
public:
    HashTable() {
        for (int i = 0; i < SIZE; i++)
            table[i] = EMPTY;
    }
 
    // Insert a key using linear probing
    void insert(int key) {
        if (key == EMPTY || key == DELETED) {
            cout << "Invalid key. Try another value.\n";
            return;
        }
 
        int index = hashFunction(key);
        int deletedPos = -1;
 
        for (int i = 0; i < SIZE; i++) {
            int pos = (index + i) % SIZE;
 
            if (table[pos] == key) {
                cout << "Duplicate key.\n";
                return;
            }
 
            if (table[pos] == DELETED && deletedPos == -1)
                deletedPos = pos;
 
            if (table[pos] == EMPTY) {
                if (deletedPos != -1)
                    pos = deletedPos;
 
                table[pos] = key;
                cout << "Inserted at index "
<< pos << endl;
                return;
            }
        }
 
        // Table has no EMPTY slots, but may have DELETED slots
        if (deletedPos != -1) {
            table[deletedPos] = key;
            cout << "Inserted at index "
<< deletedPos << endl;
        }
        else {
            cout << "Hash table is full.\n";
        }
    }
 
    // Search for a key
    int search(int key) {
        int index = hashFunction(key);
 
        for (int i = 0; i < SIZE; i++) {
            int pos = (index + i) % SIZE;
 
            if (table[pos] == EMPTY)
                return -1;
 
            if (table[pos] == key)
                return pos;
        }
 
        return -1;
    }
 
    // Delete a key
    void remove(int key) {
        int pos = search(key);
 
        if (pos == -1) {
            cout << "Key not found.\n";
            return;
        }
 
        table[pos] = DELETED;
        cout << "Key deleted from index "
<< pos << endl;
    }
 
    // Display the hash table
    void display() {
        cout << "\nINDEX\tVALUE\n";
        cout << "----------------\n";
 
        for (int i = 0; i < SIZE; i++) {
            cout << i << "\t";
 
            if (table[i] == EMPTY)
                cout << "EMPTY";
            else if (table[i] == DELETED)
                cout << "DELETED";
            else
                cout << table[i];
 
            cout << endl;
        }
    system("pause");
    }
};
int menu(){
int op;
system("cls");
cout << "\n===== HASH TABLE MENU =====\n";
        cout << "1. Insert key\n";
        cout << "2. Search key\n";
        cout << "3. Delete key\n";
        cout << "4. Display hash table\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> op;
        return op;
}
int main() {
    HashTable h;
    int key;
 
while(true){
 
        switch (menu()) {
        case 1:
            cout << "Enter key to insert: ";
            cin >> key;
            h.insert(key);
            break;
 
        case 2:
            cout << "Enter key to search: ";
            cin >> key;
 
            {
                int pos = h.search(key);
 
                if (pos != -1)
                    cout << "Key found at index "
<< pos << endl;
                else
                    cout << "Key not found.\n";
            }
            break;
 
        case 3:
            cout << "Enter key to delete: ";
            cin >> key;
            h.remove(key);
            break;
 
        case 4:
            h.display();
            break;
 
        case 5:
            cout << "Program terminated.\n";
            exit(0);
 
        default:
            cout << "Invalid choice. Try again.\n";
        }
 
    }
 
    return 0;
}