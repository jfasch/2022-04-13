#include <userdb/userdb.h>
#include <cassert>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using std::cerr;
using std::endl;


int main()
{
    char tmpname[] = "test-funny-overflow-file-XXXXXX";
    int fd = mkstemp(tmpname);

    {
        UserDB dbtmp;
        dbtmp.insert(User(666, "Joerg", "Faschingbauer", "jfasch@home.com"));
        dbtmp.write(tmpname);
    }

    UserDB db;
    db.read(tmpname);
    User u = db.find(666);

    assert(u.id == 666);
    assert(u.firstname == "Joerg");
    assert(u.lastname == "Faschingb");  // sigh, documenting a bug as
                                        // a feature
    assert(u.email == "jfasch@home.com");

    close(fd);
    unlink(tmpname);

    return 0;
}
