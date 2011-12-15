#include "../include/people.h"

// Constructor
people::people(std::string firstname, std::string lastname){
    _firstname = firstname;
    _lastname = lastname;
}

void people::display(void){
    std::cout << "My name is " << _firstname << " " << _lastname << std::endl;
}
