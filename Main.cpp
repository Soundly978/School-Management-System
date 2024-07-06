#include <iostream>
#include "School.cpp"

int main()
{
    try
    {
        // Create a School object and run the main program
        School school;
        school.run();
    }
    catch (const std::exception& e)
    {
        // Catch any exceptions and display the error message
        std::cerr << "An error occurred: " << e.what() << std::endl;
        return 1; // Return a non-zero value to indicate an error
    }

    return 0; // Return 0 to indicate successful execution
}
