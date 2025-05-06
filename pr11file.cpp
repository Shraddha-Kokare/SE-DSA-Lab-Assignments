#include<iostream>
#include<fstream>
#include<string>
using namespace std;

class Student
{
    public:
        int rollNumber;
        string name;
        string division;
        string address;

        void getDetails()
        {
            cout<<"\nEnter Roll Number: ";
            cin>>rollNumber;
            cout<<"Enter Name:";
            cin>>name;
            cout<<"Enter Division:";
            cin>>division;
            cout<<"Enter address:";
            cin>>address;
        }

        void display()
        {
            cout<<"\n\n\t\tStudent details\n";
            cout<<"\n\t\t"<<rollNumber;
            cout<<"\n\t\t"<<name;
            cout<<"\n\t\t"<<division;
            cout<<"\n\t\t"<<address;
        }
};

class FileHandling
{
    public:
        void addStudent()
        {
            Student newStudent;
            newStudent.getDetails();

            ofstream out("Students.txt",ios::app);

            if(!out)
            {
                cout<<"\nError in opening the file !!";
                return;
            }
            out<<newStudent.rollNumber<<endl;
            out<<newStudent.name<<endl;
            out<<newStudent.division<<endl;
            out<<newStudent.address<<endl;

            out.close();

            cout<<"\nStudent record added successfully !";
        }

        void deleteStudent()
        {
            ifstream inFile("Students.txt");
            ofstream outFile("temp.txt");
            int rno;

            if(!inFile || !outFile)
            {
                cout<<"\nError opening the file !";
                return;
            }

            cout<<"\nEnter roll no to delete record:";
            cin>>rno;

            Student student;

            bool found=false;

            while(inFile>>student.rollNumber)
            {
                inFile.ignore();
                getline(inFile,student.name);
                getline(inFile,student.division);
                getline(inFile,student.address);

                if(student.rollNumber==rno)
                {
                    found=true;
                    cout<<"\nDeleted record:";
                    student.display();
                }
                else{
                    outFile<<student.rollNumber<<endl;
                    outFile<<student.name<<endl;
                    outFile<<student.division<<endl;
                    outFile<<student.address<<endl;
                }
            }

            inFile.close();
            outFile.close();

            remove("Students.txt");
            rename("temp.txt","Students.txt");

            if(!found)
            {
                cout<<"\nNo record found";
            }
        }

        void displayStudents()
        {
            int rno;
            ifstream in("Students.txt");
            if(!in)
            {
                cout<<"\nError opening the file !";
                return;
            }

            cout<<"\nEnter roll number: ";
            cin>>rno;
            
            int readRoll;
            bool found=false;
            Student student;
            while(in>>student.rollNumber)
            {
                in.ignore();
                getline(in,student.name);
                getline(in,student.division);
                getline(in,student.address);
                if(student.rollNumber==rno)
                {
                    student.display();
                    found=true;
                    break;
                }
            }
            in.close();
            if(!found)
            {
                cout<<"\nNo record found !";
            }
        }
};


int main()
{
    int choice,rno;
    FileHandling file;
    do
    {
        cout<<"\n1. Add Student\n2. Delete Student\n3. Display Student\n4. Exit\nEnter your choice:";
        cin>>choice;

        switch (choice)
        {
        case 1:
            file.addStudent();
            break;

        case 2:
            file.deleteStudent();
            // cout<<"\nEnter roll no. to delete:";
            // cin>>rno;
            // deleteStudent(rno);
            break;
        
        case 3:
            // cout<<"\nEnter roll no. to display:";
            // cin>>rno;
            file.displayStudents();
            // displayStudent(rno);
            break;

        case 4:
            cout<<"\nThank You...";
            break;
        
        default:
            break;
        }
    } while (choice!=4);
    
    return 0;
}