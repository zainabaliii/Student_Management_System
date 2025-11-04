#ifndef STUDENT_H
#define STUDENT_H

#include "Person.h"
#include <vector>
#include <string>
#include <iomanip>

struct Attendance {
    std::string date;
    bool present;
};

struct Grade {
    std::string subject;
    float marks;
};

class Student : public Person {
private:
    std::string className;
    std::string section;
    std::vector<Attendance> attendanceRecords;
    std::vector<Grade> grades;

public:
    Student(const std::string& n = "", const std::string& i = "", const std::string& c = "",
            const std::string& cls = "", const std::string& sec = "");

    // operations
    void addAttendance(const std::string& date, bool present);
    void addGrade(const std::string& subject, float marks);

    // calculations
    float calculateAverage() const;
    float attendancePercent() const;

    // display / serialization
    void displayInfo() const override;
    std::string toFileString() const; // save basic fields

    // accessors & mutators
    std::string getClassName() const { return className; }
    std::string getSection() const { return section; }
    void setClass(const std::string& c) { className = c; }
    void setSection(const std::string& s) { section = s; }

    void setBasicInfo(const std::string& newName, const std::string& newContact,
                      const std::string& newClass, const std::string& newSection);

    // For FileManager
    const std::vector<Attendance>& getAttendance() const { return attendanceRecords; }
    const std::vector<Grade>& getGrades() const { return grades; }
};

#endif // STUDENT_H
