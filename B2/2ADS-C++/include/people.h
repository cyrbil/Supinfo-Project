#ifndef PEOPLE_H
#define PEOPLE_H

#include <iostream>

class people
{
    protected:
        std::string _lastname;
        std::string _firstname;
    public:
        // Constructor
        people(std::string firstname = "John", std::string lastname = "Doe");
        // Display name to cout
        void display(void);
        // Getters
        std::string Get_lastname(void) { return _lastname; }
        std::string Get_firstname(void) { return _firstname; }
};

#endif // PEOPLE_H
