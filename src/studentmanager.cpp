#include "../include/studentmanager.h"
#include <fstream>
#include <limits>
#include <iomanip>

// Constructor
StudentManager::StudentManager() {
    loadFromFile();
}

// Destructor
StudentManager::~StudentManager() {
    saveToFile();
}

void StudentManager::loadFromFile() {
    ifstream ifs(filename);
    if (!ifs) return;

    Student student;
    while (ifs >> student) {
        students.push_back(student);
    }
    ifs.close();
}

void StudentManager::saveToFile() {
    ofstream ofs(filename);
    if (!ofs) {
        cerr << "Error saving file!" << endl;
        return;
    }

    for (const auto& student : students) {
        ofs << student;
    }
    ofs.close();
}

void StudentManager::addStudent() {
    string id, name, grade, contact;
    int age;

    cout << "\nEnter Student ID: ";
    getline(cin, id);

    // Check if ID exists
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
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid age. Please enter a positive number: ";
    }
    cin.ignore();

    cout << "Enter Student Grade: ";
    getline(cin, grade);

    cout << "Enter Contact Information: ";
    getline(cin, contact);

    students.emplace_back(id, name, age, grade, contact);
    cout << "Student added successfully!" << endl;
}

void StudentManager::viewAllStudents() const {
    if (students.empty()) {
        cout << "\nNo students found." << endl;
        return;
    }

    cout << "\n" << string(80, '-') << endl;
    cout << left << setw(10) << "ID" << setw(25) << "Name" 
         << setw(8) << "Age" << setw(10) << "Grade" 
         << setw(15) << "Contact" << endl;
    cout << string(80, '-') << endl;

    for (const auto& student : students) {
        student.display();
    }
    cout << string(80, '-') << endl;
}

void StudentManager::searchStudent() const {
    string id;
    cout << "\nEnter Student ID to search: ";
    getline(cin, id);

    for (const auto& student : students) {
        if (student.getId() == id) {
            cout << "\nStudent Found:\n";
            cout << string(40, '-') << endl;
            student.display();
            cout << string(40, '-') << endl;
            return;
        }
    }
    cout << "Student not found." << endl;
}

void StudentManager::updateStudent() {
    string id;
    cout << "\nEnter Student ID to update: ";
    getline(cin, id);

    for (auto& student : students) {
        if (student.getId() == id) {
            string name, grade, contact;
            int age;

            cout << "Enter new Name: ";
            getline(cin, name);
            if (!name.empty()) student.setName(name);

            cout << "Enter new Age: ";
            string ageInput;
            getline(cin, ageInput);
            if (!ageInput.empty()) {
                try {
                    age = stoi(ageInput);
                    student.setAge(age);
                } catch (...) {
                    cout << "Invalid age." << endl;
                }
            }

            cout << "Enter new Grade: ";
            getline(cin, grade);
            if (!grade.empty()) student.setGrade(grade);

            cout << "Enter new Contact: ";
            getline(cin, contact);
            if (!contact.empty()) student.setContact(contact);

            cout << "Student updated!" << endl;
            return;
        }
    }
    cout << "Student not found." << endl;
}

void StudentManager::deleteStudent() {
    string id;
    cout << "\nEnter Student ID to delete: ";
    getline(cin, id);

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getId() == id) {
            students.erase(it);
            cout << "Student deleted!" << endl;
            return;
        }
    }
    cout << "Student not found." << endl;
}

void StudentManager::showSystemInfo() const {
    cout << "\nStudent Management System v1.0\n";
    cout << "Total students: " << students.size() << endl;
}