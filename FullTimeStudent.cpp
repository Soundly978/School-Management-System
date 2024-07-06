#pragma once
#include "Student.cpp"

class FullTimeStudent : public Student
{
public:
    FullTimeStudent(const std::string& name, int id)
        : Student(name, id) {}

    std::string getType() const override
    {
        return "Full-Time";
    }
};
