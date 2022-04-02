#include <userdb/userdb.h>
#include <cassert>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <cstring>

#include <iostream>

using std::cerr;
using std::endl;


int test_write_csv()
{
    static std::string EXPECTED_CONTENT = "666;Joerg;Faschingbauer;jfasch@home.com\n";

    UserDB db;
    db.insert(User(666, "Joerg", "Faschingbauer", "jfasch@home.com"));

    char filename[] = "test-csv-XXXXXX";
    int fd = mkstemp(filename);
    db.write_csv(filename);
    
    struct stat s;
    int error = stat(filename, &s);
    assert(!error);
    assert((unsigned)s.st_size == EXPECTED_CONTENT.size());

    char* buffer = new char[s.st_size+1];
    ssize_t nread = read(fd, buffer, s.st_size);
    assert(nread == s.st_size);
    buffer[s.st_size] = 0;

    assert(strcmp(EXPECTED_CONTENT.c_str(), buffer) == 0);

    close(fd);
    unlink(filename);

    return 0;
}

int test_read_csv()
{
    static std::string CONTENT = "666;Joerg;Faschingbauer;jfasch@home.com\n"
                                 "42;Caro;Faschingbauer;caro@home.com\n";
    char tmpfile[] = "test_read_csv-XXXXXX";
    int fd = mkstemp(tmpfile);
    ssize_t nwritten = write(fd, CONTENT.c_str(), CONTENT.size());
    assert((unsigned)nwritten == CONTENT.size());
    
    UserDB db;
    db.read_csv(tmpfile);

    User jfasch = db.find(666);
    User caro = db.find(42);

    assert(jfasch.id == 666);
    assert(jfasch.firstname == "Joerg");
    assert(jfasch.lastname == "Faschingbauer");
    assert(jfasch.email == "jfasch@home.com");

    assert(caro.id == 42);
    assert(caro.firstname == "Caro");
    assert(caro.lastname == "Faschingbauer");
    assert(caro.email == "caro@home.com");

    close(fd);
    unlink(tmpfile);

    return 0;
}

int main()
{
    int result = test_write_csv();
    if (result != 0)
        return result;
    result = test_read_csv();
    if (result != 0)
        return result;
    return 0;
}
