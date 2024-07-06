#pragma once

#include <iostream>
#include <fstream>
#include <iomanip>
#include <limits>
#include "StudentApplication.cpp"
#include "Course Application.cpp"
#include "DataValidInput.cpp"

using namespace std;

static void displayMenu()
{
    std::cout << "============================" << std::endl;
    std::cout << "[MAIN MENU: (Version 1.0.0)]\n";
    std::cout << "============================" << std::endl;
    std::cout << "1. Student Management\n";
    std::cout << "2. Course Management\n";
    std::cout << "0. Exit\n";
}

class School
{
public:
    bool login()
    {
        const std::string correctUsername = "Test";
        const std::string correctPassword = "1234";
        const int maxAttempts = 5;
        int attempts = 0;

        std::string username;
        std::string password;

        while (attempts < maxAttempts)
        {
            std::cout << std::endl;
            std::cout << "[SCHOOL INFORMATION SYSTEM]" << std::endl;
            std::cout << "==========================" << std::endl;
            std::cout << "Welcome to log in Section: " << std::endl;
            std::cout << "==========================" << std::endl
                << std::endl;
            std::cout << "Enter username: ";
            std::getline(std::cin, username);
            std::cout << "Enter password: ";
            std::getline(std::cin, password);
            std::cout << std::endl;

            if (username == correctUsername && password == correctPassword)
            {
                std::cout << "You have logged in successfully.\n " << std::endl;

                return true;
            }
            else
            {
                attempts++;
                std::cout << "Invalid login credentials. Attempt " << attempts << " of " << maxAttempts << ".\n\n";
            }
        }

        return false;
    }

public:
    void run()
    {
        if (!login())
        {
            std::cout << "Maximum login attempts reached. Exiting...\n";
            return;
        }

        int choice;
        cout.setf(ios::fixed | ios::showpoint);
        cout << setprecision(2);

        do
        {
            displayMenu();
            std::cout << std::endl;
            choice = DataValidInput::getIntInput("Enter your choice: ");
            switch (choice)
            {
            case 1:
                StudentApplication studentApp;
                studentApp.run();
                break;
            case 2:
                CourseApplication courseApp;
                courseApp.run();
                break;
            case 0:

                break;
            default:

                cout << "\aInvalid choice. Please try again.\n";
            }
        } while (choice != 0);
    }
};
