#pragma once

#include "Course.cpp"

class FullCourse : public Course
{
public:
    FullCourse(const std::string& name, int id) : Course(name, id) {}

    std::string getType() const override
    {
        return "Full-Course";
    }
};
