#include <iostream>
#include <stdio.h>

using namespace std;

class Tree{
    private:
    class tNode;

//===== doubly ll impl for BFT =======================================
    class doublyLL{
        public:
        struct Node
        {
            tNode *child;
            Node* prev;
            Node* next;
            Node(tNode *ptr)
            {
                child = ptr;
                prev = NULL;
                next = NULL;
            }
        };

        Node* head;
        Node* last;

        
        doublyLL()
        {
            head = NULL;
        }

        void newNode(tNode *ptr)
        {
            if (head == NULL)
            {
                head = new Node(ptr);
                last = head;
            }
            else
            {
                last->next = new Node(ptr);
                last->next->prev = last;
                last = last->next;
            }
        }
    };
//===== tree node unit ===============================================
    struct tNode
    {
        int data;
        doublyLL *children;
        tNode(int num)
        {
            data = num;
            children = new doublyLL();
        }
    };
//===== queue impl for BFT ===========================================
    class Queue{
        private:
        struct qNode
        {
            tNode *data;
            qNode *next;
            qNode(tNode *node)
            {
                data = node;
                next = NULL;
            }
        };
        
        
        qNode *f, *r;
        int ctr;
        
        public:
        bool isEmpty(){return ctr == 0;}
        Queue()
        {
            f = NULL;
            r = NULL;
            ctr = 0;
        }

        void enqueue(tNode *data)
        {
            qNode *newnode = new qNode(data);

            if (isEmpty()) f = r = newnode;
            else
            {
                r->next = newnode;
                r = newnode;
            }

            ctr++;
        }

        tNode *dequeue()
        {
            if (isEmpty()) return NULL;
            
            tNode *val = f->data;
            qNode *del = f;

            if (f == r) f = r = NULL;
            else f = f->next;

            delete del;
            ctr--;
            return val;
        }
    };

//===== Helper Functions =========================================
    void addNode(tNode *&p)
    {
        int num;
        if (p == NULL)
        {
            cout<<"enter root value (-1 to return): ";
            cin>>num;
            p = new tNode(num);
            addNode(p);
            return;
        }
        while (true)
        {
            printf("enter %d's child value (-1 to move to next child): ", p->data);
            cin>>num;
            if (num == -1) break;
            tNode *newnode = new tNode(num);
            p->children->newNode(newnode);
            addNode(newnode);
        }
    }
    void preOrder(tNode *p)
    {
        if (p == NULL) return;
        cout<<p->data<<" -> ";
        doublyLL::Node *q = p->children->head;
        while (q != NULL)
        {
            preOrder(q->child);
            q = q->next;
        }
    }
    void postOrder(tNode *p)
    {
        if (p == NULL) return;
        doublyLL::Node *q = p->children->head;
        while (q != NULL)
        {
            preOrder(q->child);
            q = q->next;
        }
        cout<<p->data<<" -> ";
    }
//===== BTree variable ===========================================
    tNode *root;

    public:

    Tree() { root = NULL; }

    void BuildTree()
    {
        addNode(root);
    }
    void printPreOrder()
    {
        preOrder(root);
        cout<<"\e[4D    ";
    }
    void printPostOrder()
    {
        postOrder(root);
        cout<<"\e[4D    ";
    }
    void printLevelOrder()
    {
        Queue q;
        
        if (root != NULL) q.enqueue(root);
        else return;
        while (!q.isEmpty())
        {
            tNode *p = q.dequeue();
            cout<<p->data<<" -> ";
            doublyLL::Node *ql = p->children->head;
            while (ql != NULL)
            {
                q.enqueue(ql->child);
                ql = ql->next;
            }
        }
        cout<<"\e[4D    ";
    }
};

int menu()
{
    int opt;
    printf("\033[H\033[2J");
    cout<<"=== Sir Rene's Simple Binary Tree Implementation Demo! ==="<<endl;
    cout<<"- Display Trees -"<<endl;
    cout<<"    [1] PREORDER"<<endl;
    cout<<"    [2] POSTORDER"<<endl;
    cout<<"    [3] LEVELORDER"<<endl<<endl;
    cout<<"[4] Create Simple Binary Tree"<<endl;
    cout<<"[0] Quit"<<endl;
    cout<<endl<<"Choose Option: ";
    cin>>opt;
    return opt;
}

int main(int argc, char const *argv[])
{
    Tree tree;
    while (true)
    {
        switch (menu())
        {
        case 1:
            cout<<"Tree Traversal using In Order: \n";
            tree.printPreOrder();
            break;
        case 2:
            cout<<"Tree Traversal using In Order: \n";
            tree.printPostOrder();
            break;
        case 3:
            cout<<"Tree Traversal using In Order: \n";
            tree.printLevelOrder();
            break;
        case 4:
            tree.BuildTree();
            break;
        case 0:
            goto exit_menu;
            break;
        default:
            break;
        }
        cout<<"\n[Press Enter to Continue]";
        cin.ignore();
        cin.get();
    }
    exit_menu:
    return 0;
}
