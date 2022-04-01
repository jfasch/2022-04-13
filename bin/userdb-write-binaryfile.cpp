#include <userdb/userdb.h>

#include <iostream>


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " FILENAME" << std::endl;
        return 1;
    }
    std::string filename(argv[1]);

    User joerg(1, "Joerg", "Faschingbauer");
    User caro(2, "Caro", "Faschingbauer");
    User johanna(1, "Johanna", "Faschingbauer");
    User philipp(1, "Philipp", "Lichtenberger");

    UserDB db;
    db.insert(joerg);
    db.insert(caro);
    db.insert(johanna);
    db.insert(philipp);

    return 0;
}
