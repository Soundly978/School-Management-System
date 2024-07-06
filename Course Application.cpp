#include <iostream>
#include <stdexcept>
#include "CourseManager.cpp"
#include "DataValidInput.cpp"

class CourseApplication
{
private:
    static void displayMenu()
    {
        std::cout << "======================================" << std::endl;
        std::cout << "Course Manager Menu: (Version 1.1.0)\n";
        std::cout << "======================================" << std::endl;
        std::cout << "1. Add Course\n";
        std::cout << "2. View Course\n";
        std::cout << "3. Update Course\n";
        std::cout << "4. Delete Course\n";
        std::cout << "5. Search Courses\n";
        std::cout << "6. Sort Course\n";
        std::cout << "7. Save Data\n";
        std::cout << "8. Load Data\n";
        std::cout << "9. Back to Main Menu\n";
    }

    static void addCourse(CourseManager& manager)
    {
        bool addMore = true;
        while (addMore)
        {
            std::string courseName = DataValidInput::getStringInput("Enter course name: ");
            int id = DataValidInput::getIntInput("Enter Course ID: ");
            DataValidInput::validateId(id);

            int type = DataValidInput::getIntInput("Enter 1 for Short-Course, 2 for Full-Course: ");
            manager.addCourse(id, courseName, type);

            char more = DataValidInput::getCharInput("Do you want to add more courses? (Y/N): ");
            if (more == 'N' || more == 'n')
            {
                addMore = false;
            }
        }
    }

    static void updateCourse(CourseManager& manager)
    {
        int id = DataValidInput::getIntInput("Enter Course ID: ");
        DataValidInput::validateId(id);
        manager.updateCourse(id);
    }

    static void deleteCourse(CourseManager& manager)
    {
        int id = DataValidInput::getIntInput("Enter Course ID: ");
        DataValidInput::validateId(id);
        manager.deleteCourse(id);
    }

    static void searchCourse(CourseManager& manager)
    {
        int id = DataValidInput::getIntInput("Enter Course ID to search: ");
        DataValidInput::validateId(id);
        manager.searchCourse(id);
    }

public:
    static void run()
    {
        CourseManager manager;
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
                    std::cout << "=============" << std::endl;
                    std::cout << "1. ADD COURSE" << std::endl;
                    std::cout << "=============" << std::endl;
                    addCourse(manager);
                    break;
                case 2:
                    std::cout << "2. VIEW COURSE" << std::endl;
                    manager.viewCourses();
                    break;
                case 3:
                    std::cout << "================" << std::endl;
                    std::cout << "3. UPDATE COURSE" << std::endl;
                    std::cout << "================" << std::endl;
                    updateCourse(manager);
                    break;
                case 4:
                    std::cout << "================" << std::endl;
                    std::cout << "4. DELETE COURSE" << std::endl;
                    std::cout << "================" << std::endl;
                    deleteCourse(manager);
                    break;
                case 5:
                    std::cout << "================" << std::endl;
                    std::cout << "5. SEARCH COURSE" << std::endl;
                    std::cout << "================" << std::endl;
                    searchCourse(manager);
                    break;
                case 6:
                    std::cout << "===============" << std::endl;
                    std::cout << "6. SORT COURSES" << std::endl;
                    std::cout << "===============" << std::endl;
                    manager.sortCourses();
                    break;
                case 7:
                    std::cout << "===============" << std::endl;
                    std::cout << "7. SAVE COURSES" << std::endl;
                    std::cout << "===============" << std::endl;
                    manager.saveToFile("courses.txt");
                    std::cout << "Data saved successfully" << std::endl;
                    break;
                case 8:
                    std::cout << "===============" << std::endl;
                    std::cout << "8. LOAD COURSE" << std::endl;
                    std::cout << "===============" << std::endl;
                    manager.loadFromFile("courses.txt");
                    std::cout << std::endl;
                    break;
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
