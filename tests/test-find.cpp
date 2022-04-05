#include <gtest/gtest.h>
#include <userdb/userdb.h>


TEST(UserDBSuite, Find)
{
    UserDB db;
    db.insert(User(666, "Joerg", "Faschingbauer", "jfasch@home.com"));
    User u = db.find(666);

    ASSERT_EQ(u.id, 666);
    ASSERT_EQ(u.firstname, "Joerg");
    ASSERT_EQ(u.lastname, "Faschingbauer");
    ASSERT_EQ(u.email, "jfasch@home.com");
}
