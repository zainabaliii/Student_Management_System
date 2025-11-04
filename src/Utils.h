#ifndef UTILS_H
#define UTILS_H

#include "Student.h"
#include "Course.h"
#include <vector>
#include <string>

namespace Utils {
    void pause();
    void showMenu();
    void addStudent(std::vector<Student>& students);
    void viewAll(const std::vector<Student>& students);
    void recordAttendance(std::vector<Student>& students);
    void addGrade(std::vector<Student>& students);
    void updateStudent(std::vector<Student>& students);
    void deleteStudent(std::vector<Student>& students, std::vector<Course>& courses);
    void searchStudent(const std::vector<Student>& students);
    void showAnalytics(const std::vector<Student>& students);
    void exportReport(const std::vector<Student>& students, const std::string& filename);
    // course helpers
    void manageCourses(std::vector<Student>& students, std::vector<Course>& courses);
}

#endif // UTILS_H
