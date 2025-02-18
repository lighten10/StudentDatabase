#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

namespace Database {

    class Student {
    public:
        string name;
        int rollNumber;
        float marks;

        // Constructor
        Student(string n, int roll, float mark)
            : name(n), rollNumber(roll), marks(mark) {}

        // Display Method
        void display() const {
            cout << "Roll Number: " << rollNumber
                 << ", Name: " << name
                 << ", Marks: " << marks << endl;
        }

        // Convert Student Data to String
        string toString() const {
            return to_string(rollNumber) + "," + name + "," + to_string(marks);
        }

        // Operator Overloading for Comparison
        bool operator==(const Student& other) const {
            return this->rollNumber == other.rollNumber;
        }
    };

    class StudentDatabase {
    public:
        vector<shared_ptr<Student>> students;
        const string fileName = "students.txt";

        // Load from File
        void loadFromFile() {
            ifstream inFile(fileName);
            if (!inFile) {
                cerr << "No existing records found.\n";
                return;
            }
            string line;
            while (getline(inFile, line)) {
                stringstream ss(line);
                string name, rollStr, marksStr;
                getline(ss, rollStr, ',');
                getline(ss, name, ',');
                getline(ss, marksStr, ',');
                int roll = stoi(rollStr);
                float marks = stof(marksStr);
                students.push_back(make_shared<Student>(name, roll, marks));
            }
            inFile.close();
        }

        // Save to File
        void saveToFile() const {
            ofstream outFile(fileName);
            if (!outFile) {
                cerr << "Unable to open file for saving.\n";
                return;
            }
            for (const auto& student : students) {
                outFile << student->toString() << '\n';
            }
            outFile.close();
            cout << "Students saved to file successfully.\n";
        }

        // Add Student
        void addStudent(string name, int rollNumber, float marks) {
            students.push_back(make_shared<Student>(name, rollNumber, marks));
            cout << "Student added successfully.\n";
        }

        // Display All Students
        void displayAllStudents() {
            if (students.empty()) {
                cout << "No students in the database.\n";
                return;
            }
            for (const auto& student : students) {
                student->display();
            }
        }

        // Search Student
        void searchStudent(int roll) {
            for (const auto& student : students) {
                if (student->rollNumber == roll) {
                    cout << "Student Found:\n";
                    student->display();
                    return;
                }
            }
            cout << "Student Not Found.\n";
        }
    };
}

using namespace Database;

int main() {
    StudentDatabase db;
    db.loadFromFile();

    int choice;
    while (true) {
        cout << "\n===== Student Database Menu =====\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student by Roll Number\n";
        cout << "4. Save Students to File\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                string name;
                int rollNumber;
                float marks;
                cout << "Enter Student Name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter Roll Number: ";
                cin >> rollNumber;
                cout << "Enter Marks: ";
                cin >> marks;
                db.addStudent(name, rollNumber, marks);
                break;
            }
            case 2:
                db.displayAllStudents();
                break;
            case 3: {
                int rollNumber;
                cout << "Enter Roll Number to Search: ";
                cin >> rollNumber;
                db.searchStudent(rollNumber);
                break;
            }
            case 4:
                db.saveToFile();
                break;
            case 5:
                cout << "Exiting Program. Goodbye!\n";
                return 0;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
