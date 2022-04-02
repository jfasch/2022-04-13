#include <userdb/userdb.h>
#include <string>
#include <iostream>


int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " FILENAME ID" << std::endl;
        return 1;
    }
    std::string filename(argv[1]);
    unsigned int id = std::stoul(argv[2]);

    UserDB db;
    db.read(filename);

    User u = db.find(id);
    std::cout << u.id << ',' << u.firstname << ',' << u.lastname << ',' << u.email << std::endl;

    return 0;
}
