#include "user.h"


User::User(
    unsigned int id, 
    const std::string& firstname, const std::string& lastname,
    const std::string& email)
: id(id),
  firstname(firstname),
  lastname(lastname),
  email(email)
{}
