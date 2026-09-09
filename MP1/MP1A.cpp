#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <sstream>
#define MAX 5
using namespace std;

struct Student{ //groups multiple record into one
	string name;
	int q1, q2, q3;
	float ave;
	
	Student() { //default constructor
		name = "";
		q1 = 0; q2 = 0; q3 = 0;
		ave = 0;
	}
	Student(string n, int x1, int x2, int x3) { //parameterized constructor
		name = n;
		q1 = x1;
		q2 = x2;
		q3 = x3;
	}
};

class ClassRec {
	private:
		Student stu[MAX];
		int last = -1;
		bool isfull() {return last==MAX-1;}
		bool isempty() {return last==-1;}
	
	public:
		void addRec(Student data) {
			if (isfull() == 1) {
				cout << "Record is full!" << endl; return;
			} else {
				// name sorting
					int position = 0;
					while(position <= last && stu[position].name < data.name) {
						position++;
					}
				for(int i = last; i>=position; i--){
					stu[i+1] = stu[i]; 
				}
				stu[position] = data;
				last++;
			}
		}

		void delRec(string n) {
			int i,p;
			system("cls");
			
			p = locate(n);

			if (p==-1) {
				cout << "Name does not exist!" << endl;
				system("pause"); return;
			} else {
				for (i=p;i<last;i++){
					stu[i] = stu[i+1];
				}
			}
			last--;
			cout<<n<<" was deleted from the record"<<endl;
			system("pause");
		}
		void editRec(string y) {
			int p,i, choice = 0;
			system("cls");
			
			p = locate(y);
			
			if (p==-1) {
				cout<<"Name does not exist!\n";
				system("pause"); return;
			}
			else {
				int score;
				
			while(true) {
			float ave = (stu[p].q1+stu[p].q2+stu[p].q3)/3.00; //always put inside the while loop
			system("cls");
			cout<<"Record of "<<y<<endl;
			cout<<"NAME"<<"\t"<<"QUIZ 1"<<"\t"<<"QUIZ 2"<<"\t"<<"QUIZ 3"<<"\t"<<"AVERAGE"<<endl;
			// cout << indention << set width << "string"/variable
			cout<<stu[p].name<<"\t"<<stu[p].q1<<"\t"<<stu[p].q2<<"\t"<<stu[p].q3<<"\t"<<ave<<endl;
			cout<<"\nChoose quiz to update:\n1. Quiz 1\n2. Quiz 2\n3. Quiz 3\n4. Return to menu";
			cout<<"\nChoose from 1-4: ";
			cin>>choice;
			
			switch(choice) {
				case 1: cout<<"Enter new score: "; cin>>score;
						stu[p].q1 = score;
						cout<<"Saved!";
						system("pause"); break;
				case 2: cout<<"Enter new score: "; cin>>score;
						stu[p].q2 = score;
						cout<<"Saved!";
						system("pause"); break;
				case 3: cout<<"Enter new score: "; cin>>score;
						stu[p].q3 = score;
						cout<<"Saved!";
						system("pause"); break;
				case 4: return; break;
				default: cout<<"\nInvalid Choice!\n";
						system("pause"); break;
			}
			}
		}	
		}
		
		void display() {
			int i;
			system("cls");
						
			if (isempty() == 1) {
				cout << "No record exists!" << endl; system("pause"); return;
			}
			cout << "\t  *********STUDENT RECORD*********" << endl;
			cout << left << setw(15) << "NAME"<< setw(10) <<"QUIZ 1"<< setw(10) <<"QUIZ 2"<< setw(10) <<"QUIZ 3"<< setw(10) <<"AVERAGE"<< setw(10) <<"REMARKS"<<endl;
			
			for(i=0;i<=last;i++){
				float ave = (stu[i].q1+stu[i].q2+stu[i].q3)/3.00;
				cout<< left << setw(15) << stu[i].name<< setw(10) <<
				stu[i].q1<< setw(10) <<stu[i].q2<< setw(10) <<stu[i].q3<< setw(10) <<
				fixed << setprecision(2) <<ave<< setw(10) <<(ave >= 75? "Passed" : "Failed") << endl;
			}
			cout << "\n";
			system("pause");
		}
		
		int locate (string n) {
			int i;
			for (i=0;i<=last;i++){
				if(stu[i].name == n) {return i;} //student found, return index
			} return -1; //not found
		}
		
		int menu(){
			int ch;
			system("cls");
			cout << "*********WELCOME TO STUDENT RECORD*********" << endl;
			cout << "[1] Add Record\n[2] Edit Record\n[3] Delete Record\n[4] Display Record\n[5] Exit" << endl;
			cout << "\nChoose from 1-5 only: " << endl;
			cin >> ch;
			cin.ignore();
			return ch;
		}
		
		void saveFile() {
			int i;
			ofstream fp("Records.csv");
			if (fp.fail()) {
				cout << "File error" << endl; return;
			}
			else {
				for (i=0;i<=last;i++) {
					fp << stu[i].name << "," << stu[i].q1 << "," << stu[i].q2 << "," << stu[i].q3 << endl;
				}
				fp.close();
			}
		}
		
		void retrieve() {
			ifstream fp("Records.csv");
			if (fp.fail()) {
				cout << "File error" << endl; return;
			}
			string line;
			while (getline(fp, line)){
				stringstream ss(line);
				string name, x1, x2, x3;
				int q1, q2, q3;
				if (getline(ss, name, ',') &&  getline(ss, x1, ',') && getline(ss, x2, ',') && getline(ss, x3, ',')) {
					stringstream(x1) >> q1; //alternative for stoi
					stringstream(x2) >> q2;
					stringstream(x3) >> q3;
					/* 
					q1 = stoi(x1);
					q2 = stoi(x2);
					q3 = stoi(x3);
					*/
					if (!name.empty()) {
						addRec(Student(name, q1, q2, q3));
					}
				}
			}
			fp.close();
		}
};

int main() {
	Student stu; //student record
	ClassRec recs; //accessing function
	recs.retrieve();
	
	while(true){
		switch(recs.menu()) {
			case 1: cout << "Enter a name: "; getline(cin, stu.name);
			if (recs.locate(stu.name)>-1){
				cout << "Error Duplicate!";
				system("pause");
			}
			else {
				cout << "Enter quiz 1 score: "; cin>>stu.q1;
				cout << "Enter quiz 2 score: "; cin>>stu.q2;
				cout << "Enter quiz 3 score: "; cin>>stu.q3;
				cin.ignore();
				recs.addRec(stu); recs.saveFile();
				cout << "Recorded!\n"; system("pause");
			} 
			break;
			case 2: cout << "Enter a name:"; getline(cin, stu.name);
					recs.editRec(stu.name); recs.saveFile(); break;
			case 3: cout << "Enter a name: "; getline(cin, stu.name);
					recs.delRec(stu.name); recs.saveFile(); break;
			case 4: recs.display(); break;
			case 5: cout<<"Thank you for using this program.\n"; system("pause"); exit(0); break;
			default: cout<<"Choose only from 1-5!\n"; system("pause"); cin.ignore(); 
		}
	}
}
