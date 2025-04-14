#include "../include/student.h"

// Constructors
Student::Student() : id(""), name(""), age(0), grade(""), contact("") {}

Student::Student(string id, string name, int age, string grade, string contact)
    : id(id), name(name), age(age), grade(grade), contact(contact) {}

// Getters
string Student::getId() const { return id; }
string Student::getName() const { return name; }
int Student::getAge() const { return age; }
string Student::getGrade() const { return grade; }
string Student::getContact() const { return contact; }

// Setters
void Student::setId(string id) { this->id = id; }
void Student::setName(string name) { this->name = name; }
void Student::setAge(int age) { this->age = age; }
void Student::setGrade(string grade) { this->grade = grade; }
void Student::setContact(string contact) { this->contact = contact; }

// Display method
void Student::display() const {
    cout << left << setw(10) << id 
         << setw(25) << name 
         << setw(8) << age 
         << setw(10) << grade 
         << setw(15) << contact << endl;
}

// Operator overloading
bool Student::operator==(const Student& other) const {
    return this->id == other.id;
}

bool Student::operator!=(const Student& other) const {
    return !(*this == other);
}

// Friend function implementations
ofstream& operator<<(ofstream& ofs, const Student& student) {
    ofs << student.id << endl;
    ofs << student.name << endl;
    ofs << student.age << endl;
    ofs << student.grade << endl;
    ofs << student.contact << endl;
    return ofs;
}

ifstream& operator>>(ifstream& ifs, Student& student) {
    getline(ifs, student.id);
    getline(ifs, student.name);
    ifs >> student.age;
    ifs.ignore();
    getline(ifs, student.grade);
    getline(ifs, student.contact);
    return ifs;
}