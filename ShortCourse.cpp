#pragma once

#include "Course.cpp"

class ShortCourse : public Course
{
public:
    ShortCourse(const std::string& name, int id) : Course(name, id) {}

    std::string getType() const override
    {
        return "Short-Course";
    }
};
