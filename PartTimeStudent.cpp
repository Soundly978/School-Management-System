#pragma once
#include "Student.cpp"

class PartTimeStudent : public Student
{
public:
    PartTimeStudent(const std::string& name, int id)
        : Student(name, id) {}

    std::string getType() const override
    {
        return "Part-Time";
    }
};
