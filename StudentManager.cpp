#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include "PartTimeStudent.cpp"
#include "FullTimeStudent.cpp"
#include "StudentRepository.cpp"
#include "DataValidInput.cpp"

class StudentManager : public StudentRepository
{
private:
    std::vector<Student*> students;

    Student* findStudentById(int id)
    {
        auto it = std::find_if(students.begin(), students.end(), [id](Student* student)
            { return student->getId() == id; });
        return (it != students.end()) ? *it : nullptr;
    }

    void printHeader() const
    {
        const int width = 20;
        std::cout << std::left << std::setw(width) << "Name"
            << std::left << std::setw(width) << "ID"
            << std::left << std::setw(width) << "Type"
            << std::endl;
    }

public:
    ~StudentManager()
    {
        for (auto student : students)
        {
            delete student;
        }
    }

    void addStudent(int id, const std::string& name, int type)
    {
        if (findStudentById(id) != nullptr)
        {
            throw std::invalid_argument("Student ID already exists.");
        }

        if (type == 1)
        {
            students.push_back(new PartTimeStudent(name, id));
        }
        else if (type == 2)
        {
            students.push_back(new FullTimeStudent(name, id));
        }
        else
        {
            throw std::invalid_argument("Invalid student type.");
        }

        std::cout << "Student added successfully.\n\n";
    }

    void updateStudent(int id)
    {
        Student* student = findStudentById(id);
        if (student == nullptr)
        {
            throw std::invalid_argument("Student not found.");
        }

        printHeader();
        student->display();
        std::cout << "\nWhich attribute do you want to update?\n";
        std::cout << "1. ID\n";
        std::cout << "2. Name\n";
        std::cout << "3. Type\n";
        int choice = DataValidInput::getIntInput("Enter your choice (1-3): ");

        switch (choice)
        {
        case 1:
        {
            int newId = DataValidInput::getIntInput("Enter new ID: ");
            DataValidInput::validateId(newId);
            if (findStudentById(newId) != nullptr)
            {
                throw std::invalid_argument("New ID already exists.");
            }
            student->setId(newId);
            break;
        }
        case 2:
        {
            std::string newName = DataValidInput::getValidatedStringInput("Enter new name: ");
            student->setName(newName);
            break;
        }
        case 3:
        {
            int newType = DataValidInput::getIntInput("Enter new type (1 for Part-Time, 2 for Full-Time): ");
            if (newType == 1)
            {
                if (typeid(*student) != typeid(PartTimeStudent))
                {
                    delete student;
                    student = new PartTimeStudent(student->getName(), student->getId());
                    students.push_back(student);
                }
            }
            else if (newType == 2)
            {
                if (typeid(*student) != typeid(FullTimeStudent))
                {
                    delete student;
                    student = new FullTimeStudent(student->getName(), student->getId());
                    students.push_back(student);
                }
            }
            else
            {
                throw std::invalid_argument("Invalid student type.");
            }
            break;
        }
        default:
            std::cout << "Invalid choice.\n";
            break;
        }

        std::cout << "Student updated successfully.\n\n";
    }

    void deleteStudent(int id)
    {
        auto it = std::remove_if(students.begin(), students.end(), [id](Student* student)
            {
                if (student->getId() == id)
                {
                    delete student;
                    return true;
                }
                return false;
            });

        if (it != students.end())
        {
            students.erase(it, students.end());
            std::cout << "Student deleted successfully.\n\n";
        }
        else
        {
            throw std::invalid_argument("Student not found.");
        }
    }

    void viewStudents()
    {
        if (students.empty())
        {
            throw std::invalid_argument("No students available.");
        }

        printHeader();
        for (const auto& student : students)
        {
            student->display();
        }
        std::cout << std::endl;
    }

    void searchStudent(int id)
    {
        Student* student = findStudentById(id);
        if (student == nullptr)
        {
            throw std::invalid_argument("Student not found.");
        }

        printHeader();
        student->display();
        std::cout << std::endl;
    }

    void sortStudents()
    {
        std::cout << "Sort students by:\n";
        std::cout << "1. ID\n";
        std::cout << "2. Name\n";
        int choice = DataValidInput::getIntInput("Enter your choice (1-2): ");

        switch (choice)
        {
        case 1:
            std::sort(students.begin(), students.end(), [](Student* a, Student* b)
                { return a->getId() < b->getId(); });
            std::cout << "Students sorted by ID.\n\n";
            break;
        case 2:
            std::sort(students.begin(), students.end(), [](Student* a, Student* b)
                { return a->getName() < b->getName(); });
            std::cout << "Students sorted by name.\n\n";
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
        }

        printHeader();
        for (const auto& student : students)
        {
            student->display();
        }
        std::cout << std::endl;
    }

    void saveToFile(const std::string& filename) const
    {
        std::ofstream outFile(filename);
        if (!outFile)
        {
            throw std::runtime_error("Cannot open file for writing.");
        }

        for (const auto& student : students)
        {
            outFile << student->getId() << " " << student->getName() << " " << student->getType() << std::endl;
        }

        std::cout << "Data saved successfully.\n\n";
    }

    void loadFromFile(const std::string& filename)
    {
        std::ifstream inFile(filename);
        if (!inFile)
        {
            throw std::runtime_error("Cannot open file for reading.");
        }

        students.clear();
        int id;
        std::string name, type;

        while (inFile >> id >> name >> type)
        {
            if (type == "Part-Time")
            {
                students.push_back(new PartTimeStudent(name, id));
            }
            else if (type == "Full-Time")
            {
                students.push_back(new FullTimeStudent(name, id));
            }
            else
            {
                throw std::runtime_error("Unknown student type in file.");
            }
        }

        std::cout << "Data loaded successfully.\n\n";
    }
};
