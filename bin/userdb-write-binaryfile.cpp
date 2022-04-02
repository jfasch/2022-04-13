#include <userdb/userdb.h>

#include <iostream>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stoul;


int main(int argc, char** argv)
{
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " FILENAME" << std::endl;
        return 1;
    }
    std::string filename(argv[1]);

    UserDB db;

    while (cin) {
        string id, fn, ln, email;
        cout << "ID: ";
        cin >> id;
        cout << "Firstname: ";
        cin >> fn;
        cout << "Lastname: ";
        cin >> ln;
        cout << "Email: ";
        cin >> email;

        db.insert(User(stoul(id), fn, ln, email));

        string yesno;
        cout << "another round (y/n): " << endl;
        cin >> yesno;
        if (yesno == "n")
            break;
    }

    db.write(filename);

    return 0;
}
