#include "SystemManager.h"
#include <iostream>

using namespace std;

int main() {
    SystemManager sys;
    sys.loadFromFile(); // Load existing data on startup
    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT =====\n";
        cout << "1. Add Student\n";
        cout << "2. Edit Student\n";
        cout << "3. Delete Student\n";
        cout << "4. Add Score to Student\n";
        cout << "5. Display Students\n";
        cout << "6. Search Student (by ID)\n";
        cout << "7. Search Student (by Name)\n";
        cout << "8. Sort Students\n";
        cout << "9. Save to File\n";
        cout << "10. Load from File\n";
        cout << "0. Exit\n";
        cout << "Choose an option: ";
        
        if (!(cin >> choice)) {
            cout << "Invalid input. Enter a number.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        switch (choice) {
            case 1: sys.addStudent(); break;
            case 2: sys.editStudent(); break;
            case 3: sys.deleteStudent(); break;
            case 4: sys.addScoreToStudent(); break;
            case 5: sys.displayStudents(); break;
            case 6: sys.searchByID(); break;
            case 7: sys.searchByName(); break;
            case 8: sys.sortStudents(); break;
            case 9: sys.saveToFile(); break;
            case 10: sys.loadFromFile(); break;
            case 0: 
                sys.saveToFile(); // Auto-save on exit
                cout << "Exiting program. Goodbye!\n"; 
                break;
            default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}