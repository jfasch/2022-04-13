#include <userdb/userdb.h>

#include <iostream>


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " FILENAME" << std::endl;
        return 1;
    }
    std::string filename(argv[1]);

    User joerg(1, "Joerg", "Huber", "joerg@home.com");
    User caro(2, "Caro", "Huber", "caro@home.com");
    User johanna(1, "Johanna", "Huber", "johanna@home.com");
    User philipp(1, "Philipp", "Huber", "philipp@home.com");

    UserDB db;
    db.insert(joerg);
    db.insert(caro);
    db.insert(johanna);
    db.insert(philipp);

    db.write(filename);

    return 0;
}
