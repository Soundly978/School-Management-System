#pragma once

#include <iostream>
#include <string>
#include <stdexcept>
#include <fstream>
#include "PartTimeStudent.cpp"
#include "FullTimeStudent.cpp"
#include "DataValidInput.cpp"

class StudentRepository
{
public:
    virtual ~StudentRepository() {}

    virtual void addStudent(int id, const std::string& name, int type) = 0;

    virtual void updateStudent(int id) = 0;

    virtual void deleteStudent(int id) = 0;

    virtual void viewStudents() = 0;

    virtual void saveToFile(const std::string& filename) const = 0;

    virtual void loadFromFile(const std::string& filename) = 0;

protected:
    void validateId(int id)
    {
        if (id <= 0)
        {
            throw std::invalid_argument("ID must be greater than zero.");
        }
    }

    std::string getStudentType(int type) const
    {
        return (type == 1) ? "Part-Time" : (type == 2) ? "Full-Time" : "";
    }
};
