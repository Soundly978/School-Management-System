#pragma once

#include "Course.cpp"

class CourseRepository {
public:
    virtual void addCourse(int id, const std::string& courseName, int type) = 0;
    virtual void updateCourse(int id) = 0;
    virtual void deleteCourse(int id) = 0;
    virtual void viewCourses() = 0;
    virtual ~CourseRepository() = default; // Virtual destructor for interface
};
