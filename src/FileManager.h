#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include "Student.h"
#include "Course.h"
#include <vector>
#include <string>
#include <mutex>

class FileManager {
private:
    static FileManager* instance;
    static std::mutex instMutex;
    FileManager() = default;

public:
    FileManager(const FileManager&) = delete;
    FileManager& operator=(const FileManager&) = delete;

    static FileManager* getInstance();

    // student-related
    void saveAll(const std::vector<Student>& students, const std::string& studentsFile,
                 const std::string& attendanceFile, const std::string& gradesFile);
    void loadAll(std::vector<Student>& students, const std::string& studentsFile,
                 const std::string& attendanceFile, const std::string& gradesFile);

    // 🆕 course-related
    void saveCourses(const std::vector<Course>& courses, const std::string& filename);
    void loadCourses(std::vector<Course>& courses, const std::string& filename, std::vector<Student>& students);
};

#endif // FILEMANAGER_H
