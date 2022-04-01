#ifndef USERDB_USERDB_H
#define USERDB_USERDB_H

#include "user.h"
#include <map>

class UserDB
{
public:
    void insert(const User&);
    void write(const std::string& filename);
private:
    std::map<unsigned int, User> _store;
};

#endif
