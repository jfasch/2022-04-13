#include <userdb/userdb.h>


int main()
{
    UserDB db;
    db.insert(User(666, "Joerg", "Faschingbauer", "jfasch@home.com"));
    

    return 0;
}
