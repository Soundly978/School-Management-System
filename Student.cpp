#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include <iomanip>

class Student
{
protected:
    std::string name;
    int id;


public:
    Student(const std::string& name, int id) : name(name), id(id) {}

    virtual ~Student() = default;

    std::string getName() const
    {
        return name;
    }

    void setName(const std::string& name)
    {
        this->name = name;
    }

    int getId() const
    {
        return id;
    }

    void setId(int id)
    {
        this->id = id;
    }

    virtual std::string getType() const = 0;

    void printHeader() const
    {
        const int width = 20;
        std::cout << std::left << std::setw(width) << "Name"
            << std::left << std::setw(width) << "ID"
            << std::left << std::setw(width) << "Type"
            << std::endl;
    }

    virtual void display() const
    {
        const int width = 20;
        std::cout << std::left << std::setw(width) << name
            << std::left << std::setw(width) << id
            << std::left << std::setw(width) << getType()
            << std::endl;
    }
};

