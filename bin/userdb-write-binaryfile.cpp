#include <userdb/userdb.h>

#include <iostream>

using std::cout;
using std::cin;
using std::cerr;
using std::endl;
using std::string;
using std::stoul;


int main(int argc, char** argv)
{
    if (argc != 3) {
        std::cerr << "Usage: " << argv[0] << " TYPE FILENAME" << std::endl;
        std::cerr << "   TYPE ... \"binary\" or \"text\"" << std::endl;
        return 1;
    }
    std::string type(argv[1]);
    std::string filename(argv[2]);

    bool binary;
    if (type == "binary")
        binary = true;
    else if (type == "text")
        binary = false;
    else {
        std::cerr << "Bad type: " << type << std::endl;
        return 1;
    }

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
        cout << "another round (y/n): ";
        cin >> yesno;
        if (yesno == "n")
            break;
    }

    db.write(filename, binary);

    return 0;
}
