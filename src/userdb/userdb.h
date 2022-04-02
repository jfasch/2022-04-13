#ifndef USERDB_USERDB_H
#define USERDB_USERDB_H

#include "user.h"
#include <map>

class UserDB
{
public:
    using store = std::map<unsigned int, User>;
    struct UserDB_iterator
    {
        store::const_iterator _impl;

        UserDB_iterator(store::const_iterator it) : _impl(it) {}
        bool operator!=(const UserDB_iterator& other) const { 
            return _impl!=other._impl; 
        }
        const User& operator*() const {
            return _impl->second;
        }
        UserDB_iterator& operator++() {
            ++_impl;
            return *this;
        }
    };

public:
    void insert(const User&);
    const User& find(unsigned int id) const;
    void write(const std::string& filename);
    void read(const std::string& filename);
    void write_csv(const std::string& filename);
    void read_csv(const std::string& filename);

    UserDB_iterator begin() { return UserDB_iterator(_store.begin()); }
    UserDB_iterator end() { return UserDB_iterator(_store.end()); }

private:
    store _store;
};

#endif
