#include <iostream>
#include <stdio.h>

#define MAX 5

using namespace std;

// array circular queue
class arrQueue
{
    private:
    int arr[MAX];
    int f,r,ctr;
    bool isEmpty(){return ctr == 0;}
    bool isFull(){return ctr == MAX;}
    public:
    arrQueue()
    {
        f = 0;
        r = -1;
        ctr = 0;
    }
    void enqueue(int data)
    {
        if (isFull()) {cout<<"Queue is Full, Dequeue some elements first."<<endl; return;}
        r = (r+1) % MAX;
        arr[r] = data;
        ctr++;
        cout<<"queued "<<data<<", f = "<<f<<", r = "<<r<<endl;
    }
    int dequeue()
    {
        if (isEmpty()) {cout<<"Queue is empty..."<<endl; return -1;}
        int val = arr[f];
        f = (f + 1) % MAX;
        ctr--;
        cout<<"dequeued "<<val<<", f = "<<f<<", r = "<<r<<endl;
        return val;
    }
    int peek()
    {
        cout<<arr[f]<<" is first in line"<<endl;
        return arr[f];
    }
    int size()
    {
        cout<<ctr<<" is the current queue size"<<endl;
        return ctr;
    }
    void display()
    {
        int p = f;
        int c = 0;
        cout<<endl;
        if (isEmpty()) {cout<<"Queue is empty, Queue some elements first."<<endl; return;}
        for(int c = 0; c < ctr; c++) 
        {
            p = p % MAX;
            cout<<arr[p++];
            if (c < ctr-1) cout<<" <- ";
        }
        cout<<endl;
    }
};

struct qNode
{
    int data;
    qNode *next;
    qNode()
    {
        next = NULL;
    }
};

class LlQueue
{
    private:
    qNode *f, *r;
    int ctr;

    bool isEmpty(){return ctr == 0;}
    bool isFull(){return ctr == MAX;}

    public:
    LlQueue()
    {
        f = NULL;
        r = NULL;
        ctr = 0;
    }
    void enqueue(int data)
    {
        if (isFull()) {cout<<"Queue is Full, Dequeue some elements first."<<endl; return;}
        
        qNode *newnode = new qNode();
        newnode->data = data;

        if (isEmpty()) {
            f = r = newnode;
            r->next = f;
        } else {
            r->next = newnode;
            r = newnode;
            r->next = f;
        }

        ctr++;
        cout<<"queued "<<data<<endl;
    }

    int dequeue()
    {
        if (isEmpty()) {cout<<"Queue is empty, Queue some elements first."<<endl; return -1;}
        
        int val = f->data;
        qNode *del = f;

        if (f == r) f = r = NULL;
        else
        {
            f = f->next;
            r->next = f;
        }

        delete del;
        ctr--;
        return val;
    }
    void display()
    {
        if (isEmpty()) {cout<<"Queue is empty, Queue some elements first."<<endl; return;}
        qNode *w = f;
        int c = 0;
        cout<<endl;
        for(int c = 0; c < ctr; c++) 
        {
            cout<<w->data;
            if (c < ctr-1) cout<<" <- ";
            w = w->next;
        }
        return;
    }
};

class LlQueueUnlimited
{
    private:
    qNode *f, *r;
    int ctr;

    bool isEmpty(){return ctr == 0;}

    public:
    LlQueueUnlimited()
    {
        f = NULL;
        r = NULL;
        ctr = 0;
    }
    
    void enqueue(int data)
    {
        qNode *newnode = new qNode();
        newnode->data = data;

        if (isEmpty()) {
            f = r = newnode;
            r->next = f;
        } else {
            r->next = newnode;
            r = newnode;
            r->next = f;
        }

        ctr++;
        cout<<"queued "<<data<<endl;
    }

    int dequeue()
    {
        if (isEmpty()) {cout<<"Queue is empty, Queue some elements first."<<endl; return -1;}
        
        int val = f->data;
        qNode *del = f;

        if (f == r) f = r = NULL;
        else
        {
            f = f->next;
            r->next = f;
        }

        delete del;
        ctr--;
        return val;
    }
    
    void display()
    {
        if (isEmpty()) {cout<<"Queue is empty, Queue some elements first."<<endl; return;}
        qNode *w = f;
        cout<<endl;
        for(int c = 0; c < ctr; c++) 
        {
            cout<<w->data;
            if (c < ctr-1) cout<<" <- ";
            w = w->next;
        }
        cout<<endl;
        return;
    }
};

int menu();
int methods_menu();

int main(int argc, char const *argv[])
{
    arrQueue q1 = arrQueue();
    LlQueue q2 = LlQueue();
    LlQueueUnlimited q3 = LlQueueUnlimited();
    int main_opt;
    
    main_menu:
    while (true)
    {
        main_opt = menu();
        if (main_opt == 1 || main_opt == 2 || main_opt == 3)
        {
            while (true)
            {
                switch (methods_menu())
                {
                case 1:
                    cout<<"Enter data to push to Queue: ";
                    int num;
                    cin>>num;
                    
                    if (main_opt == 1) q1.enqueue(num);
                    else if (main_opt == 2) q2.enqueue(num);
                    else q3.enqueue(num);
                    break;
                case 2:
                    if (main_opt == 1) q1.dequeue();
                    else if (main_opt == 2) q2.dequeue();
                    else q3.dequeue();
                    break;
                case 3:
                    if (main_opt == 1) q1.display();
                    else if (main_opt == 2) q2.display();
                    else q3.display();
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
    cout<<"=== Sir Rene's Queue ADT Implementation Demo! ==="<<endl;
    cout<<"[1] Array Queue Implementation"<<endl;
    cout<<"[2] Linked List Queue Implementation"<<endl;
    cout<<"[3] Unlimited Linked List Queue Implementation"<<endl;
    cout<<"[0] Quit"<<endl;
    cout<<endl<<"Choose Option: ";
    cin>>opt;
    return opt;
}

int methods_menu()
{
    int opt;
    printf("\033[H\033[J");
    cout<<"== Queue Operations =="<<endl;
    cout<<"[1] Enqueue Element to Queue"<<endl;
    cout<<"[2] Dequeue Element to Queue"<<endl;
    cout<<"[3] Display Queue"<<endl;
    cout<<"[0] Go back to Main Menu"<<endl;

    cout<<endl<<"Choose Option: ";
    cin>>opt;
    return opt;
}