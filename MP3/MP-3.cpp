#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#define MAX 10

using namespace std;

struct Student
{
    string n;
    int g1, g2, g3;
    Student *next, *prev;
    Student(string name, int grade1, int grade2, int grade3)
    {
        n = name;
        g1 = grade1;
        g2 = grade2;
        g3 = grade3;
        next = NULL;
        prev = NULL;
    }
};

class StudentRecord
{
    private:
    Student* head = NULL;
    Student* tail = NULL;
    int last = -1;

    bool isFull()
    {
        return last == MAX-1;
    }

    bool isEmpty()
    {
        return last == -1;
    }

    void locate(string name, Student* &p)
    {
        Student* walker = head;
        while (walker != NULL && walker->n != name) walker = walker->next;
        p = walker;
    }

    void loadFromFile()
    {
        ifstream file("databasecpp.csv");
        if (!file) return; 

        string n;
        int g1, g2, g3;
        char comma;
        Student* q = NULL;
        while (getline(file, n, ',')) {
            if (isFull()) break;
            
            file >> g1 >> comma >> g2 >> comma >> g3;
            file.ignore(10000, '\n');
            if (last == -1)
            {
                head = new Student(n, g1, g2, g3);
                q = head;
                tail = head;
            }
            else
            {
                q->next = new Student(n, g1, g2, g3);
                q->next->prev = q;
                q = q->next;
                tail = q;
            }
            last++;
        }
        file.close();
    }

    void saveToFile()
    {
        ofstream file("databasecpp.csv");
        if (!file) return;

        Student* walker = head;
        while (walker != NULL)
        {
            file << walker->n << ","
                 << walker->g1 << "," 
                 << walker->g2 << "," 
                 << walker->g3 << "\n";
            walker = walker->next;
        }
        file.close();
    }

    void enterInteger(int& g)
    {
        while (1)
        {
            cin >> g;
            if (cin.fail())
            {
                cin.clear();
                cin.ignore(10000, '\n'); 
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }

            if (g < 0 || g > 100)
            {
                cout << "Input value is out of range (0-100).\n";
                continue; 
            }
            break; 
        }
    }

    public:
    StudentRecord()
    {
        loadFromFile();
    }

    ~StudentRecord()
    {
        saveToFile();
        Student* walker = head;
        while (walker != NULL)
        {
            Student* temp = walker->next; 
            delete walker;                
            walker = temp;                
        }
    }

    void addStudent()
    {
        if (isFull())
        {
            cout << "Database is full!\n";
            system("pause");
            return;
        } 
        string name;
        int g1, g2, g3;
        
        cout << "Enter your Name: ";
        getline(cin >> ws, name);
        cout << "Enter grade in Science: ";
        enterInteger(g1);
        cout << "Enter grade in Math: ";
        enterInteger(g2);
        cout << "Enter grade in English: ";
        enterInteger(g3);

        Student* newnode = new Student(name, g1, g2, g3);

        if (head == NULL)
        {
            head = newnode;
            tail = newnode;
        }
        else
        {
            Student* walker = head;
            while (walker != NULL && walker->n < name) walker = walker->next;
            
            if (walker == head)
            {
                newnode->next = head;
                head->prev = newnode;
                head = newnode;
            } 
            else if (walker == NULL)
            {
                tail->next = newnode;
                newnode->prev = tail;
                tail = newnode;
            }
            else
            {
                newnode->next = walker;
                newnode->prev = walker->prev;
                walker->prev->next = newnode;
                walker->prev = newnode;
            }
        }
        last++;

        cout << "Student added successfully!\n";
        system("pause");
    }

    void deleteStudent(string name, bool silent = false)
    {
        if (isEmpty())
        {
            if (!silent) cout << "Nothing to delete.\n";
            if (!silent) system("pause");
            return;
        }

        Student *p;
        locate(name, p);
        if (p == NULL)
        {
            if (!silent) cout << "Not found.\n";
            if (!silent) system("pause");
            return;
        }
        
        if (p->prev != NULL) p->prev->next = p->next;
        else head = p->next;
        
        if (p->next != NULL) p->next->prev = p->prev;
        else tail = p->prev;
        
        delete p;
        last--;

        if (!silent) {
            cout << "Student deleted successfully!\n";
            system("pause");
        }
    }

    void updateStudent(string name)
    {
        if (isEmpty())
        {
            cout << "Nothing to update.\n";
            system("pause");
            return;
        }

        Student *p;
        locate(name, p);
        if (p == NULL)
        {
            cout << "Not found.\n";
            system("pause");
            return;
        }
        
        cout << "Enter new grade in Science: ";
        enterInteger(p->g1);
        cout << "Enter new grade in Math: ";
        enterInteger(p->g2);
        cout << "Enter new grade in English: ";
        enterInteger(p->g3);

        cout << "Student updated successfully!\n";
        system("pause");
    }

    void display()
    {
        system("cls");
        
        cout << setw(50) << right << "Sir Rene's Student Record" << "\n\n";
        
        cout << left << setw(5) << "No." 
             << setw(20) << "Name" 
             << setw(10) << "Science" 
             << setw(10) << "Math" 
             << setw(10) << "English" 
             << setw(10) << "Average" 
             << setw(10) << "Remarks" << "\n";
             
        cout << setfill('-') << setw(75) << "" << setfill(' ') << "\n";

        Student* walker = head;
        int i = 0;
        while (walker != NULL)
        {
            float avg = (walker->g1 + walker->g2 + walker->g3) / 3.0f;
            string remarks = (avg >= 75.0f) ? "Passed" : "Failed";
            
            cout << left << setw(5) << i + 1 
                 << setw(20) << walker->n 
                 << setw(10) << walker->g1 
                 << setw(10) << walker->g2 
                 << setw(10) << walker->g3 
                 << setw(10) << fixed << setprecision(2) << avg 
                 << setw(10) << remarks << "\n";
            walker = walker->next;
            i++;
        }
        
        cout << "\n";
        system("pause");
    }
};

int menu();

int main()
{
    StudentRecord db;
    string n;
    while (1)
    {
        switch (menu())
        {
            case 1: 
                system("cls"); 
                db.addStudent(); 
                break;
            case 2: 
                system("cls"); 
                cout << "Input Name to Update: "; 
                getline(cin >> ws, n); 
                db.updateStudent(n); 
                break;
            case 3: 
                system("cls"); 
                cout << "Input Name to Delete: "; 
                getline(cin >> ws, n); 
                db.deleteStudent(n); 
                break;
            case 4: 
                db.display(); 
                break;
            case 5: 
                return 0;
            default: 
                cout << "Invalid choice.\n"; 
                system("pause");
        }
    }
    return 0;
}

int menu()
{
    int op;
    system("cls");
    cout << "MENU\n";
    cout << "1. Add Record\n";
    cout << "2. Update Record\n";
    cout << "3. Delete Record\n";
    cout << "4. Display\n";
    cout << "5. Exit\n";
    cout << "\nSelect(1-5): ";
    cin >> op;
    if (cin.fail())
    {
        cin.clear();
        cin.ignore(10000, '\n');
        return -1;
    }
    return op;
}