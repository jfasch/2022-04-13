#ifndef USERDB_USER_H
#define USERDB_USER_H

#include <string>

struct User
{
    User(unsigned int id, 
         const std::string& firstname, const std::string& lastname,
         const std::string& email)
    : id(id),
      firstname(firstname),
      lastname(lastname),
      email(email)
    {}

    unsigned int id;
    std::string firstname;
    std::string lastname;
    std::string email;
};

#endif
