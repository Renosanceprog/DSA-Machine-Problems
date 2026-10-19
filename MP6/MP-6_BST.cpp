#include <iostream>
#include <stdio.h>

using namespace std;

class BTree{
    private:
//===== tree node unit ===============================================
    struct tNode
    {
        int data;
        tNode *left;
        tNode *right;
        tNode(int num)
        {
            data = num;
            left = NULL;
            right = NULL;
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
    void addNode()
    {
        int num;
        while (true)
        {
            cout<<"enter root value (-1 to return): ";
            cin>>num;
            if (num == -1) return;
            tNode *newnode = new tNode(num);
            if (root == NULL){ root = newnode; continue;}
            tNode *p = root;
            while (true)
            {
                cout<<p->data<<endl;
                if (p->data > num)
                {
                    if (p->left == NULL) {p->left = newnode; break;}
                    p = p->left;
                    cout<<p->data<<endl;
                }
                else
                {
                    if (p->right == NULL) {p->right = newnode; break;}
                    p = p->right;
                    cout<<p->data<<endl;
                }
            }
        }
    }
    void inOrder(tNode *p)
    {
        if (p == NULL) return;
        inOrder(p->left);
        cout<<p->data<<" -> ";
        inOrder(p->right);
    }
    void preOrder(tNode *p)
    {
        if (p == NULL) return;
        cout<<p->data<<" -> ";
        preOrder(p->left);
        preOrder(p->right);
    }
    void postOrder(tNode *p)
    {
        if (p == NULL) return;
        postOrder(p->left);
        postOrder(p->right);
        cout<<p->data<<" -> ";
    }
//===== BTree variable ===========================================
    tNode *root;

    public:

    BTree() { root = NULL; }

    void BuildTree()
    {
        addNode();
    }
    void printInOrder()
    {
        inOrder(root);
        cout<<"\e[4D    ";
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
            if (p->left  != NULL) q.enqueue(p->left);
            if (p->right != NULL) q.enqueue(p->right);
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
    cout<<"    [1] INORDER"<<endl;
    cout<<"    [2] PREORDER"<<endl;
    cout<<"    [3] POSTORDER"<<endl;
    cout<<"    [4] LEVELORDER"<<endl<<endl;
    cout<<"[5] Create Simple Binary Tree"<<endl;
    cout<<"[0] Quit"<<endl;
    cout<<endl<<"Choose Option: ";
    cin>>opt;
    return opt;
}

int main(int argc, char const *argv[])
{
    BTree tree;
    while (true)
    {
        switch (menu())
        {
        case 1:
            cout<<"Tree Traversal using In Order: \n";
            tree.printInOrder();
            break;
        case 2:
            cout<<"Tree Traversal using In Order: \n";
            tree.printPreOrder();
            break;
        case 3:
            cout<<"Tree Traversal using In Order: \n";
            tree.printPostOrder();
            break;
        case 4:
            cout<<"Tree Traversal using In Order: \n";
            tree.printLevelOrder();
            break;
        case 5:
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

