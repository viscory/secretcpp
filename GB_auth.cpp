#include "GB_auth.h"
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

Authenticator::Authenticator()
{
    attempts=0;
}

int Authenticator::authenticate()
{
    char username[20];
    char password[20];
    char stored_username[20];
    char stored_password[20];

    ifstream pull("password.txt",ios::in);
    if (!pull) {
        cout<<"Password File not exist!"<<endl;
        return -1;
    }

    cout<<"(Enter exit to leave) Username: " << endl;
    cin>>username;
    while(strcmp(username,stored_username))
    {
        if (strcmp(username, "exit")==0) {
            cout<<"Bye!" << endl;
            return -1;
        }
        pull>>stored_username;
        pull>>stored_password;
        if(pull.eof()){   //if it is the end of file
            cout<<"Username does not exist. Enter Password to create account!" << endl;
            cin>>password;
            ofstream push("password.txt", ios_base::app);
            push << username << " " << password << "\n";
            return 1;
        }
    }
    cout<<"Password: " << endl;
    cin>>password;
    while(strcmp(password,stored_password)){
        cout<<"Wrong password. "<<endl;
        cout<<"Try again: " << endl;
        attempts++;
        if (attempts>3){
            cout<<"Too many attempts" << endl;
            return -1;
        }
        cin>>password;
    }
    cout<<"Login successful." << endl;
    return 1;
}
