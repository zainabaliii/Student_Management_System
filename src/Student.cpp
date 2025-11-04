#include "Student.h"
#include <iostream>
#include <sstream>

Student::Student(const std::string& n, const std::string& i, const std::string& c,
                 const std::string& cls, const std::string& sec)
    : Person(n, i, c), className(cls), section(sec) {}

void Student::addAttendance(const std::string& date, bool present) {
    attendanceRecords.push_back({date, present});
}

void Student::addGrade(const std::string& subject, float marks) {
    grades.push_back({subject, marks});
}

float Student::calculateAverage() const {
    if (grades.empty()) return 0.0f;
    float sum = 0.0f;
    for (const auto& g : grades) sum += g.marks;
    return sum / grades.size();
}

float Student::attendancePercent() const {
    if (attendanceRecords.empty()) return 0.0f;
    int presentCount = 0;
    for (const auto& a : attendanceRecords) if (a.present) ++presentCount;
    return (presentCount * 100.0f) / attendanceRecords.size();
}

void Student::displayInfo() const {
    std::cout << std::left << std::setw(8) << id
              << std::setw(20) << name
              << std::setw(10) << className
              << std::setw(8) << section
              << std::setw(15) << contact
              << " | Avg: " << std::fixed << std::setprecision(2) << calculateAverage()
              << " | Att: " << std::fixed << std::setprecision(1) << attendancePercent() << "%\n";
}

std::string Student::toFileString() const {
    std::ostringstream oss;
    // id,name,class,section,contact\n
    oss << id << "," << name << "," << className << "," << section << "," << contact << "\n";
    return oss.str();
}

void Student::setBasicInfo(const std::string& newName, const std::string& newContact,
                           const std::string& newClass, const std::string& newSection) {
    if (!newName.empty()) name = newName;
    if (!newContact.empty()) contact = newContact;
    if (!newClass.empty()) className = newClass;
    if (!newSection.empty()) section = newSection;
}
