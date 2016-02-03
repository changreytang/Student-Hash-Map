#include "Student.h"
#include <string>
using namespace std;

Student::Student(string name, double gpa) {
    
    this->name = name;
    this->gpa = gpa;
    
}

void Student::setName(string name) {
    
    this->name = name;
    
}

void Student::setGpa(double gpa) {
    
    this->gpa = gpa;
    
}