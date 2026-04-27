#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
using namespace std;

class Login
{
private:
    string LoginID, Password;

public:
    void setID(string id) 
    { 
        LoginID = id; 
    }
    void setPW(string pw) 
    {
         Password = pw; 
    }

    string getID()
     {
         return LoginID;
     }
    string getPW()
     {
         return Password;
     }
};

// check user exists
bool isUserExists(string id)
{
    ifstream infile("Login.txt");
    string line;

    while (getline(infile, line))
    {
        stringstream ss(line);
        string uid, pw;

        getline(ss, uid, ':');
        getline(ss, pw);

        if (uid == id)
            return true;
    }
    return false;
}

// register
void registration()
{
    system("cls");

    string id, pw;
    cout << "\tEnter Login ID: ";
    cin >> id;

    if (isUserExists(id))
    {
        cout << "\tUser already exists!\n";
        Sleep(1500);
        return;
    }

    do
    {
        cout << "\tEnter Password (min 8 chars): ";
        cin >> pw;

        if (pw.length() < 8)
            cout << "\tToo short!\n";

    } while (pw.length() < 8);

    ofstream outfile("Login.txt", ios::app);
    outfile << id << ":" << pw << endl;

    cout << "\tRegistered Successfully!\n";
    Sleep(1000);
}

// after login
void afterLogin(string id)
{
    cout << "\nWelcome " << id << " !!\n";
}

// login
void login()
{
    system("cls");

    string id, pw;
    cout << "\tEnter Login ID: ";
    cin >> id;

    cout << "\tEnter Password: ";
    cin >> pw;

    ifstream infile("Login.txt");
    string line;
    bool found = false;

    while (getline(infile, line))
    {
        stringstream ss(line);
        string uid, upw;

        getline(ss, uid, ':');
        getline(ss, upw);

        if (id == uid && pw == upw)
        {
            found = true;
            cout << "\tLogin Successful...\n";
            afterLogin(id);
            Sleep(3000);
            break;
        }
    }

    if (!found)
        cout << "\tInvalid ID or Password!\n";

    infile.close();
}

int main()
{
    int choice;

    while (true)
    {
        system("cls");

        cout << "\n\t===== LOGIN SYSTEM =====\n";
        cout << "\t1. Register\n";
        cout << "\t2. Login\n";
        cout << "\t3. Exit\n";
        cout << "\tEnter choice: ";

        cin >> choice;

        switch (choice)
        {
        case 1:
            registration();
            break;

        case 2:
            login();
            break;

        case 3:
            return 0;

        default:
            cout << "\tInvalid choice!\n";
            Sleep(1000);
        }
    }
}
