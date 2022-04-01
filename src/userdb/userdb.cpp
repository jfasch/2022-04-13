#include "userdb.h"

void UserDB::insert(const User& u)
{
    _store.insert(std::make_pair(u.id, u));
}

