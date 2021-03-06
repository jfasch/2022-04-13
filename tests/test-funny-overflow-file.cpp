#include <userdb/userdb.h>

#include <gtest/gtest.h>

#include <cassert>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>

using std::cerr;
using std::endl;


TEST(BinaryFormatSuite, FunnyOverflow)
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

    ASSERT_EQ(u.id, 666);
    ASSERT_EQ(u.firstname, "Joerg");
    ASSERT_EQ(u.lastname, "Faschingb");  // sigh, documenting a bug as a feature
    ASSERT_EQ(u.email, "jfasch@home.com");

    close(fd);
    unlink(tmpname);
}
