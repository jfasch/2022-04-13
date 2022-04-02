#include <userdb/userdb.h>
#include <cassert>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using std::cerr;
using std::endl;


int main()
{
    char tmpname[] = "test-truncate-on-overflow-file-XXXXXX";
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
    assert(u.lastname == "Faschingb");  // name too long, truncated to
                                        // 9 chars
    assert(u.email == "jfasch@home.com");

    close(fd);

    return 0;
}
