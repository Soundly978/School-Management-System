#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <iomanip>
#include <fstream>

#include "Course.cpp"
#include "ShortCourse.cpp"
#include "FullCourse.cpp"
#include "DataValidInput.cpp"
#include "CourseRepository.cpp"

class CourseManager : public CourseRepository {
private:
    std::vector<Course*> courses;

    Course* findCourseById(int id) const {
        auto it = std::find_if(courses.begin(), courses.end(), [id](Course* course) {
            return course->getId() == id;
            });
        return (it != courses.end()) ? *it : nullptr;
    }

    void printHeader() const {
        const int width = 20;
        std::cout << std::left << std::setw(width) << "Course Name"
            << std::left << std::setw(width) << "ID"
            << std::left << std::setw(width) << "Type"
            << std::endl;
    }

public:
    ~CourseManager() {
        for (auto course : courses) {
            delete course;
        }
    }

    void addCourse(int id, const std::string& courseName, int type) override {
        if (findCourseById(id) != nullptr) {
            throw std::invalid_argument("Course ID already exists.");
        }

        if (type == 1) {
            courses.push_back(new ShortCourse(courseName, id));
        }
        else if (type == 2) {
            courses.push_back(new FullCourse(courseName, id));
        }
        else {
            throw std::invalid_argument("Invalid course type.");
        }

        std::cout << "Course added successfully.\n\n";
    }

    void updateCourse(int id) override {
        Course* course = findCourseById(id);
        if (course == nullptr) {
            throw std::invalid_argument("Course not found.");
        }

        printHeader();
        course->display();
        std::cout << "Which attribute do you want to update?\n";
        std::cout << "1. Update ID\n";
        std::cout << "2. Update Course Name\n";
        std::cout << "3. Update Type\n";
        int choice = DataValidInput::getIntInput("Please choose option (1-3): ");

        switch (choice) {
        case 1: {
            int newId = DataValidInput::getIntInput("Enter new ID: ");
            DataValidInput::validateId(newId);
            if (findCourseById(newId) != nullptr) {
                throw std::invalid_argument("New ID already exists.");
            }
            course->setId(newId);
            break;
        }
        case 2: {
            std::string newCourseName = DataValidInput::getStringInput("Enter new course name: ");
            course->setCourseName(newCourseName);
            break;
        }
        case 3: {
            int newType = DataValidInput::getIntInput("Enter 1 for Short-Course, 2 for Full-Course: ");
            if (newType == 1 && dynamic_cast<ShortCourse*>(course) == nullptr) {
                delete course;
                course = new ShortCourse(course->getCourseName(), course->getId());
            }
            else if (newType == 2 && dynamic_cast<FullCourse*>(course) == nullptr) {
                delete course;
                course = new FullCourse(course->getCourseName(), course->getId());
            }
            else {
                throw std::invalid_argument("Invalid course type.");
            }
            break;
        }
        default:
            std::cout << "Invalid choice.\n";
            break;
        }

        std::cout << "Course updated successfully.\n\n";
    }

    void deleteCourse(int id) override {
        auto it = std::remove_if(courses.begin(), courses.end(), [id](Course* course) {
            if (course->getId() == id) {
                delete course;
                return true;
            }
            return false;
            });

        if (it != courses.end()) {
            courses.erase(it, courses.end());
            std::cout << "Course deleted successfully.\n\n";
        }
        else {
            throw std::invalid_argument("Course not found.");
        }
    }

    void viewCourses() override {
        if (courses.empty()) {
            throw std::invalid_argument("No courses available.");
        }

        printHeader();
        for (const auto& course : courses) {
            course->display();
        }
        std::cout << std::endl;
    }

    void sortCourses() {
        std::cout << "Sort courses by:\n";
        std::cout << "1. ID\n";
        std::cout << "2. Name\n";
        int choice = DataValidInput::getIntInput("Enter your choice: ");

        switch (choice) {
        case 1:
            std::sort(courses.begin(), courses.end(), [](Course* a, Course* b) {
                return a->getId() < b->getId();
                });
            std::cout << "Courses sorted by ID.\n";
            break;
        case 2:
            std::sort(courses.begin(), courses.end(), [](Course* a, Course* b) {
                return a->getCourseName() < b->getCourseName();
                });
            std::cout << "Courses sorted by name.\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
        }
    }

    void saveToFile(const std::string& filename) const {
        std::ofstream outFile(filename);
        if (!outFile) {
            throw std::runtime_error("Cannot open file for writing.");
        }

        for (const auto& course : courses) {
            outFile << course->getId() << " " << course->getCourseName() << " " << course->getType() << std::endl;
        }

        std::cout << "Data saved successfully to " << filename << std::endl;
    }

    void loadFromFile(const std::string& filename) {
        std::ifstream inFile(filename);
        if (!inFile) {
            throw std::runtime_error("Cannot open file for reading.");
        }

        for (auto course : courses) {
            delete course;
        }
        courses.clear();

        int id;
        std::string name, type;
        bool hasCourses = false;

        while (inFile >> id >> name >> type) {
            if (type == "Short-Course") {
                courses.push_back(new ShortCourse(name, id));
                hasCourses = true;
            }
            else if (type == "Full-Course") {
                courses.push_back(new FullCourse(name, id));
                hasCourses = true;
            }
            else {
                throw std::runtime_error("Unknown course type in file.");
            }
        }

        if (!hasCourses) {
            std::cout << "No courses available in " << filename << std::endl;
        }
        else {
            std::cout << "Courses loaded successfully from " << filename << std::endl;
        }
    }

    Course* searchCourse(int id) const {
        Course* course = findCourseById(id);
        if (course == nullptr) {
            throw std::invalid_argument("Course not found.");
        }

        printHeader();
        course->display();
        std::cout << std::endl;

        return course;
    }
};
