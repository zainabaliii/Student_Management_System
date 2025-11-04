#ifndef COURSE_H
#define COURSE_H

#include "Student.h"
#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
#include <iomanip>

class Course {
private:
    std::string courseCode;
    std::string courseName;
    std::vector<Student*> enrolled;

public:
    Course(const std::string& code = "", const std::string& name = "")
        : courseCode(code), courseName(name) {}

    void addStudent(Student* s) { if (s) enrolled.push_back(s); }

    void removeStudentByID(const std::string& id) {
        enrolled.erase(std::remove_if(enrolled.begin(), enrolled.end(),
            [&](Student* s){ return s && s->getID() == id; }), enrolled.end());
    }

    void showCourseInfo() const {
        std::cout << "\nCourse: " << courseCode << " - " << courseName
                  << " | Enrolled: " << enrolled.size() << "\n";
        if (enrolled.empty()) return;
        std::cout << std::left << std::setw(8) << "ID" << std::setw(20) << "Name"
                  << std::setw(10) << "Class" << std::setw(8) << "Sec"
                  << std::setw(15) << "Contact" << " | Avg | Att%\n";
        std::cout << std::string(75, '-') << "\n";
        for (auto s : enrolled) s->displayInfo();
    }

    float classAverage() const {
        if (enrolled.empty()) return 0.0f;
        float sum = 0.0f;
        for (auto s : enrolled) sum += s->calculateAverage();
        return sum / enrolled.size();
    }

    std::string getCode() const { return courseCode; }
    std::string getName() const { return courseName; }

    // 🆕 expose enrolled list for FileManager
    const std::vector<Student*>& getEnrolledStudents() const { return enrolled; }
};

#endif // COURSE_H
