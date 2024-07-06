#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <stdexcept>
#include "PartTimeStudent.cpp"
#include "FullTimeStudent.cpp"
#include "StudentManager.cpp"
#include "DataValidInput.cpp"

class StudentApplication
{
private:
    static void displayMenu()
    {
        std::cout << "=====================================" << std::endl;
        std::cout << "STUDENT MANAGER MENU: (Version 1.1.0)\n";
        std::cout << "=====================================" << std::endl;
        std::cout << "1. Add Student\n";
        std::cout << "2. View Student\n";
        std::cout << "3. Update Student\n";
        std::cout << "4. Delete Student\n";
        std::cout << "5. Search Student\n";
        std::cout << "6. Sort Student\n";
        std::cout << "7. Save Data\n";
        std::cout << "8. Lond Data\n";
        std::cout << "9. Back to Main Menu\n\n";
    }

public:
    static void run()
    {
        StudentManager manager;
        int choice;

        bool done = false;
        while (!done)
        {
            displayMenu();
            choice = DataValidInput::getIntInput("Enter your choice: ");
            std::cout << std::endl;
            try
            {
                switch (choice)
                {
                case 1:
                {
                    bool addMore = true; // Declaration of addMore
                    while (addMore)
                    {
                        std::string name;
                        int id;
                        int type;
                        std::cout << "==============" << std::endl;
                        std::cout << "1. Add Student" << std::endl;
                        std::cout << "==============" << std::endl;
                        id = DataValidInput::getIntInput("Enter student ID: ");
                        name = DataValidInput::getValidatedStringInput("Enter student name: ");
                        DataValidInput::validateId(id);
                        type = DataValidInput::getIntInput("Enter 1 for Part-Time, 2 for Full-Time: ");
                        manager.addStudent(id, name, type);

                        // Ask user a question to add more or not
                        char more;
                        more = DataValidInput::getCharInput("Do you want to add more students? (Y/N): ");
                        std::cout << std::endl;

                        if (more == 'N' || more == 'n')
                        {
                            addMore = false;
                        }
                    }

                    break;
                }
                case 2:
                    std::cout << "===============" << std::endl;
                    std::cout << "2. VIEW STUDENT" << std::endl;
                    std::cout << "===============" << std::endl;
                    manager.viewStudents();
                    break;
                case 3:
                {
                    int id;
                    std::cout << "=================" << std::endl;
                    std::cout << "3. UPDATE STUDENT" << std::endl;
                    std::cout << "=================" << std::endl;
                    std::cout << "Who do you want to update?\n";
                    id = DataValidInput::getIntInput("Please enter student ID: ");
                    DataValidInput::validateId(id);

                    manager.updateStudent(id);
                    break;
                }
                case 4:
                {
                    int id;
                    std::cout << "=================" << std::endl;
                    std::cout << "4. DELETE STUDENT" << std::endl;
                    std::cout << "=================" << std::endl;
                    std::cout << "Who do you want to delete?\n";
                    id = DataValidInput::getIntInput("Enter student ID: ");
                    std::cout << std::endl;
                    DataValidInput::validateId(id);

                    manager.deleteStudent(id);
                    break;
                }
                case 5:
                {
                    int id;
                    std::cout << "=================" << std::endl;
                    std::cout << "5. SEARCH STUDENT" << std::endl;
                    std::cout << "=================" << std::endl;
                    id = DataValidInput::getIntInput("Enter student ID: ");
                    std::cout << std::endl;
                    DataValidInput::validateId(id);

                    manager.searchStudent(id);
                    break;
                }
                case 6:
                {
                    std::cout << "===============" << std::endl;
                    std::cout << "6. SORT STUDENT" << std::endl;
                    std::cout << "===============" << std::endl;
                    manager.sortStudents();
                    break;
                }
                case 7:
                {
                    std::cout << "===============" << std::endl;
                    std::cout << "7. SAVE STUDENT" << std::endl;
                    std::cout << "===============" << std::endl;
                    manager.saveToFile("students.txt");
                    std::cout << "Data saved successfully" << std::endl;
                    break;
                }
                case 8:
                {
                    std::cout << "===============" << std::endl;
                    std::cout << "8. LOAD STUDENT" << std::endl;
                    std::cout << "===============" << std::endl;
                    manager.loadFromFile("students.txt");
                    std::cout << std::endl;
                    break;
                }
                case 9:
                    done = true;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again.\n";
                }
            }
            catch (const std::exception& e)
            {
                std::cout << "Error: " << e.what() << std::endl;
            }
        }
    }
};