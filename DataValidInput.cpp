#pragma once

#include <iostream>
#include <string>
#include <limits>
#include <cctype>

class DataValidInput {
public:
    static void validateId(int id) {
        if (id <= 0) {
            throw std::invalid_argument("ID must be a positive integer.");
        }
    }

    static std::string getStringInput(const std::string& prompt) {
        std::string input;
        std::cout << prompt;
        std::getline(std::cin, input);
        return input;
    }

    static int getIntInput(const std::string& prompt) {
        int input;
        std::cout << prompt;
        while (!(std::cin >> input)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter an integer: ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return input;
    }

    static char getCharInput(const std::string& prompt) {
        char input;
        std::cout << prompt;
        while (!(std::cin >> input) || (std::toupper(input) != 'Y' && std::toupper(input) != 'N')) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input. Please enter 'Y' or 'N': ";
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return std::toupper(input);
    }

    static std::string getValidatedStringInput(const std::string& prompt) {
        std::string input;
        while (true) {
            std::cout << prompt;
            std::getline(std::cin, input);
            if (isAlphaString(input)) {
                break;
            }
            else {
                std::cout << "Invalid input. Please enter only alphabetic characters and spaces." << std::endl;
            }
        }
        return input;
    }

private:
    static bool isAlphaString(const std::string& str) {
        for (char c : str) {
            if (!std::isalpha(c) && c != ' ') {
                return false;
            }
        }
        return true;
    }
};
