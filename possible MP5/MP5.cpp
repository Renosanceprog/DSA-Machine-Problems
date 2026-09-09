#include <iostream>
#include <stdio.h>

#define MAX 3

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
        if (isEmpty()) {cout<<"Queue is empty, Queue some elements first."<<endl; return -1;}
        ctr--;
        return arr[f++];
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
        if (isEmpty()) {cout<<"Queue is empty, Queue some elements first."<<endl; return;}
        while (c != ctr)
        {
            p = p % MAX;
            cout<<arr[p++];
            if (c < ctr-1) cout<<" <- ";
            c++;
        }
        cout<<endl;
        cout<<endl;        
    }
};

int main(int argc, char const *argv[])
{
    arrQueue p1 = arrQueue();
    return 0;
}
