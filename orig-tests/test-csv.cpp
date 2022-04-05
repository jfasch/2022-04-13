#include <userdb/userdb.h>
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


int test_write_csv()
{
    static std::string EXPECTED_CONTENT = "666;Joerg;Faschingbauer;jfasch@home.com\n";

    char filename[] = "test-csv-XXXXXX";
    int fd = mkstemp(filename);

    UserDB db;
    db.insert(User(666, "Joerg", "Faschingbauer", "jfasch@home.com"));
    db.write(filename, false);
    
    std::string content = read_file(filename);
    assert(content == EXPECTED_CONTENT);

    close(fd);
    unlink(filename);

    return 0;
}

int test_read_csv()
{
    static std::string CONTENT = "666;Joerg;Faschingbauer;joerg@home.com\n"
                                 "42;Caro;Faschingbauer;caro@home.com\n";
    char tmpfile[] = "test_read_csv-XXXXXX";
    int fd = mkstemp(tmpfile);
    ssize_t nwritten = write(fd, CONTENT.c_str(), CONTENT.size());
    assert((unsigned)nwritten == CONTENT.size());
    
    UserDB db;
    db.read(tmpfile, false);

    User joerg = db.find(666);
    User caro = db.find(42);

    assert(joerg.id == 666);
    assert(joerg.firstname == "Joerg");
    assert(joerg.lastname == "Faschingbauer");
    assert(joerg.email == "joerg@home.com");

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
