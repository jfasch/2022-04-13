#include "userdb.h"

#include <iostream>
#include <cstdint>
#include <cstring>
#include <cassert>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <arpa/inet.h>

using std::ofstream;
using std::ifstream;
using std::string;
using std::cout;
using std::cerr;
using std::endl;


struct BinaryUser
{
    uint32_t id;
    char firstname[10];
    char lastname[10];
    char email[20];
};

void UserDB::insert(const User& u)
{
    _store.insert(std::make_pair(u.id, u));
}

const User& UserDB::find(unsigned int id) const
{
    store::const_iterator found = _store.find(id);
    assert(found != _store.cend()); // this is intentional
    return found->second;
}

void UserDB::write(const string& filename)
{
    int fd = open(filename.c_str(), O_WRONLY|O_TRUNC);
    assert(fd >= 0);

    for (const auto& x: _store) {
        const User& u = x.second;

        BinaryUser bu;
        bu.id = htonl(u.id);
        strcpy(bu.firstname, u.firstname.c_str());
        strcpy(bu.lastname, u.lastname.c_str());
        strcpy(bu.email, u.email.c_str());

        ssize_t nwritten = ::write(fd, &bu, sizeof(bu));
        assert(nwritten == sizeof(bu));
    }

    close(fd);
}

void UserDB::read(const string& filename)
{
    int fd = open(filename.c_str(), O_RDONLY);
    assert(fd >= 0);

    for (;;) {
        BinaryUser bu;
        ssize_t nread = ::read(fd, &bu, sizeof(bu));
        if (nread == 0)
            break;
        assert(nread == sizeof(bu));
        User u(ntohl(bu.id),
               bu.firstname,
               bu.lastname,
               bu.email);
        insert(u);
    }
}
