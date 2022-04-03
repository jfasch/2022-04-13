#include <userdb/userdb.h>

#include <iostream>

using std::cout;
using std::endl;


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " FILENAME" << std::endl;
        return 1;
    }
    std::string filename(argv[1]);

    UserDB db;
    db.read(filename);

    for (auto u: db) {
        cout << u.id << ',' << u.firstname << ',' << u.lastname << ',' << u.email << endl;
    }

    return 0;
}
