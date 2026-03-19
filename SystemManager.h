#ifndef SYSTEMMANAGER_H
#define SYSTEMMANAGER_H

#include "Student.h"
#include <vector>
#include <memory>

// Template function to find an item in a vector based on a custom condition
template <typename T, typename Condition>
int searchGeneric(const std::vector<T>& vec, Condition cond) {
    for (int i = 0; i < vec.size(); ++i) {
        if (cond(vec[i])) {
            return i; // Return index if found
        }
    }
    return -1; // Not found
}

class SystemManager {
private:
    vector<shared_ptr<Student>> students;

public:
    void addStudent();
    void editStudent();
    void deleteStudent();
    void displayStudents() const;
    void addScoreToStudent();
    
    // Search & Sort
    void searchByID() const;
    void searchByName() const;
    void sortStudents();
    
    // File I/O
    void saveToFile() const;
    void loadFromFile();
};

#endif