#include "FileManager.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include <mutex>

FileManager* FileManager::instance = nullptr;
std::mutex FileManager::instMutex;

// Singleton instance getter
FileManager* FileManager::getInstance() {
    std::lock_guard<std::mutex> lock(instMutex);
    if (instance == nullptr)
        instance = new FileManager();
    return instance;
}

// Save all student data
void FileManager::saveAll(const std::vector<Student>& students,
                          const std::string& studentsFile,
                          const std::string& attendanceFile,
                          const std::string& gradesFile) {
    std::ofstream fs(studentsFile);
    std::ofstream fa(attendanceFile);
    std::ofstream fg(gradesFile);

    if (!fs || !fa || !fg) {
        std::cerr << "Error: Unable to open data files for saving.\n";
        return;
    }

    for (const auto& s : students) {
        fs << s.toFileString();

        for (const auto& att : s.getAttendance())
            fa << s.getID() << "," << att.date << "," << att.present << "\n";

        for (const auto& g : s.getGrades())
            fg << s.getID() << "," << g.subject << "," << g.marks << "\n";
    }

    fs.close();
    fa.close();
    fg.close();
    std::cout << "All student data saved successfully.\n";
}

// Load all student data
void FileManager::loadAll(std::vector<Student>& students,
                          const std::string& studentsFile,
                          const std::string& attendanceFile,
                          const std::string& gradesFile) {
    std::ifstream fs(studentsFile);
    std::ifstream fa(attendanceFile);
    std::ifstream fg(gradesFile);

    if (!fs) {
        std::cout << "No student data found (" << studentsFile << "). Starting fresh.\n";
        return;
    }

    std::string line;
    while (std::getline(fs, line)) {
        std::stringstream ss(line);
        std::string id, name, cls, sec, contact;
        std::getline(ss, id, ',');
        std::getline(ss, name, ',');
        std::getline(ss, cls, ',');
        std::getline(ss, sec, ',');
        std::getline(ss, contact, '\n');

        students.emplace_back(name, id, contact, cls, sec);
    }

    // Load attendance
    if (fa) {
        while (std::getline(fa, line)) {
            std::stringstream ss(line);
            std::string id, date, presentStr;
            std::getline(ss, id, ',');
            std::getline(ss, date, ',');
            std::getline(ss, presentStr, '\n');
            bool present = (presentStr == "1" || presentStr == "true");
            for (auto& s : students)
                if (s.getID() == id)
                    s.addAttendance(date, present);
        }
    }

    // Load grades
    if (fg) {
        while (std::getline(fg, line)) {
            std::stringstream ss(line);
            std::string id, subject, marksStr;
            std::getline(ss, id, ',');
            std::getline(ss, subject, ',');
            std::getline(ss, marksStr, '\n');
            float marks = std::stof(marksStr);
            for (auto& s : students)
                if (s.getID() == id)
                    s.addGrade(subject, marks);
        }
    }

    std::cout << "Student data loaded successfully (" << students.size() << ").\n";
}

// Save courses
void FileManager::saveCourses(const std::vector<Course>& courses, const std::string& filename) {
    std::ofstream fc(filename);
    if (!fc) {
        std::cerr << "Error: Cannot open " << filename << " for writing.\n";
        return;
    }

    for (const auto& c : courses) {
        fc << c.getCode() << "," << c.getName() << ",";
        const auto& enrolled = c.getEnrolledStudents();
        for (size_t i = 0; i < enrolled.size(); ++i) {
            fc << enrolled[i]->getID();
            if (i < enrolled.size() - 1) fc << ";";
        }
        fc << "\n";
    }
    fc.close();
    std::cout << "Courses saved successfully.\n";
}

// Load courses
void FileManager::loadCourses(std::vector<Course>& courses,
                              const std::string& filename,
                              std::vector<Student>& students) {
    std::ifstream fc(filename);
    if (!fc) {
        std::cout << "No course data found (" << filename << "). Starting fresh.\n";
        return;
    }

    std::string line;
    while (std::getline(fc, line)) {
        std::stringstream ss(line);
        std::string code, name, idsPart;
        std::getline(ss, code, ',');
        std::getline(ss, name, ',');
        std::getline(ss, idsPart, '\n');

        Course course(code, name);
        std::stringstream idStream(idsPart);
        std::string id;
        while (std::getline(idStream, id, ';')) {
            auto it = std::find_if(students.begin(), students.end(),
                                   [&](Student& s){ return s.getID() == id; });
            if (it != students.end()) course.addStudent(&(*it));
        }
        courses.push_back(course);
    }
    fc.close();
    std::cout << "Courses loaded successfully (" << courses.size() << ").\n";
}
