#include<iostream>
#include<fstream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

namespace Database{

    class Student {
        private : 
        string name;
        int rollNumber;
        float marks ;

        Student(string n , int roll , float mark) : name(n) , rollNumber(roll) , marks(mark) {} // new way of declaring consturctor ;

        //display method 
        // declaring const 
        void display() const {
            cout<<"Roll Number :"<<rollNumber
               <<"name :"<<name
               <<"marks : "<<marks<<endl; 
            }

        //== operator overloading to compare student
        bool operator==(const Student& other) const{
            return  this->rollNumber = other.rollNumber ; 
        }

        string toString() const{
            return to_string(this->rollNumber) + "," + this->name  + ", " + to_string(this->marks);
        }

    };

    class StudentDatabase {
        private :
        vector<shared_ptr<Student>> students;
        const string fileName = "student.txt";
        
        void loadFromFile(){
            ifstream inFile(fileName);
            if (!inFile) return ;
            string line;
            while(getline(inFile , line)){
                stringstream ss(line);
                string name , rollStr , marksStr;
                getline(ss,rollStr , ',');
                getline(ss,name,',');
                getline(ss,marksStr,',');
                int roll = stoi(rollStr);
                int marks = stoi(marksStr);
                students.push_back(make_shared<Student>(name,roll,marks));
            }
            inFile.close();

        }

        void saveToFile() const {
            ofstream outFile(fileName);
            if(!outFile) {
                cerr<<"unable to open up the file "<<endl;
                return ;
            }
            for(const auto& student : students){
                outFile << student->toString() << '\n' ; 
            }
            outFile.close();
            cout<<"students added to File successfully";
        }

        void addStudent(string name , int rollNumber , float marks){
            students.push_back(make_shared<Student>(name,rollNumber,marks));
            cout<<"Student added successfully";
        }

        void displayAllStudents(){
            if(!students.empty()){
                for(const auto& student : students ){
                    student->display();
                }
            }
            return ;
        }

        void searchStudent(int roll){
            for(const auto& student : students){
                if(student->rollNumber == roll){
                    cout<<"Student Found"<<endl;
                    return ;
                }
            }
            cout<<"Student Not Found"<<endl;

        }
        



    };


    };


