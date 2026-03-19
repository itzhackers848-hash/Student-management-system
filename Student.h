#ifndef STUDENT_H
#define STUDENT_H

#include <iostream>
#include <string>
#include <map>

using namespace std;

class Student {
private:
    string id;
    string name;
    int birthYear;
    string major;
    string subject;
    float gpa;
    map<string, float> scores; // Stores subject name and score

public:
    // Constructor
    Student(string id, string name, int birthYear, string major, string subject);

    // Getters
    string getId() const;
    string getName() const;
    int getBirthYear() const;
    string getMajor() const;
    float getGpa() const;
    string getSubject() const;

    // Setters
    void setName(string newName);
    void setMajor(string newMajor);
    void setId(string newID);
    void setBirthYear(int newYear);
    void setGpa(float newGpa);

    // Score and Display functions
    void addScore(string subject, float score);
    void calculateGPA(); // Calculates average of all scores
    void displayStudent() const;
    
    // For file saving
    string toCSV() const; 
};

#endif