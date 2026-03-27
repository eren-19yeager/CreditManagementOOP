#include "ResultManager.h"
#include <bits/stdc++.h>
using namespace std;

void ResultManager::addGrade(const string& studentID, const string& courseCode, float marks) {
    // Update if already exists, otherwise add
    for (auto& g : internalGrades) {
        if (g.studentID == studentID && g.courseCode == courseCode) {
            g = Grades(studentID, courseCode, marks);
            return;
        }
    }
    internalGrades.push_back(Grades(studentID, courseCode, marks));
}

float ResultManager::calculateGPA(const vector<Grades>& grades, string studentID) {
    float total = 0;
    int   count = 0;
    for (const auto& g : grades) {
        if (g.studentID == studentID) {
            if      (g.letter == "A") total += 4;
            else if (g.letter == "B") total += 3;
            else if (g.letter == "C") total += 2;
            else if (g.letter == "D") total += 1;
            else                      total += 0;
            count++;
        }
    }
    if (count == 0) return 0;
    return total / count;
}

void ResultManager::generateTranscript(const vector<Grades>& grades, string studentID) {
    cout << "\n===== TRANSCRIPT =====\n";

    // Collect and sort using Grades::operator< (highest marks first)
    vector<Grades> studentGrades;
    for (const auto& g : grades)
        if (g.studentID == studentID) studentGrades.push_back(g);

    sort(studentGrades.begin(), studentGrades.end()); // uses Grades::operator<

    if (studentGrades.empty()) cout << "No grades recorded.\n";
    else
        for (const auto& g : studentGrades)
            cout << "  " << g << "\n";  // uses Grades::operator<<

    cout << "=====================\n";
}
