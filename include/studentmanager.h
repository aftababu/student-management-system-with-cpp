#ifndef STUDENTMANAGER_H
#define STUDENTMANAGER_H

#include "./helpers.h"
#include "./student.h"
#include <vector>

class StudentManager {
private:
    vector<Student> students;
    string filename = "students.txt";

    void loadFromFile();
    void saveToFile();

public:
    StudentManager();
    ~StudentManager();

    // CRUD Operations
    void addStudent();
    void viewAllStudents() const;
    void searchStudent() const;
    void updateStudent();
    void deleteStudent();

    // Additional polymorphic example
    virtual void showSystemInfo() const;
};

#endif // STUDENTMANAGER_H

