#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void UserRegistration()
{
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    string filename = username + ".txt";
    ofstream file(filename.c_str());
    if (file.is_open())
    {
        file << "username : " << username << " " << "password : " << password << endl;
        file.close();
        cout << "Registration successful! User file created: " << filename << endl;
    }
    else
    {
        cout << "Unable to open file for writing." << endl;
    }
}

bool UserLogin()
{
    string username, password, u, p;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    string filename = username + ".txt";
    ifstream file(filename.c_str());
    if (file.is_open())
    {
        file >> u >> p;
        file.close();
        if (u == username && p == password)
        {
            return true;
        }
    }
    else
    {
        cout << "User not found. Please register first." << endl;
    }

    return false;
}

int main()
{
    int choice;
    cout << "Login and Registration System" << endl;
    cout << "1. Register\n2. Login\n3. Exit\n";
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        UserRegistration();
        break;
    case 2:
        if (UserLogin())
        {
            cout << "Login Successful." << endl;
        }
        else
        {
            cout << "Invalid credentials." << endl;
        }
        break;
    case 3:
        exit(0);
    default:
        cout << "Invalid choice. Please try again." << endl;
    }
    return 0;
}
