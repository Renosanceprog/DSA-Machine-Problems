/*
GARCIA, IZZE MATTHEW S.
BSCS - 2B
MACHINE PROBLEM 4
*/

#include <iostream>
#include <iomanip>
#define MAX 10

using namespace std;

class StackArray{
    private:
        int stk[MAX];
        int Top;

        bool isFull(){
            return Top == 0;
        };

        bool isEmpty(){
            return Top == MAX;
        };

    public:
        StackArray(){
            Top = MAX;
        };

        void push(int x){
            if (isFull()){
                cout << "Stack Overflow. Stack is full." << endl;
                return;
            }
            Top--;
            stk[Top] = x;
            cout << x << " pushed to stack." << endl;
        };

        void pop(){
            if (isEmpty()){
                cout << "Stack Underflow. Stack is empty." << endl;
                return;
            }
            cout << stk[Top] << " popped from stack." << endl;
            Top++;
        };

        void top(){
            if (isEmpty()){
                cout << "Stack is empty. No top element." << endl;
                return;
            }
            cout << "Top element: " << stk[Top] << endl;
        };

        void display(){
            cout << "\n| Stack Contents (Array) First In Last Out |" << endl;
            if (isEmpty()){
                cout << "(stack is empty)" << endl;
                return;
            }
            cout << "----------------------------" << endl;
            int j = 1;
            for (int i = Top; i < MAX; i++){
                cout << setw(7) << j << " .) | " << stk[i];
                if (i == Top) cout << "  <-- TOP";
                cout << endl;
                j++;
            }
            cout << "----------------------------" << endl;
        };
};

struct Node{
    int data;
    Node *next;

    Node(int d){
        data = d;
        next = NULL;
    }
};

class StackPointer{
    private:
        Node *Top;

        bool isEmpty(){
            return Top == NULL;
        };

    public:
        StackPointer(){
            Top = NULL;
        };

        void push(int x){
            Node *newNode = new Node(x);
            newNode->next = Top;
            Top = newNode;
            cout << x << " pushed to stack." << endl;
        };

        void pop(){
            if (isEmpty()){
                cout << "Stack Underflow. Stack is empty." << endl;
                return;
            }
            Node *p = Top;
            Top = Top->next;
            cout << p->data << " popped from stack." << endl;
            delete p;
        };

        void top(){
            if (isEmpty()){
                cout << "Stack is empty. No top element." << endl;
                return;
            }
            cout << "Top element: " << Top->data << endl;
        };

        void display(){
            cout << "\n| Stack Contents (Pointer) First In Last Out |" << endl;
            if (isEmpty()){
                cout << "(stack is empty)" << endl;
                return;
            }
            cout << "----------------------------" << endl;
            Node *p = Top;
            int j = 1;
            while (p != NULL){
                cout << setw(7) << j << " .) | " << p->data;
                if (p == Top) cout << "  <-- TOP";
                cout << endl;
                p = p->next;
                j++;
            }
            cout << "----------------------------" << endl;
        };
};

int stackMenu(){
    int choice;
    cout << "\n| [1] - Array implementation |";
    cout << "\n| [2] - Pointer implementation |";
    cout << "\n| [3] - Exit |";
    cout << "\nEnter your choice: ";
    cin >> choice;
    return choice;
};

int stackOpMenu(){
    int choice;
    cout << "\n| [1] - Push |";
    cout << "\n| [2] - Pop |";
    cout << "\n| [3] - Top |";
    cout << "\n| [4] - Display |";
    cout << "\n| [5] - Exit |";
    cout << "\nEnter your choice: ";
    cin >> choice;
    return choice;
};

int main(){
    StackArray array;
    StackPointer pointer;
    int val;

    cout << "\n| Welcome to Machine Problem 4 |";
    cout << "\n| Stack ADT: Array and Pointer Implementations |";

    while (1){
        switch (stackMenu()){
            case 1:
                while (1){
                    int opChoice = stackOpMenu();
                    if (opChoice == 5){
                        cout << "Returning to main menu...\n";
                        break;
                    }
                    switch (opChoice){
                        case 1:
                            cout << "Enter value to push: ";
                            cin >> val;
                            array.push(val);
                            break;

                        case 2:
                            array.pop();
                            break;

                        case 3:
                            array.top();
                            break;

                        case 4:
                            array.display();
                            break;

                        default:
                            cout << "| Invalid input try again! |";
                            break;
                    }
                }
                break;

            case 2:
                while (1){
                    int opChoice = stackOpMenu();
                    if (opChoice == 5){
                        cout << "Returning to main menu...\n";
                        break;
                    }
                    switch (opChoice){
                        case 1:
                            cout << "Enter value to push: ";
                            cin >> val;
                            pointer.push(val);
                            break;

                        case 2:
                            pointer.pop();
                            break;

                        case 3:
                            pointer.top();
                            break;

                        case 4:
                            pointer.display();
                            break;

                        default:
                            cout << "| Invalid input try again! |";
                            break;
                    }
                }
                break;

            case 3:
                cout << "Exiting Program...";
                exit(0);

            default:
                cout << "| Invalid input try again! |";
                break;
        }
    }
}