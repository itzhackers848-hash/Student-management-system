#include "Student.h"
#include <iomanip>
#include <stdexcept>

// Constructor implementation
Student::Student(string i, string n, int b, string m, string s) {
    id = i;
    name = n;
    birthYear = b;
    major = m;
    gpa = 0.0f;
}

// Getters
string Student::getId() const { return id; }
string Student::getName() const { return name; }
int Student::getBirthYear() const { return birthYear; }
string Student::getMajor() const { return major; }
float Student::getGpa() const { return gpa; }

// Setters
void Student::setId(string newId) { id = newId; }
void Student::setName(string newName) { name = newName; }
void Student::setBirthYear(int newYear) { birthYear = newYear; }
void Student::setMajor(string newMajor) { major = newMajor; }
void Student::setGpa(float newGpa) { gpa = newGpa; }

// Add a score and recalculate GPA
void Student::addScore(string subject, float score) {
    if (score < 0.0 || score > 10.0) {
        throw invalid_argument("Score must be between 0 and 10.");
    }
    scores[subject] = score;
    calculateGPA();
}

// Calculate GPA based on the map of scores
void Student::calculateGPA() {
    if (scores.empty()) {
        gpa = 0.0f;
        return;
    }
    float totalScore = 0.0f;
    for (const auto& pair : scores) {
        totalScore += pair.second;
    }
    gpa = totalScore / scores.size();
}

// Display student info in a clean table row
void Student::displayStudent() const {
    cout << left << setw(10) << id 
         << setw(20) << name 
         << setw(10) << birthYear 
         << setw(35) << major 
         << setw(10) << fixed << setprecision(2) << gpa << endl;
}

// Format data for saving to a text file
string Student::toCSV() const {
    return id + "," + name + "," + to_string(birthYear) + "," + major + ","  + to_string(gpa);
}