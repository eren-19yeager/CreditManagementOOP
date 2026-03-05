#include "Grades.h"

Grades::Grades(float p) {
    percentage = p;
    computeGrade();
}

void Grades::computeGrade() {
    if(percentage >= 80){
        gradePoint = 4.0; letter = "A+";
    }
    else if(percentage >= 75){
        gradePoint = 3.75; letter = "A";
    }
    else if(percentage >= 70){
        gradePoint = 3.5; letter = "A-";
    }
    else if(percentage >= 65){
        gradePoint = 3.25; letter = "B+";
    }
    else if(percentage >= 60){
        gradePoint = 3.0; letter = "B";
    }
    else{
        gradePoint = 0.0; letter = "F";
    }
}

float Grades::getGPA() const { return gradePoint; }
string Grades::getLetter() const { return letter; }