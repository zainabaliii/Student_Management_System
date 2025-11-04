#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <fstream>
#include <limits>

using namespace std;

namespace Utils {

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // Wait for the user to press Enter (if input buffer is already clean it's okay)
}

void showMenu() {
    cout << "\n=========================================\n";
    cout << "       STUDENT MANAGEMENT SYSTEM         \n";
    cout << "=========================================\n";
    cout << "1. Add Student\n";
    cout << "2. View All Students\n";
    cout << "3. Record Attendance\n";
    cout << "4. Add Grade\n";
    cout << "5. Update Student\n";
    cout << "6. Delete Student\n";
    cout << "7. Search Student\n";
    cout << "8. View Analytics\n";
    cout << "9. Manage Courses\n";
    cout << "10. Export Report\n";
    cout << "11. Save & Exit\n";
    cout << "Enter your choice: ";
}

void addStudent(vector<Student>& students) {
    string id, name, contact, cls, sec;
    cout << "Enter ID: "; cin >> id;
    cin.ignore();
    cout << "Enter Name: "; getline(cin, name);
    cout << "Enter Contact: "; getline(cin, contact);
    cout << "Enter Class: "; getline(cin, cls);
    cout << "Enter Section: "; getline(cin, sec);

    // check for duplicate ID
    for (const auto& s : students) if (s.getID() == id) {
        cout << "❌ A student with this ID already exists.\n";
        return;
    }

    students.emplace_back(name, id, contact, cls, sec);
    cout << "✅ Student added successfully.\n";
}

void viewAll(const vector<Student>& students) {
    if (students.empty()) { cout << "No students available.\n"; return; }
    cout << left << setw(8) << "ID" << setw(20) << "Name"
         << setw(10) << "Class" << setw(8) << "Sec"
         << setw(15) << "Contact" << " | Avg | Att%\n";
    cout << string(75, '-') << endl;
    for (const auto& s : students) s.displayInfo();
}

void recordAttendance(vector<Student>& students) {
    string id, date;
    cout << "Enter Student ID: "; cin >> id;
    cout << "Enter Date (YYYY-MM-DD): "; cin >> date;
    char status;
    cout << "Present (P) or Absent (A)? "; cin >> status;

    for (auto& s : students) {
        if (s.getID() == id) {
            s.addAttendance(date, (status == 'P' || status == 'p'));
            cout << "✅ Attendance recorded.\n";
            return;
        }
    }
    cout << "❌ Student not found.\n";
}

void addGrade(vector<Student>& students) {
    string id, subject;
    double marks;
    cout << "Enter Student ID: "; cin >> id;
    cout << "Enter Subject: "; cin >> subject;
    cout << "Enter Marks: "; cin >> marks;

    for (auto& s : students) {
        if (s.getID() == id) {
            s.addGrade(subject, static_cast<float>(marks));
            cout << "✅ Grade added.\n";
            return;
        }
    }
    cout << "❌ Student not found.\n";
}

void updateStudent(vector<Student>& students) {
    string id;
    cout << "Enter ID of student to update: "; cin >> id;
    cin.ignore();
    for (auto& s : students) {
        if (s.getID() == id) {
            string newName, newContact, newClass, newSection;
            cout << "Enter new Name (leave blank to keep current): ";
            getline(cin, newName);
            cout << "Enter new Contact (leave blank to keep current): ";
            getline(cin, newContact);
            cout << "Enter new Class (leave blank to keep current): ";
            getline(cin, newClass);
            cout << "Enter new Section (leave blank to keep current): ";
            getline(cin, newSection);
            s.setBasicInfo(newName, newContact, newClass, newSection);
            cout << "✅ Student updated.\n";
            return;
        }
    }
    cout << "❌ Student not found.\n";
}

void deleteStudent(vector<Student>& students, vector<Course>& courses) {
    string id;
    cout << "Enter ID of student to delete: "; cin >> id;
    auto it = remove_if(students.begin(), students.end(),
                        [&](const Student &s){ return s.getID() == id; });
    if (it != students.end()) {
        students.erase(it, students.end());
        // remove from all courses
        for (auto& c : courses) c.removeStudentByID(id);
        cout << "✅ Student deleted successfully.\n";
    } else {
        cout << "❌ Student not found.\n";
    }
}

