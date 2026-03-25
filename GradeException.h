#ifndef GRADEEXCEPTION_H
#define GRADEEXCEPTION_H

#include <stdexcept>
#include <string>
using namespace std;

class GradeException : public runtime_error {
private:
    string studentID;
    string courseCode;

public:
    GradeException(const string &msg,
                   const string &sid  = "",
                   const string &code = "")
        : runtime_error(msg), studentID(sid), courseCode(code) {}

    const string& getStudentID()  const { return studentID;  }
    const string& getCourseCode() const { return courseCode; }
};

#endif