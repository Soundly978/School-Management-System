#pragma once

#include <iostream>
#include <iomanip>
#include <string>

class Course
{
protected:
    std::string courseName;
    int id;

public:
    Course(const std::string& name, int id) : courseName(name), id(id) {}

    virtual std::string getType() const = 0;  // Pure virtual function

    static void printHeader()
    {
        const int width = 20;
        std::cout << std::left << std::setw(width) << "Course Name"
            << std::left << std::setw(width) << "ID"
            << std::left << std::setw(width) << "Type"
            << std::endl;
    }

    virtual void display() const
    {
        const int width = 20;
        std::cout << std::left << std::setw(width) << courseName
            << std::left << std::setw(width) << id
            << std::left << std::setw(width) << getType()
            << std::endl;
    }

    virtual ~Course() = default;

    // Getter and setter for courseName
    std::string getCourseName() const { return courseName; }
    void setCourseName(const std::string& name) { courseName = name; }

    // Getter and setter for id
    int getId() const { return id; }
    void setId(int id) { this->id = id; }
};
