#ifndef USERDB_USER_H
#define USERDB_USER_H

#include <string>

struct User
{
    User(unsigned int id, const std::string& firstname, const std::string& lastname);
    unsigned int id;
    std::string firstname;
    std::string lastname;
};

#endif
