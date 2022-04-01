#include "user.h"


User::User(
    unsigned int id, 
    const std::string& firstname, 
    const std::string& lastname)
: id(id),
  firstname(firstname),
  lastname(lastname)
{}
