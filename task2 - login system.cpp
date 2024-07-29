#include <iostream>
#include <string>
#include <fstream>

using namespace std;

class person {
    string username;
    string pw;

public:
    void registeruser() {
        cout << "Enter a username: ";
        cin >> username;

        cout << "Enter a password: ";
        cin >> pw;

        ofstream file;
        file.open(username + ".txt");
        if (file.is_open()) {
            file << username << endl;
            file << pw << endl;
            file.close();
            cout << "New user registered successfully.\n";
        } else {
            cout << "Error registering user. Please try again.\n";
        }
    }

    bool login() {
        cout << "Enter valid username: ";
        cin >> username;
        cout << "Enter password: ";
        cin >> pw;

        ifstream file(username + ".txt");
        if (!file.is_open()) {
            cout << "Entered username is incorrect. Please try again or register the user first.\n";
            return false;
        }

        string fileun, filepw;
        getline(file, fileun);
        getline(file, filepw);

        if (username == fileun && pw == filepw) {
            cout << "Login succeeded!\n";
            return true;
        } else {
            cout << "Incorrect password.\n";
            return false;
        }
    }
};

int main() {
    cout << "Login and registration system\n\n";
    person u;
    int choice;

    do {
        cout << "1. Login existing user\n2. Register new user\n3. Exit\n\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                u.login();
                break;
            case 2:
                u.registeruser();
                break;
            case 3:
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 3);

}
