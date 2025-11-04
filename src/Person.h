#ifndef PERSON_H
#define PERSON_H

#include <string>

class Person {
protected:
    std::string name;
    std::string id;
    std::string contact;

public:
    Person(const std::string& n = "", const std::string& i = "", const std::string& c = "")
        : name(n), id(i), contact(c) {}

    virtual ~Person() = default;
    virtual void displayInfo() const = 0;

    // getters & setters
    std::string getID() const { return id; }
    std::string getName() const { return name; }
    std::string getContact() const { return contact; }

    void setName(const std::string& n) { name = n; }
    void setContact(const std::string& c) { contact = c; }
};

#endif // PERSON_H
