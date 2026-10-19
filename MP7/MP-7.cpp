#include <iostream>
#include <stdio.h>

#define SIZE 10

using namespace std;

class lList
{
    private:
    struct node
    {
        int key;
        node *next;
        node(int k)
        {
            key = k;
            next = NULL;
        }
    };

    node *head;
    node *last;

    public:
    lList()
    {
        head = NULL;
        last = NULL;
    }
    void insert(int k)
    {
        node *target = new node(k);
        if (head == NULL) head = target;
        else last->next = target;
        last = target;
    }

    int locate(int k, node* &p, node* &q)
    {
        int i = 0;
        node *p1 = head;
        node *p2 = NULL;
        while (p1 != NULL && p1->key != k)
        {
            p2 = p1;
            p1 = p1->next;
            i++;
        }

        p = p1;
        q = p2;
        return i;
    }

    bool remove(int k)
    {
        if (head == NULL) return false;

        node *p = head;
        node *q = NULL;

        locate(k,p,q);
        if (p == NULL) return false;
        if (q == NULL) head = head->next;
        else q->next = p->next;

        delete p;
        return true;
    }

    int search(int k)
    {
        if (head == NULL) return -1;

        node *p = head;
        node *q = NULL;

        int i = locate(k,p,q);

        if (p == NULL) return -1;
        else return i;
    }

    void display()
    {
        node *p = head;

        while (p != NULL)
        {
            cout<<p->key;
            if (p->next != NULL) cout<<" -> ";
            p = p->next;
        }
    }
};

class intMap
{
    private:
    lList map[SIZE];
    
    int hashFunction(int k)
    {
        return k % SIZE;
    }
    public:
    int ctr;
    intMap(){ ctr = 0; }

    void insertKey(int k)
    {
        int index = hashFunction(k);
        map[index].insert(k);
        ctr++;
        
        printf("%d has been added to the map.\n", k);
    }

    void searchKey(int k)
    {
        int x = hashFunction(k);
        int y = map[x].search(k);

        if (y == -1) printf("%d is not found at map[%d].\n", k, x);
        else printf("%d is found at map[%d] as node #%d.\n", k, x, y+1);
    }

    void deleteKey(int k)
    {
        int index = hashFunction(k);
        if (map[index].remove(k)) { printf("%d has been removed from the map.\n", k); ctr--; }
        else printf("%d has not been removed from the map. may not existed or already deleted.\n", k);
    }

    void display()
    {
        for (size_t i = 0; i < SIZE; i++)
        {
            printf("[%d]: ", i);
            map[i].display();
            cout<<endl;
        }
    }
};

int menu()
{
    int opt;
    printf("\033[H\033[2J");
    cout<<"=== Sir Rene's Map ADT Implementation Demo! ==="<<endl;
    cout<<"[1] Insert Key"<<endl;
    cout<<"[2] Search Key"<<endl;
    cout<<"[3] Delete Key"<<endl;
    cout<<"[4] Display Table"<<endl;
    cout<<"[0] Quit"<<endl;
    cout<<endl<<"Choose Option: ";
    cin>>opt;
    return opt;
}

int main(int argc, char const *argv[])
{
    intMap m = intMap();
    int x;
    while (true)
    {
        switch (menu())
        {
        case 1:
            cout<<"enter key to insert: ";
            cin>>x;
            m.insertKey(x);
            break;
        case 2:
            cout<<"enter key to search: ";
            cin>>x;
            m.searchKey(x);
            break;
        case 3:
            cout<<"enter key to delete: ";
            cin>>x;
            m.deleteKey(x);
            break;
        case 4:
            printf("- Map Structure | Current Items: %d -\n", m.ctr);
            m.display();
            break;
        case 0: goto exit_menu;
        default:
            cout<<"Invalid input Try Again..."<<endl;
            break;
        }

        cin.ignore();
        cin.get();
    }
    exit_menu:
    return 0;
}
