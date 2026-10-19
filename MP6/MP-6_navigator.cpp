#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

class BTree{
    private:
//===== tree node unit ===============================================
    struct tNode
    {
        int data;
        tNode *root;
        tNode *left;
        tNode *right;
        tNode(int num)
        {
            data = num;
            root = NULL;
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
        // Start at the actual tree root if it exists, otherwise NULL
        tNode *cur = root; 
        int opt;
        
        while (true)
        {
            printf("\033[H\033[2J"); // Clear screen
            cout << "=== Tree Navigation ===" << endl;
            
            // 1. FIXED: Safely check if cur is NULL before checking its branches
            string cn = (cur == NULL) ? "NULL" : to_string(cur->data);
            string rn = (cur == NULL || cur->root == NULL) ? "NULL" : to_string(cur->root->data);
            string lc = (cur == NULL || cur->left == NULL) ? "NULL" : to_string(cur->left->data);
            string rc = (cur == NULL || cur->right == NULL) ? "NULL" : to_string(cur->right->data);
            
            // 2. FIXED: Replaced printf with cout to avoid std::string segfaults
            cout << "Current Node: " << cn << ", Parent Node: " << rn 
                 << ", Left child: " << lc << ", Right child: " << rc << endl;
                 
            cout << "[1] Insert/Edit data" << endl;
            cout << "[2] Go to Parent" << endl;
            cout << "[3] Go to Left" << endl;
            cout << "[4] Go to Right" << endl;
            cout << "[0] Quit" << endl;
            cout << endl << "Choose Option: ";
            cin >> opt;
            
            switch (opt)
            {
            case 1:
            {   // Scope brackets added to safely declare variables inside a switch case
                int opt2;
                int val; // 3. FIXED: Using a separate variable so we don't overwrite 'opt'
                
                cout << "enter value: ";
                cin >> val;
                cout << "enter which node to edit: " << endl;
                cout << "[1] root (current node)" << endl;
                cout << "[2] left" << endl;
                cout << "[3] right" << endl;
                cin >> opt2;
                
                switch (opt2)
                {
                case 1:
                    if (cur == NULL) {
                        root = new tNode(val); // Initialize the main tree root
                        cur = root;            // Move our cursor to it
                    }
                    else cur->data = val;      // Edit existing
                    break;
                case 2:
                    if (cur != NULL) { // Must be on a node to add a child
                        if (cur->left == NULL) {
                            cur->left = new tNode(val);   // 4. FIXED: Assign to cur->left, not cur
                            cur->left->root = cur;        // Link parent pointer backwards
                        }
                        else cur->left->data = val;
                    }
                    break;
                case 3:
                    if (cur != NULL) {
                        if (cur->right == NULL) {
                            cur->right = new tNode(val);
                            cur->right->root = cur;       // Link parent pointer backwards
                        }
                        else cur->right->data = val;
                    }
                    break;
                default:
                    break;
                }
                break;
            }
            case 2:
                // Safely check both the current node and parent before moving
                if (cur != NULL && cur->root != NULL) cur = cur->root; 
                break;
            case 3:
                if (cur != NULL && cur->left != NULL) cur = cur->left;
                break;
            case 4:
                if (cur != NULL && cur->right != NULL) cur = cur->right;
                break;
            case 0:
                return; // 5. FIXED: A simple return avoids needing a goto label
            default:
                break;
            }
        }
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

