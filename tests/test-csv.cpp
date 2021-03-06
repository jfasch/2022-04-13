#include "tempfile.h"

#include <userdb/userdb.h>

#include <gtest/gtest.h>

#include <cassert>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <cstring>

#include <iostream>

using std::cerr;
using std::endl;

static std::string read_file(const std::string& filename)
{
    struct stat s;
    int error = stat(filename.c_str(), &s);
    assert(!error);

    int fd = open(filename.c_str(), O_RDONLY);

    char* buffer = new char[s.st_size+1];
    ssize_t nread = read(fd, buffer, s.st_size);
    assert(nread == s.st_size);
    buffer[s.st_size] = 0;

    close(fd);

    return std::string(buffer, s.st_size);
}

class CSVFormatSuite : public TempfileFixture {};

TEST_F(CSVFormatSuite, Write)
{
    static std::string EXPECTED_CONTENT = "666;Joerg;Faschingbauer;jfasch@home.com\n";

    UserDB db;
    db.insert(User(666, "Joerg", "Faschingbauer", "jfasch@home.com"));
    db.write(tempname, false);
    
    std::string content = read_file(tempname);
    ASSERT_EQ(content, EXPECTED_CONTENT);
}

TEST_F(CSVFormatSuite, Read)
{
    static std::string CONTENT = "666;Joerg;Faschingbauer;joerg@home.com\n"
                                 "42;Caro;Faschingbauer;caro@home.com\n";
    ssize_t nwritten = write(tempfd, CONTENT.c_str(), CONTENT.size());
    ASSERT_EQ((unsigned)nwritten, CONTENT.size());
    
    UserDB db;
    db.read(tempname, false);

    User joerg = db.find(666);
    User caro = db.find(42);

    ASSERT_EQ(joerg.id, 666);
    ASSERT_EQ(joerg.firstname, "Joerg");
    ASSERT_EQ(joerg.lastname, "Faschingbauer");
    ASSERT_EQ(joerg.email, "joerg@home.com");

    ASSERT_EQ(caro.id, 42);
    ASSERT_EQ(caro.firstname, "Caro");
    ASSERT_EQ(caro.lastname, "Faschingbauer");
    ASSERT_EQ(caro.email, "caro@home.com");
}

