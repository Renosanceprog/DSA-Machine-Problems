#include <iostream>

using namespace std;

struct Node
{
    int num;
    Node* prev;
    Node* next;
    Node(int data)
    {
        num = data;
        prev = NULL;
        next = NULL;
    }
};

void newNode(int data, Node*& head)
{
    Node* p = head;
    Node* q = NULL;
    while (p != NULL && p->num > data)
    {
        q = p;
        p = p->next;
    }
    Node* newnode = new Node(data);
    q->next = newnode;
    newnode->prev = q;
    newnode->next = p;
    p->prev = newnode;
}

void printNode(Node*& head)
{
    Node* p = head;
    while (p != NULL)
    {
        cout<<p->num;
        p = p->next;
    }
}

Node* head = NULL;
Node* tail = NULL;

int main()
{
    newNode(5, head);
    printNode(head);
    return 0;
}

