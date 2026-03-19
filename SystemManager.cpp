#include "SystemManager.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <iomanip>
#include <cctype>
using namespace std;

void SystemManager::addStudent() {
    string id, name, major;
    int birthYear;

    // 1. Kiểm tra ID: Không âm, chỉ chứa chữ và số
    while (true) {
        cout << "Enter ID (Letters and positive numbers only): ";
        cin >> id;
        
        bool valid = true;
        for (char c : id) {
            if (!isalnum(c)) { valid = false; break; } // Bắt lỗi nếu có dấu trừ (-) hoặc ký tự đặc biệt
        }
        
        if (!valid) {
            cout << "Invalid ID. No special characters or negative signs allowed.\n";
            continue;
        }

        // Kiểm tra xem ID có bị trùng trong hệ thống không
        int index = searchGeneric(students, [&](shared_ptr<Student> s) { return s->getId() == id; });
        if (index != -1) {
            cout << "Error: Student ID already exists! Please enter a different ID.\n";
            continue;
        }
        break; // ID hợp lệ, thoát vòng lặp
    }

    cin.ignore(10000, '\n'); // Dọn dẹp bộ nhớ đệm trước khi dùng getline

    // 2. Kiểm tra Name: Chỉ chứa chữ cái và khoảng trắng
    while (true) {
        cout << "Enter Name (Letters only): ";
        getline(cin, name);
        
        bool valid = true;
        if (name.empty()) valid = false;
        for (char c : name) {
            if (!isalpha(c) && c != ' ') { valid = false; break; } // Cho phép chữ cái và dấu cách
        }
        
        if (!valid) {
            cout << "Invalid Name. Please use only letters and spaces.\n";
        } else {
            break;
        }
    }

    // 3. Kiểm tra Birth Year: Lớn hơn 1975 và <= 2007
    while (true) {
        cout << "Enter Birth Year (1975 - 2007): ";
        if (cin >> birthYear && birthYear > 1975 && birthYear <= 2007) {
            break; // Năm sinh hợp lệ
        } else {
            cout << "Invalid year. Please enter a valid number between 1975 and 2007.\n";
            cin.clear(); // Xóa trạng thái lỗi của cin
            cin.ignore(10000, '\n'); // Loại bỏ các ký tự rác (như chữ cái người dùng cố tình nhập)
        }
    }

    cin.ignore(10000, '\n'); // Dọn dẹp sau khi nhập số

    // 4. Kiểm tra Major: Chỉ chứa chữ cái và khoảng trắng
    while (true) {
        cout << "Enter Major (Letters only, e.g., Thiet ke vi mach ban dan): ";
        getline(cin, major);
        
        bool valid = true;
        if (major.empty()) valid = false;
        for (char c : major) {
            if (!isalpha(c) && c != ' ') { valid = false; break; }
        }
        
        if (!valid) {
            cout << "Invalid Major. Please use only letters and spaces.\n";
        } else {
            break;
        }
    }

    // Nếu qua được hết các ải trên thì mới tiến hành tạo sinh viên
    students.push_back(make_shared<Student>(id, name, birthYear, major));
    cout << "Student added successfully!\n";
}

void SystemManager::editStudent() {
    string searchId;
    cout << "Enter ID of student to edit: "; 
    cin >> searchId;
    
    int index = searchGeneric(students, [&](shared_ptr<Student> s) { 
        return s->getId() == searchId; 
    });

    if (index != -1) {
        int choice;
        bool editing = true;
        shared_ptr<Student> target = students[index];

        while (editing) {
            cout << "\n========================================" << endl;
            cout << "   EDITING: " << target->getName() << " [" << target->getId() << "]" << endl;
            cout << "========================================" << endl;
            cout << "1. Edit Student ID" << endl;
            cout << "2. Edit Full Name" << endl;
            cout << "3. Edit Birth Year" << endl;
            cout << "4. Edit Major" << endl;
            cout << "5. Edit GPA" << endl;
            cout << "6. Save & Return" << endl;
            cout << "----------------------------------------" << endl;
            cout << "Selection (1-6): ";
            
            if (!(cin >> choice)) {
                cout << ">> Invalid input! Please enter a number." << endl;
                cin.clear();
                cin.ignore(1000, '\n');
                continue;
            }

            cin.ignore(); // Clean buffer for getline usage below

            switch (choice) {
                case 1: {
                    string newId;
                    cout << "Enter New ID: ";
                    getline(cin, newId);
                    target->setId(newId);
                    cout << ">> ID updated successfully!\n";
                    break;
                }
                case 2: {
                    string newName;
                    cout << "Enter New Name: ";
                    getline(cin, newName);
                    target->setName(newName);
                    cout << ">> Name updated successfully!\n";
                    break;
                }
                case 3: {
                    int newYear;
                    cout << "Enter New Birth Year: ";
                    cin >> newYear;
                    target->setBirthYear(newYear);
                    cout << ">> Birth Year updated successfully!\n";
                    break;
                }
                case 4: {
                    string newMajor;
                    cout << "Enter New Major: ";
                    getline(cin, newMajor);
                    target->setMajor(newMajor);
                    cout << ">> Major updated successfully!\n";
                    break;
                }
                case 5: {
                    float newGpa;
                    cout << "Enter New GPA: ";
                    cin >> newGpa;
                    target->setGpa(newGpa);
                    cout << ">> GPA updated successfully!\n";
                    break;
                }
                case 6:
                    editing = false;
                    break;
                default:
                    cout << ">> Selection out of range!\n";
            }
        }
    } else {
        cout << "[X] Error: Student not found!\n";
    }
}

