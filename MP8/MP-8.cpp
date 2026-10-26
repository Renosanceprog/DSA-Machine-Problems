#include <iostream>
#include <stdio.h>

#define MAX 10

using namespace std;

class MySet
{
    private:
    int data[MAX];
    int ctr;

    int isMember(int x)
    {
        for (int i = 0; i < ctr; i++) if (data[i] == x) return i; 
        return -1;
    }
    public:
    MySet() { ctr = 0; }

    bool add(int x)
    {
        if (ctr == MAX) return false;
        if (isMember(x) == -1) 
        {
            data[ctr++] = x;
            return true;
        }
        return false;
    }

    bool remove(int x)
    {
        int idx = isMember(x);
        if (idx != -1)
        {
            for (int i = idx; i < ctr; i++) data[i] = data[i+1];
            ctr--;
            return true;
        }
        return false;
    }

    void displaySet()
    {
        cout<<"{";
        for (int i = 0; i < ctr; i++)
        {
            cout<<data[i];
            if (i != ctr-1) cout<<", ";
        }
        cout<<"}";
        cout<<" ctr = "<<ctr;
    }

    MySet setUnion(MySet b)
    {
        MySet c;
        for (int i = 0; i < ctr; i++) c.add(data[i]);
        for (int i = 0; i < b.ctr; i++) c.add(b.data[i]);
        return c;
    }
    MySet setIntersection(MySet b)
    {
        MySet c;
        for (int i = 0; i < ctr; i++) if (b.isMember(data[i]) != -1) c.add(data[i]);
        return c;
    }
    MySet setDifference(MySet b)
    {
        MySet c;
        for (int i = 0; i < ctr; i++) if (b.isMember(data[i]) == -1) c.add(data[i]);
        return c;
    }
};

int menu()
{
    int opt;
    printf("\033[H\033[2J");
    cout<<"=== Sir Rene's Set ADT Implementation Demo! ==="<<endl;
    cout<<"[1] Add Element"<<endl;
    cout<<"[2] Remove Element"<<endl;
    cout<<"[3] Display Set"<<endl;
    cout<<"[4] Union"<<endl;
    cout<<"[5] Intersection"<<endl;
    cout<<"[6] Difference"<<endl;
    cout<<"[0] Quit"<<endl;
    cout<<endl<<"Choose Option: ";
    cin>>opt;
    return opt;
}

int main(int argc, char const *argv[])
{
    MySet a;
    int x;
    while (true)
    {
        int choice = menu();
        switch (choice)
        {
        case 1:
            cout<<"enter int to insert: ";
            cin>>x;
            if (a.add(x)) printf("%d succesfully added in set.", x);
            else printf("failed to add %d. either set is full or already exists\n", x);
            break;
        case 2:
            cout<<"enter int to remove: ";
            cin>>x;
            if (a.remove(x)) printf("%d succesfully removed in set.", x);
            else printf("failed to remove %d. is not in set.\n", x);
            break;
        case 3:
            cout<<"===== Your Set ====="<<endl;
            a.displaySet();
            cout<<endl;
            break;
        case 4:
        case 5:
        case 6:
        {
            MySet b;
            while (true)
            {
                printf("\033[H\033[2J");
                if (choice == 4) cout<<"===== Create Set to Union ====="<<endl;
                if (choice == 5) cout<<"===== Create Set to Intersect ====="<<endl;
                if (choice == 6) cout<<"===== Create Set to Differentiate ====="<<endl;
                b.displaySet();
                cout<<endl<<"enter int (enter a duplicate to finish early): ";
                cin>>x;
                if (!b.add(x)) break;
            }
            if (choice == 4) a.setUnion(b).displaySet();
            if (choice == 5) a.setIntersection(b).displaySet();
            if (choice == 6) a.setDifference(b).displaySet();
            break;
        }
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