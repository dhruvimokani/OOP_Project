#include<iostream>
#include<fstream>
#include<windows.h>
#include<sstream>
using namespace std;

class Login //login class
{
private:     string LoginID,Password;
public:
    void setID(string id){ LoginID=id; }
    void setPW(string pw){ Password=pw; }

    string getID(){ return LoginID; }
    string getPW(){ return Password; }
};

bool isUserExists(string id)   //if user already exist with same id
{
    ifstream infile("Login.txt");
    string line;
    while(getline(infile,line))
    {
        stringstream ss(line);
        string uid, pw;
        getline(ss, uid, ':');
        getline(ss, pw);

        if(uid == id)
            return true;
    }
    return false;
}

void changePassword(string id)      // Change password 
{
    ifstream infile("Login.txt");
    ofstream temp("temp.txt");
    string line;
    string newpw;

    cout<<"\tEnter New Password (min 8 chars): ";
    cin>>newpw;
    if(newpw.length() < 8)
    {
        cout<<"\tPassword too short!\n";
        return;
    }
    while(getline(infile,line))
    {
        stringstream ss(line);
        string uid, pw;
        getline(ss, uid, ':');
        getline(ss, pw);

        if(uid == id)
        {
            temp << uid << ":" << newpw << endl;
        }
        else
        {
            temp << uid << ":" << pw << endl;
        }
    }

    infile.close();
    temp.close();
    remove("Login.txt");
    rename("temp.txt","Login.txt");

    cout<<"\tPassword Changed Successfully!\n";
}

void deleteAccount(string id)               //Delete account
{
    ifstream infile("Login.txt");
    ofstream temp("temp.txt");
    string line;

    while(getline(infile,line))
    {
        stringstream ss(line);
        string uid, pw;
        getline(ss, uid, ':');
        getline(ss, pw);
        if(uid != id)
        {
            temp << uid << ":" << pw << endl;
        }
    }

    infile.close();
    temp.close();
    remove("Login.txt");
    rename("temp.txt","Login.txt");
    cout<<"\tAccount Deleted Successfully!\n";
}

void userMenu(string id)
{
    int choice;
    do {
        cout<<"\n\n\t===== USER MENU =====\n";
        cout<<"\t1. Change Password\n";
        cout<<"\t2. Delete Account\n";
        cout<<"\t3. Logout\n";
        cout<<"\tEnter choice: ";
        cin>>choice;
        if(choice == 1)
        {
            changePassword(id);
        }
        else if(choice == 2)
        {
            deleteAccount(id);
            break;
        }
    } while(choice != 3);
}

void registration()
{
    system("cls");
    string id,pw;
    cout<<"\tEnter Login ID: ";
    cin>>id;
    if(isUserExists(id))
    {
        cout<<"\tUser already exists!\n";
        Sleep(1500);
        return;
    }
    do {
        cout<<"\tEnter Password (min 8 chars): ";
        cin>>pw;
        if(pw.length()<8)
            cout<<"\tToo short!\n";
    } while(pw.length()<8);

    ofstream outfile("Login.txt", ios::app);
    outfile << id << ":" << pw << endl;
    cout<<"\tRegistered Successfully!\n";
    Sleep(1000);
}

void login()
{
    system("cls");
    string id,pw;
    cout<<"\tEnter Login ID: ";
    cin>>id;
    cout<<"\tEnter Password: ";
    cin>>pw;

    ifstream infile("Login.txt");
    string line;
    bool found=false;
    while(getline(infile,line))
    {
        stringstream ss(line);
        string uid, upw;
        getline(ss, uid, ':');
        getline(ss, upw);

        if(id==uid && pw==upw)
        {
            found=true;
            cout<<"\tLogin Successful...\n";
            Sleep(1000);
            userMenu(id);
            break;
        }
    }
    if(!found)
        cout<<"\tInvalid ID or Password!\n";
    infile.close();
}

int main()
{
    int choice;
    while(true)
    {
        system("cls");
        cout<<"\n\t===== LOGIN SYSTEM =====\n";
        cout<<"\t1. Register\n";
        cout<<"\t2. Login\n";
        cout<<"\t3. Exit\n";
        cout<<"\tEnter choice: ";
        cin>>choice;

        if(choice==1)
            registration();
        else if(choice==2)
            login();
        else if(choice==3)
            break;
        Sleep(500);
    }
}
