#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#define MAX 10

using namespace std;

//GLOBAL
struct Student
{
    string n;
    int g1, g2, g3;
    Student(string name, int grade1, int grade2, int grade3)
    {
        n = name;
        g1 = grade1;
        g2 = grade2;
        g3 = grade3;
    }
};

class StudentRecord
{
    private:
    Student* students[MAX] = {0};
    int last = -1;

    bool isFull()
    {
        return last == MAX-1;
    }

    bool isEmpty()
    {
        return last == -1;
    }

    int locate(string name)
    {
        for (int i = 0; i <= last; i++) {
            if (students[i]->n == name) return i;
        }
        return -1;
    }

    void loadFromFile()
    {
        ifstream file("databasecpp.csv");
        if (!file) return; 

        string n;
        int g1, g2, g3;
        char comma;
        
        while (getline(file, n, ',')) {
            if (isFull()) break;
            
            file >> g1 >> comma >> g2 >> comma >> g3;
            file.ignore(10000, '\n');
            
            int i;
            for (i = last; i >= 0; i--) {
                if (students[i]->n > n) {
                    students[i + 1] = students[i];
                } else {
                    break;
                }
            }
            students[i + 1] = new Student(n, g1, g2, g3);
            last++;
        }
        file.close();
    }

    void saveToFile()
    {
        ofstream file("databasecpp.csv");
        if (!file) return;

        for (int i = 0; i <= last; i++) {
            file << students[i]->n << ","
                 << students[i]->g1 << "," 
                 << students[i]->g2 << "," 
                 << students[i]->g3 << "\n";
        }
        file.close();
    }

    void enterInteger(int& g){
        while (1) {
            cin >> g;
            if (cin.fail()) {
                cin.clear();
                cin.ignore(10000, '\n'); 
                cout << "Invalid input! Please enter a number.\n";
                continue;
            }

            if (g < 0 || g > 100) {
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
        for (int i = 0; i <= last; i++) {
            delete students[i];
        }
    }

    void addStudent()
    {
        if (isFull()){
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
        
        int i;
        for (i = last; i >= 0; i--) {
            if (students[i]->n > name) {
                students[i + 1] = students[i];
            } else {
                break;
            }
        }
        students[i + 1] = new Student(name, g1, g2, g3);
        last++;
        
        cout << "Student added successfully!\n";
        system("pause");
    }

    void deleteStudent(string name, bool silent = false)
    {
        if (isEmpty()) {
            if (!silent) cout << "Nothing to delete.\n";
            if (!silent) system("pause");
            return;
        }

        int p = locate(name);
        if (p < 0) {
            if (!silent) cout << "Not found.\n";
            if (!silent) system("pause");
            return;
        }

        delete students[p];
        for (int i = p; i < last; i++) {
            students[i] = students[i + 1];
        }
        students[last] = 0;
        last--;

        if (!silent) {
            cout << "Student deleted successfully!\n";
            system("pause");
        }
    }

    void updateStudent(string name)
    {
        if (isEmpty()) {
            cout << "Nothing to update.\n";
            system("pause");
            return;
        }

        int p = locate(name);
        if (p < 0) {
            cout << "Not found.\n";
            system("pause");
            return;
        }

        int g1, g2, g3;
        cout << "Enter new grade in Science: ";
        enterInteger(g1);
        cout << "Enter new grade in Math: ";
        enterInteger(g2);
        cout << "Enter new grade in English: ";
        enterInteger(g3);

        deleteStudent(name, true);

        int i;
        for (i = last; i >= 0; i--) {
            if (students[i]->n > name) {
                students[i + 1] = students[i];
            } else {
                break;
            }
        }
        students[i + 1] = new Student(name, g1, g2, g3);
        last++;
        
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

        for (int i = 0; i <= last; i++) {
            float avg = (students[i]->g1 + students[i]->g2 + students[i]->g3) / 3.0f;
            string remarks = (avg >= 75.0f) ? "Passed" : "Failed";
            
            cout << left << setw(5) << i + 1 
                 << setw(20) << students[i]->n 
                 << setw(10) << students[i]->g1 
                 << setw(10) << students[i]->g2 
                 << setw(10) << students[i]->g3 
                 << setw(10) << fixed << setprecision(2) << avg 
                 << setw(10) << remarks << "\n";
        }
        
        cout << "\n";
        system("pause");
    }
};

//UDFs
int menu();

int main()
{
    StudentRecord db;
    string n;
    while (1) {
        switch (menu()) {
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
    if (cin.fail()) {
        cin.clear();
        cin.ignore(10000, '\n');
        return -1;
    }
    return op;
}