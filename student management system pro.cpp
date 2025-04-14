#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <limits>
#include <iomanip>

using namespace std;

class Student {
private:
    string id;
    string name;
    int age;
    string grade;
    string contact;

public:
    // Constructor
    Student(string id = "", string name = "", int age = 0, string grade = "", string contact = "")
        : id(id), name(name), age(age), grade(grade), contact(contact) {}

    // Getters
    string getId() const { return id; }
    string getName() const { return name; }
    int getAge() const { return age; }
    string getGrade() const { return grade; }
    string getContact() const { return contact; }

    // Setters
    void setId(string id) { this->id = id; }
    void setName(string name) { this->name = name; }
    void setAge(int age) { this->age = age; }
    void setGrade(string grade) { this->grade = grade; }
    void setContact(string contact) { this->contact = contact; }

    // Display student info
    void display() const {
        cout << left << setw(10) << id 
             << setw(25) << name 
             << setw(8) << age 
             << setw(10) << grade 
             << setw(15) << contact << endl;
    }

    // For file operations - modified to avoid ambiguity
    void saveToFile(ofstream& ofs) const {
        ofs << id << endl;
        ofs << name << endl;
        ofs << age << endl;
        ofs << grade << endl;
        ofs << contact << endl;
    }

    void loadFromFile(ifstream& ifs) {
        getline(ifs, id);
        getline(ifs, name);
        ifs >> age;
        ifs.ignore(); // To ignore the newline character after age
        getline(ifs, grade);
        getline(ifs, contact);
    }
};

class StudentManager {
private:
    vector<Student> students;
    string filename = "students.txt";

    void loadFromFile() {
        ifstream ifs(filename);
        if (!ifs) {
            return; // File doesn't exist yet
        }

        while (!ifs.eof()) {
            Student student;
            student.loadFromFile(ifs);
            if (!student.getId().empty()) { // Check if we read valid data
                students.push_back(student);
            }
        }
        ifs.close();
    }

    void saveToFile() {
        ofstream ofs(filename);
        if (!ofs) {
            cerr << "Error opening file for writing!" << endl;
            return;
        }

        for (const auto& student : students) {
            student.saveToFile(ofs);
        }
        ofs.close();
    }

public:
    StudentManager() {
        loadFromFile();
    }

    ~StudentManager() {
        saveToFile();
    }

    void addStudent() {
        string id, name, grade, contact;
        int age;

        cout << "\nEnter Student ID: ";
        getline(cin, id);

        // Check if ID already exists
        for (const auto& student : students) {
            if (student.getId() == id) {
                cout << "Student with this ID already exists!" << endl;
                return;
            }
        }

        cout << "Enter Student Name: ";
        getline(cin, name);

        cout << "Enter Student Age: ";
        while (!(cin >> age) || age <= 0) {
            cout << "Invalid age. Please enter a positive number: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        cin.ignore(); // Clear the newline character

        cout << "Enter Student Grade: ";
        getline(cin, grade);

        cout << "Enter Contact Information: ";
        getline(cin, contact);

        students.emplace_back(id, name, age, grade, contact);
        cout << "Student added successfully!" << endl;
    }

    void viewAllStudents() {
        if (students.empty()) {
            cout << "\nNo students found in the system." << endl;
            return;
        }

        cout << "\n" << string(80, '-') << endl;
        cout << left << setw(10) << "ID" 
             << setw(25) << "Name" 
             << setw(8) << "Age" 
             << setw(10) << "Grade" 
             << setw(15) << "Contact" << endl;
        cout << string(80, '-') << endl;

        for (const auto& student : students) {
            student.display();
        }
        cout << string(80, '-') << endl;
    }

    void searchStudent() {
        string id;
        cout << "\nEnter Student ID to search: ";
        getline(cin, id);

        for (const auto& student : students) {
            if (student.getId() == id) {
                cout << "\nStudent Found:\n";
                cout << string(40, '-') << endl;
                cout << left << setw(10) << "ID" 
                     << setw(25) << "Name" 
                     << setw(8) << "Age" 
                     << setw(10) << "Grade" 
                     << setw(15) << "Contact" << endl;
                cout << string(40, '-') << endl;
                student.display();
                cout << string(40, '-') << endl;
                return;
            }
        }

        cout << "Student with ID " << id << " not found." << endl;
    }

    void updateStudent() {
        string id;
        cout << "\nEnter Student ID to update: ";
        getline(cin, id);

        for (auto& student : students) {
            if (student.getId() == id) {
                string name, grade, contact;
                int age;

                cout << "Enter new Name (current: " << student.getName() << "): ";
                getline(cin, name);
                if (!name.empty()) student.setName(name);

                cout << "Enter new Age (current: " << student.getAge() << "): ";
                string ageInput;
                getline(cin, ageInput);
                if (!ageInput.empty()) {
                    try {
                        age = stoi(ageInput);
                        student.setAge(age);
                    } catch (...) {
                        cout << "Invalid age entered. Age not updated." << endl;
                    }
                }

                cout << "Enter new Grade (current: " << student.getGrade() << "): ";
                getline(cin, grade);
                if (!grade.empty()) student.setGrade(grade);

                cout << "Enter new Contact (current: " << student.getContact() << "): ";
                getline(cin, contact);
                if (!contact.empty()) student.setContact(contact);

                cout << "Student updated successfully!" << endl;
                return;
            }
        }

        cout << "Student with ID " << id << " not found." << endl;
    }

    void deleteStudent() {
        string id;
        cout << "\nEnter Student ID to delete: ";
        getline(cin, id);

        for (auto it = students.begin(); it != students.end(); ++it) {
            if (it->getId() == id) {
                students.erase(it);
                cout << "Student deleted successfully!" << endl;
                return;
            }
        }

        cout << "Student with ID " << id << " not found." << endl;
    }
};

void displayMenu() {
    cout << "\nStudent Management System\n";
    cout << "1. Add Student\n";
    cout << "2. View All Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Exit\n";
    cout << "Enter your choice (1-6): ";
}

int main() {
    StudentManager manager;
    int choice;

    do {
        displayMenu();
        cin >> choice;
        cin.ignore(); // Clear the newline character

        switch (choice) {
            case 1:
                manager.addStudent();
                break;
            case 2:
                manager.viewAllStudents();
                break;
            case 3:
                manager.searchStudent();
                break;
            case 4:
                manager.updateStudent();
                break;
            case 5:
                manager.deleteStudent();
                break;
            case 6:
                cout << "Exiting program. Goodbye!" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}