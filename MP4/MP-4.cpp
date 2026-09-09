#include <iostream>
#include <stdio.h>
#define MAX 5

using namespace std;

class ArrStk
{
    private:
    int stck[MAX] = {0};
    int topptr;

    bool isEmpty()
    {
        return topptr == -1;
    }
    bool isFull()
    {
        return topptr == MAX;
    }
    public:
    ArrStk()
    {
        topptr = -1;
    }
    void push(int data)
    {
        if (isFull())
        {
            cout<<"could not push "<<data<<". Stack is Full.\n";
            return;
        }
        stck[++topptr] = data;
        cout<<"pushed "<<data<<" to Stack Successfully.\n";
    }
    int pop()
    {
        if (isEmpty())
        {
            cout<<"could not pop. Stack is Empty.\n";
            return -1;
        }
        int temp = stck[topptr];
        stck[topptr] = 0;
        topptr--;
        cout<<"popped "<<temp<<" to Stack Successfully.\n";
        return temp;
    }

    int top()
    {
        if (isEmpty())
        {
            cout<<"could not top. Stack is Empty.\n";
            return -1;
        }
        cout<<stck[topptr]<<" is Top Element in the Stack.\n";
        return stck[topptr];
    }

    void display()
    {
        for (int i = MAX-1; i >= 0; i--)
        {
            printf("(idx:%2d) - [ %3d ]", i, stck[i]);
            if (i == topptr) cout<<"<- Top of Stack";
            cout<<endl;
        }
        cout<<endl;
    }
};

struct stckNode
{
    int data;
    stckNode *next;
    stckNode()
    {
        next = NULL;
    }
};

class llStk
{
    private:
    int stkLen;
    stckNode *topptr;
    bool isEmpty()
    {
        return stkLen == 0;
    }
    bool isFull()
    {
        return stkLen == MAX;
    } 
    public:
    llStk()
    {
        stkLen = 0;
        topptr = NULL;
    }
    void push(int data)
    {
        if (isFull())
        {
            cout<<"could not push "<<data<<". Developer Stack limit is Reached.\n";
            return;
        }
        stckNode *newnode = new stckNode();
        newnode->data = data;
        newnode->next = topptr;
        topptr = newnode;
        stkLen++;
        cout<<"pushed "<<data<<" to Stack Successfully.\n";
    }
    int pop()
    {
        if (isEmpty())
        {
            cout<<"could not pop. Stack is Empty.\n";
            return -1;
        }
        int temp = topptr->data;
        stckNode *q = topptr;
        topptr = topptr->next;
        delete(q);
        stkLen--;
        cout<<"popped "<<temp<<" to Stack Successfully.\n";
        return temp;
    }

    int top()
    {
        if (isEmpty())
        {
            cout<<"could not top. Stack is Empty.\n";
            return -1;
        }
        cout<<topptr->data<<" is Top Element in the Stack.\n";
        return topptr->data;
    }

    void display()
    {
        stckNode *walker = topptr;
        int i = 1;
        for (size_t i = 0; i < MAX-stkLen; i++) printf("(node: #) - [ NULL ]\n");
        while (walker != NULL)
        {
            printf("(node:%2d) - [ %4d ]", i, walker->data);
            if (i == 1) cout<<"<- Top of Stack";
            i++;
            cout<<endl;
            walker = walker->next;
        }

        cout<<endl;
    }
};

int menu();
int methods_menu();

int main(int argc, char const *argv[])
{
    ArrStk s1 = ArrStk();
    llStk s2 = llStk();
    int main_opt;
    main_menu:
    while (true)
    {
        main_opt = menu();
        if (main_opt == 1 || main_opt == 2)
        {
            while (true)
            {
                switch (methods_menu())
                {
                case 1:
                    cout<<"Enter data to push to Stack: ";
                    int num;
                    cin>>num;
                    
                    if (main_opt == 1) s1.push(num);
                    else s2.push(num);
                    break;
                case 2:
                    if (main_opt == 1) s1.pop();
                    else s2.pop();
                    break;
                case 3:
                    if (main_opt == 1) s1.top();
                    else s2.top();
                    break;
                case 4:
                    if (main_opt == 1) s1.display();
                    else s2.display();
                    break;
                case 0:
                    goto main_menu;
                    break;
                default:
                    cout<<"Invalid input Try Again..."<<endl;
                    break;
                }
                cin.ignore();
                cin.get();
            }
        }
        else if (main_opt == 0) goto exit_menu;
        else cout<<"Invalid input Try Again..."<<endl;

        cin.ignore();
        cin.get();
    }
    exit_menu:
    return 0;
}

int menu()
{
    int opt;
    printf("\033[H\033[2J");
    cout<<"=== Sir Rene's Stack ADT Implementation Demo! ==="<<endl;
    cout<<"[1] Array Stack Implementation"<<endl;
    cout<<"[2] Linked List Stack Implementation"<<endl;
    cout<<"[0] Quit"<<endl;
    cout<<endl<<"Choose Option: ";
    cin>>opt;
    return opt;
}

int methods_menu()
{
    int opt;
    printf("\033[H\033[J");
    cout<<"== Stack Operations =="<<endl;
    cout<<"[1] Push Element to Stack"<<endl;
    cout<<"[2] Pop Element to Stack"<<endl;
    cout<<"[3] Peek the Top Element"<<endl;
    cout<<"[4] Display Stack"<<endl;
    cout<<"[0] Go back to Main Menu"<<endl;

    cout<<endl<<"Choose Option: ";
    cin>>opt;
    return opt;
}