void searchStudent(const vector<Student>& students) {
    string keyword;
    cin.ignore();
    cout << "Enter Name or ID to search: ";
    getline(cin, keyword);
    bool found = false;
    for (const auto& s : students) {
        if (s.getID() == keyword || s.getName() == keyword) {
            cout << left << setw(8) << "ID" << setw(20) << "Name"
                 << setw(10) << "Class" << setw(8) << "Sec"
                 << setw(15) << "Contact" << " | Avg | Att%\n";
            cout << string(75, '-') << endl;
            s.displayInfo();
            found = true;
        }
    }
    if (!found) cout << "❌ No matching student found.\n";
}

void showAnalytics(const vector<Student>& students) {
    if (students.empty()) { cout << "No students to analyze.\n"; return; }
    float total = 0.0f;
    float highest = -1.0f;
    std::string topName;
    for (const auto& s : students) {
        float avg = s.calculateAverage();
        total += avg;
        if (avg > highest) { highest = avg; topName = s.getName(); }
    }
    cout << "\n--- CLASS ANALYTICS ---\n";
    cout << "Average Class Score: " << (total / students.size()) << "\n";
    cout << "Top Performer: " << topName << " (" << highest << ")\n";
}

void exportReport(const vector<Student>& students, const string& filename) {
    ofstream out(filename);
    if (!out) { cerr << "Error creating report file.\n"; return; }
    out << "===== CLASS REPORT =====\n";
    for (const auto& s : students) {
        out << s.getID() << " - " << s.getName()
            << " | Avg: " << s.calculateAverage()
            << " | Attendance: " << s.attendancePercent() << "%\n";
    }
    out.close();
    cout << "✅ Report exported to " << filename << "\n";
}

void manageCourses(vector<Student>& students, vector<Course>& courses) {
    int choice = 0;
    do {
        cout << "\n--- Course Management ---\n";
        cout << "1. Create Course\n2. List Courses\n3. Enroll Student in Course\n4. Remove Student from Course\n5. Show Course Info\n6. Back\nChoice: ";
        cin >> choice;
        if (choice == 1) {
            string code, name;
            cout << "Course Code: "; cin >> code; cin.ignore();
            cout << "Course Name: "; getline(cin, name);
            courses.emplace_back(code, name);
            cout << "✅ Course created.\n";
        } else if (choice == 2) {
            if (courses.empty()) cout << "No courses exist.\n";
            else {
                for (size_t i = 0; i < courses.size(); ++i)
                    cout << i+1 << ". " << courses[i].getCode() << " - " << courses[i].getName() << "\n";
            }
        } else if (choice == 3) {
            if (courses.empty()) { cout << "No courses. Create one first.\n"; continue; }
            int idx; string sid;
            cout << "Choose course index to enroll into: "; cin >> idx;
            if (idx < 1 || idx > (int)courses.size()) { cout << "Invalid index.\n"; continue; }
            cout << "Enter Student ID to enroll: "; cin >> sid;
            bool ok = false;
            for (auto& s : students) {
                if (s.getID() == sid) {
                    courses[idx-1].addStudent(&s);
                    cout << "✅ Student enrolled.\n";
                    ok = true; break;
                }
            }
            if (!ok) cout << "Student not found.\n";
        } else if (choice == 4) {
            if (courses.empty()) { cout << "No courses.\n"; continue; }
            int idx; string sid;
            cout << "Choose course index to remove from: "; cin >> idx;
            if (idx < 1 || idx > (int)courses.size()) { cout << "Invalid index.\n"; continue; }
            cout << "Enter Student ID to remove: "; cin >> sid;
            courses[idx-1].removeStudentByID(sid);
            cout << "✅ If student was enrolled, they have been removed from that course.\n";
        } else if (choice == 5) {
            if (courses.empty()) { cout << "No courses.\n"; continue; }
            int idx;
            cout << "Choose course index to view: "; cin >> idx;
            if (idx < 1 || idx > (int)courses.size()) { cout << "Invalid index.\n"; continue; }
            courses[idx-1].showCourseInfo();
            cout << "Course Average: " << courses[idx-1].classAverage() << "\n";
        }
    } while (choice != 6);
}

} // namespace Utils
