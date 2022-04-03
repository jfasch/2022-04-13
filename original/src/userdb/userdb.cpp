#include "userdb.h"

#include <iostream>
#include <fstream>
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

void UserDB::write(const string& filename, bool binary)
{
    if (binary) {
        int fd = open(filename.c_str(), O_WRONLY|O_TRUNC);
        assert(fd >= 0);

        for (const auto& x: _store) {
            const User& u = x.second;

            BinaryUser bu;
            bu.id = htonl(u.id);
            strncpy(bu.firstname, u.firstname.c_str(), 10);
            strncpy(bu.lastname, u.lastname.c_str(), 10);
            strncpy(bu.email, u.email.c_str(), 20);
            bu.firstname[9] = '\0';
            bu.lastname[9] = '\0';
            bu.email[19] = '\0';

            ssize_t nwritten = ::write(fd, &bu, sizeof(bu));
            assert(nwritten == sizeof(bu));
        }

        close(fd);
    }
    else {
        ofstream f(filename);
        for (const auto& u: *this)
            f << u.id << ';' << u.firstname << ';' << u.lastname << ';' << u.email << '\n';
    }
}

void UserDB::read(const string& filename, bool binary)
{
    if (binary) {
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
    else {
        ifstream f(filename);
        string line;
        while (getline(f, line)) {
            int lastpos = 0;

            auto pos = line.find(';', lastpos);
            string id = line.substr(lastpos, pos-lastpos);
            lastpos = pos+1;

            pos = line.find(';', lastpos);
            string firstname = line.substr(lastpos, pos-lastpos);
            lastpos = pos+1;

            pos = line.find(';', lastpos);
            string lastname = line.substr(lastpos, pos-lastpos);
            lastpos = pos+1;

            string email = line.substr(lastpos);

            insert(User(std::stoul(id), firstname, lastname, email));
        }
    }
}
