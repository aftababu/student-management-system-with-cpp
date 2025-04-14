#ifndef STUDENT_H
#define STUDENT_H

#include "./helpers.h"
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>

class Student {
private:
    string id;
    string name;
    int age;
    string grade;
    string contact;

public:
    // Constructors (Polymorphism - overloading)
    Student();
    Student(string id, string name, int age, string grade, string contact);

    // Getters
    string getId() const;
    string getName() const;
    int getAge() const;
    string getGrade() const;
    string getContact() const;

    // Setters
    void setId(string id);
    void setName(string name);
    void setAge(int age);
    void setGrade(string grade);
    void setContact(string contact);

    // Virtual function for polymorphism
    virtual void display() const;

    // Friend functions
    friend ofstream& operator<<(ofstream& ofs, const Student& student);
    friend ifstream& operator>>(ifstream& ifs, Student& student);

    // Operator overloading
    bool operator==(const Student& other) const;
    bool operator!=(const Student& other) const;
};

// Overloaded operators
ofstream& operator<<(ofstream& ofs, const Student& student);
ifstream& operator>>(ifstream& ifs, Student& student);

#endif // STUDENT_H