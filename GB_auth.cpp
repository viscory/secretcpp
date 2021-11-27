#include "GB_auth.h"
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

Authenticator::Authenticator()
{
    attempts=0;
}

// a return of 1 means the user has authenticated themselves successfully
// a return of -1 means the program will exit
int Authenticator::authenticate()
{
    // these are inputted by the user
    char username[20];
    char password[20];
    // these are parsed from the password.txt file
    char stored_username[20];
    char stored_password[20];

    fstream pull("password.txt", ios::in);
    // must avoid space characters as it messes up the format in which passwords and usernames are stored
    cout << "(only a-zA-Z1-9) Enter exit to leave or username" << endl;
    cin >> username;
    // strcmp returns a 0 when the two inputs are identical
    if (strcmp(username, "exit")==0) {
        cout<<"Bye!" << endl;
        return -1;
    }
    
    cout<<"Password: ";
    cin>>password;
    // loop stops when username and stored username are the same
    // the program loops throug password.txt and stores each username in stored_username to compare
    while(strcmp(username, stored_username))
    {
        // if the file does not exist or file has reached end, create an account
        if(!pull || pull.eof()){   //if it is the end of file
            cout<<"Username does not exist. Creating new account!" << endl;
            pull.close();
            // stopping the pull and we are writing to the file now
            fstream push("password.txt", ios_base::app);
            push << username << " " << password << "\n";
            return 1;
        }
        // stored in password.txt file as user1 pass1\n user2 pass2. so they are taken from the file two words at a time
        pull>>stored_username;
        pull>>stored_password;
    }
    // loop to allow user two more attemps to login if password is incorrect
    while(strcmp(password, stored_password)){
        cout<<"Wrong password. " << endl;
        cout<<"Try again: " << endl;
        attempts++;
        if (attempts>2){
            cout<<"Too many attempts" << endl;
            return -1;
        }
        cin>>password;
    }
    cout<<"Login successful." << endl;
    return 1;
}