void SystemManager::deleteStudent() {
    string id;
    cout << "Enter ID to delete: "; cin >> id;
    
    int index = searchGeneric(students, [&](shared_ptr<Student> s) { return s->getId() == id; });
    if (index != -1) {
        students.erase(students.begin() + index);
        cout << "Student deleted successfully!\n";
    } else {
        cout << "Student not found!\n";
    }
}

void SystemManager::displayStudents() const {
    if (students.empty()) {
        cout << "No students in the system.\n";
        return;
    }
    cout << "\n" << left << setw(10) << "ID" << setw(20) << "Name"
         << setw(10) << "BirthYear" << setw(35) << "Major" << setw(10) << "GPA" << "\n";
    cout << string(85, '-') << "\n";
    for (const auto& s : students) {
        s->displayStudent();
    }
}

void SystemManager::addScoreToStudent() {
    string id, subject;
    float score;
    cout << "Enter Student ID: "; cin >> id;

    int index = searchGeneric(students, [&](shared_ptr<Student> s) { return s->getId() == id; });
    if (index != -1) {
        cout << "Enter Subject: "; cin >> subject;
        cout << "Enter Score (0-10): "; cin >> score;
        try {
            students[index]->addScore(subject, score);
            cout << "Score added and GPA updated!\n";
        } catch (const exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    } else {
        cout << "Student not found!\n";
    }
}

void SystemManager::searchByID() const {
    string id; cout << "Enter ID to search: "; cin >> id;
    int index = searchGeneric(students, [&](shared_ptr<Student> s) { return s->getId() == id; });
    if (index != -1) {
        students[index]->displayStudent();
    } else {
        cout << "Student not found!\n";
    }
}

void SystemManager::searchByName() const {
    string name; 
    cout << "Enter Name to search: "; 
    cin.ignore(); getline(cin, name);
    
    bool found = false;
    for (const auto& s : students) {
        if (s->getName() == name) {
            s->displayStudent();
            found = true;
        }
    }
    if (!found) cout << "No student with that name found.\n";
}

void SystemManager::sortStudents() {
    int choice;
    cout << "Sort by: 1. GPA (Descending) | 2. Name | 3. Birth Year\nChoice: ";
    cin >> choice;

    if (choice == 1) {
        sort(students.begin(), students.end(), [](shared_ptr<Student> a, shared_ptr<Student> b) {
            return a->getGpa() > b->getGpa();
        });
    } else if (choice == 2) {
        sort(students.begin(), students.end(), [](shared_ptr<Student> a, shared_ptr<Student> b) {
            return a->getName() < b->getName();
        });
    } else if (choice == 3) {
        sort(students.begin(), students.end(), [](shared_ptr<Student> a, shared_ptr<Student> b) {
            return a->getBirthYear() < b->getBirthYear();
        });
    } else {
        cout << "Invalid choice!\n";
        return;
    }
    cout << "Students sorted successfully!\n";
    displayStudents();
}

void SystemManager::saveToFile() const {
    try {
        ofstream file("students.txt");
        if (!file.is_open()) throw runtime_error("Could not open file to save.");
        
        for (const auto& s : students) {
            file << s->toCSV() << "\n";
        }
        file.close();
        cout << "Data saved to students.txt successfully!\n";
    } catch (const exception& e) {
        cout << "File Error: " << e.what() << "\n";
    }
}

void SystemManager::loadFromFile() {
    try {
        ifstream file("students.txt");
        if (!file.is_open()) {
            cout << "No existing data file found. Starting fresh.\n";
            return;
        }
        
        students.clear();
        string line, id, name, major, temp;
        int year;
        
        while (getline(file, line)) {
            stringstream ss(line);
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, temp, ','); year = stoi(temp);
            getline(ss, major, ',');
            getline(ss, temp, ','); // Skip GPA reading, it calculates based on scores normally, but kept simple here
            
            students.push_back(make_shared<Student>(id, name, year, major));
        }
        file.close();
        cout << "Data loaded successfully!\n";
    } catch (const exception& e) {
         cout << "File Load Error: " << e.what() << "\n";
    }
}