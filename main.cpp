#include "./include/studentmanager.h"

void displayMenu()
{
    cout << "\nStudent Management System\n";
    cout << "1. Add Student\n";
    cout << "2. View All Students\n";
    cout << "3. Search Student\n";
    cout << "4. Update Student\n";
    cout << "5. Delete Student\n";
    cout << "6. Exit\n";
    cout << "Enter your choice (1-6): ";
}

int main()
{
    StudentManager manager;
    int choice;

    do
    {
        displayMenu();
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
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