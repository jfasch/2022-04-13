#include <userdb/userdb.h>
#include <cassert>


int main()
{
    UserDB db;
    db.insert(User(666, "Joerg", "Faschingbauer", "jfasch@home.com"));
    User u = db.find(666);

    assert(u.id == 666);
    assert(u.firstname == "Joerg");
    assert(u.lastname == "Faschingbauer");
    assert(u.email == "jfasch@home.com");

    return 0;
}
