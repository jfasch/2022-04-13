#include <userdb/userdb.h>


int main(void)
{
    User joerg(1, "Joerg", "Faschingbauer");
    User caro(2, "Caro", "Faschingbauer");
    User johanna(1, "Johanna", "Faschingbauer");
    User philipp(1, "Philipp", "Lichtenberger");

    UserDB db;
    db.insert(std::make_pair(joerg.id, joerg));
    db.insert(std::make_pair(caro.id, joerg));
    db.insert(std::make_pair(johanna.id, joerg));
    db.insert(std::make_pair(philipp.id, joerg));

    return 0;
}
