#include "Student.h"
#include "FileManager.h"
#include "Course.h"
#include "Utils.h"
#include <vector>
#include <iostream>

int main() {
    std::vector<Student> students;
    std::vector<Course> courses;

    const std::string studentsFile = "data/students.txt";
    const std::string attendanceFile = "data/attendance.txt";
    const std::string gradesFile = "data/grades.txt";
    const std::string coursesFile = "data/courses.txt";

    FileManager* fm = FileManager::getInstance();
    fm->loadAll(students, studentsFile, attendanceFile, gradesFile);
    fm->loadCourses(courses, coursesFile, students);

    int choice = 0;
    do {
        Utils::showMenu();
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input.\n";
            continue;
        }

        switch (choice) {
            case 1: Utils::addStudent(students); break;
            case 2: Utils::viewAll(students); break;
            case 3: Utils::recordAttendance(students); break;
            case 4: Utils::addGrade(students); break;
            case 5: Utils::updateStudent(students); break;
            case 6: Utils::deleteStudent(students, courses); break;
            case 7: Utils::searchStudent(students); break;
            case 8: Utils::showAnalytics(students); break;
            case 9: Utils::manageCourses(students, courses); break;
            case 10: Utils::exportReport(students, "class_report.txt"); break;
            case 11:
                fm->saveAll(students, studentsFile, attendanceFile, gradesFile);
                fm->saveCourses(courses, coursesFile);
                std::cout << "Saved all data. Exiting...\n";
                break;
            default: std::cout << "Invalid option.\n"; break;
        }

        if (choice != 11) Utils::pause();
    } while (choice != 11);
}

