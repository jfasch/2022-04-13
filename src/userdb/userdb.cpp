#include "userdb.h"

#include <fstream>
#include <cstdint>
#include <cstring>
#include <arpa/inet.h>

using std::ofstream;
using std::string;


void UserDB::insert(const User& u)
{
    _store.insert(std::make_pair(u.id, u));
}

struct BinaryUser
{
    uint32_t id;
    char firstname[10];
    char lastname[10];
    char email[20];
};

void UserDB::write(const string& filename)
{
    ofstream f(filename);

    for (const auto& x: _store) {
        const User& u = x.second;

        BinaryUser bu;
        bu.id = htonl(u.id);
        strcpy(bu.firstname, u.firstname.c_str());
        strcpy(bu.lastname, u.lastname.c_str());
        strcpy(bu.email, u.email.c_str());

        f.write((const char*)&bu, sizeof(bu));
    }
}
