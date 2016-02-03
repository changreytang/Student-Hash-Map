#ifndef STUDENT_H
#define STUDENT_H
#include <string>
using namespace std;

class Student {
private:
    string name;
    double gpa;
    
public:
    Student(string name, double gpa);
    void setName(string name);
    void setGpa(double gpa);
    string getName() { return this->name; }
    double getGpa() { return this->gpa; }
};

#endif
