#include "GB_handler.h"
#include <string.h>
#include <iostream>
#include <fstream>
using namespace std;

//constructor for setting data to zero
GradeBook::GradeBook()
{
	sName[99] = sEmail[99] = sIDno[9] = 0; 
    for (int i=0; i<3; i++){
        sMarks[i]=0;
    }
}

//set name
void GradeBook::setName(const char *name)
{
	strncpy(sName, name, 99);
}

//get To_From
const char* GradeBook::getName() const
{
	return sName;
}

//set email
void GradeBook::setEmail(const char *email)
{
	strncpy(sEmail, email, 99);
}

//get email
const char* GradeBook::getEmail() const
{
	return sEmail;
}

//set id
void GradeBook::setID(const char *id)
{
	strncpy(sIDno, id, 9);	//char [10] -> 9 usable characters
}

//get id
const char* GradeBook::getID() const
{
	return sIDno;
}

//set mark
void GradeBook::setMark(int i, int mark)
{
	sMarks[i] = mark;
}

//get mark
int GradeBook::getMark(int i) const
{
	return sMarks[i];
}

//get marks
const int* GradeBook::getMarks() const
{
	return sMarks;
}

//display the grade book
void GradeBook::display() const
{
	cout << "|Name:   " << sName << endl;
	cout << "|Email:  " << sEmail << endl;
	cout << "|ID:     " << sIDno << endl;
	cout << "|Marks:  " << sMarks[0] << ", " << sMarks[1] << ", " << sMarks[2] << endl;
	cout << "------------------------------------------" << endl;
}


//Implementation of GB_hander class

//Constructor set number of elements to zero
GradeBookHandle::GradeBookHandle()
{
	nEm = 0;
}

//display all grade books in the list
void GradeBookHandle::display() const
{
	cout << "------------------------------------------"<<endl;
	cout << "            Showing...."<<endl;
	cout << "------------------------------------------"<<endl;
	for (int i=0; i<nEm; i++) display(i);
}

//display the i th grade book in the list
void GradeBookHandle::display(int i) const
{
	if (i<nEm)
	{
	    cout << "------------------------------------------"<<endl;
	    cout << "|Serial: " << i << endl;
	    list[i].display();
	}
}

//delete the i th grade book from the list
void GradeBookHandle::delGradeBook(int i)
{
	if (i<nEm)
	{
		GradeBook tmp;
        for (int k=i+1; k<nEm; k++) list[k-1] = list[k];
        list[nEm-1] = tmp; 
		nEm--;
	}
	else cout << "No such grade book!" << endl;

}


//check if the input is an alphabet
bool isLetter(char c)
{
	return (c>='A' && c<='Z') || (c>='a' && c<='z');
}

//check if the input is a number
bool isNumber(char c)
{
	return c>='0' && c<='9';
}

// composite function to check if name has one space and only ascii leters
int checkName(char* name)
{
    int len=strlen(name);
    if (len==0) { cin.getline(name, 100); len=strlen(name); }

    bool noSpace = true, onlyLetter=true;
    for (int i=0; i<len; i++)
    {
        if (name[i]==' ') noSpace = false;
        else if (!isLetter(name[i])) {onlyLetter = false; break;}
    }
    if (!noSpace && onlyLetter) return 1;
    return 0;
}

// function to check if the email is valid
int checkEmail(char* email)
{
    int len=strlen(email);
    if (len==0) { cin.getline(email, 100); len=strlen(email); }

    bool nok=false;	
    char c;
    int nat=0, ndot=0; 

    if (isLetter(email[0]) && email[len-1]!='.')
    {

        for (int i=1; i<len; i++)
        {
            c = email[i];
            if (nat == 1 && c=='.') ndot++;

            if (c=='@' && ++nat >1){ nok = true; break; }

            if (c!='.' && c!='@' && c!='_' && c!='-' && !isLetter(c) && !isNumber(c)) {nok = true; break;}
        }
    }
    else nok = true;

    if (!nok && ndot>0) return 1;
    return 0;
}

// function to check if the id is valid
int checkID(char* id)
{
    int len=strlen(id);
    if (len==0) { cin.getline(id, 100); len=strlen(id); }

    bool nok=false;	
    for (int i=0; i<8; i++)
        if ( !isNumber(id[i]) ){ nok = true; break; }

    if (!nok && len==9 && (id[8]=='D'||id[8]=='d')) return 1;
    return 0;
}

// checking if mark is within correct range
int checkMark(int mark)
{
    if (mark>=0 && mark <=100) return 1;
    return 0;
}

//input student name and check the format
const char* inputName()
{
	static char name[100];
	while(true)
	{
		cout << "Name = "<< endl;
		cin.getline(name, 100);
		if (checkName(name)) return name;
        cout << "Illegal input!" << endl;
    }
}

//input student email and check the format
const char* inputEmail()
{
	static char email[100];
	while(true)
	{
		cout << "Email = " << endl;
		cin.getline(email, 100);
		if (checkEmail(email)) return email;
        cout << "Illegal input!" << endl;
	}
}

//input student id and check the format
const char* inputID()
{
	static char id[100];
	while(true)
	{
		cout << "ID = " << endl;
		cin.getline(id, 100);
		if (checkID(id)) return id;
        cout << "Illegal input!" << endl;
	}
}

//input quiz mark
int inputMark()
{
	int mark;
	while(true)
	{
		cout << "Mark = " << endl;
        cin >> mark;
		if (checkMark(mark)) return mark;
        cout << "Illegal input!" << endl;
	}
}

// function to add a new record to database
void GradeBookHandle::add()
{
    list[nEm].setName( inputName() );
	list[nEm].setEmail( inputEmail() );
	list[nEm].setID( inputID() );
	for (int i=0; i<3; i++) list[nEm].setMark(i, inputMark() );
	nEm++;
}

// function to edit the content of a database record
void GradeBookHandle::edit(int i)
{
    display(i);
    list[i].setName( inputName() );
	list[i].setEmail( inputEmail() );
	list[i].setID( inputID() );
	for (int j=0; j<3; j++) list[i].setMark(j, inputMark() );
}


// populates database with faulty data for verify() testing
void GradeBookHandle::populate()
{
	list[nEm].setName( "Peter Lee" );		//preset data
	list[nEm].setEmail( "p@peter.lee" );
	list[nEm].setID( "12345678D" );
	list[nEm].setMark(0, 0 ); list[nEm].setMark(1, 10 ); list[nEm].setMark(2, 20 );
	nEm++;

    // intentionally faulty data
	list[nEm].setName( "Mary Lie" );
	list[nEm].setEmail( "mlie.org" );
	list[nEm].setID( "12345675D" );
	list[nEm].setMark(0, 100 ); list[nEm].setMark(1, 90 ); list[nEm].setMark(2, 80 );
	nEm++;

	list[nEm].setName( "Ester Wong" );
	list[nEm].setEmail( "e@wo-ng.ee" );
	list[nEm].setID( "12345679D" );
	list[nEm].setMark(0, 50 ); list[nEm].setMark(1, 60 ); list[nEm].setMark(2, 70 );
	nEm++;
}

// goes through database and uses input validation functions to check if valid
void GradeBookHandle::verify()
{
    for(int i=0; i<nEm; i++)
    {
        if (!checkName((char*)list[i].getName()))
        {
            list[i].display();
            cout << "Error in Name" << endl;
            list[i].setName(inputName()); 
        }
        if (!checkID((char*)list[i].getID()))
        {
            list[i].display();
            cout << "Error in ID" << endl;
            list[i].setID(inputID()); 
        }
        if (!checkEmail((char*)list[i].getEmail()))
        {
            list[i].display();
            cout << "Error in Email" << endl;
            list[i].setEmail(inputEmail()); 
        }
        for (int j=0; j<3; j++){
            if (!checkMark(list[i].getMark(i)))
            {
                list[i].display();
                cout << "Error in Mark " << j << endl;
                list[i].setMark(i, inputMark()); 
            }
        }
    }
}

// replacing spaces with underscores before storing database to file, encoding
char* replaceSpace(char* text)
{
    for(int i=0; i<strlen(text); i++)
    {
        if(text[i] == ' ')
        {
            text[i]='_';
            return text;
        }
    }
    return text;       
}

// decoding underscores into spaces before loading up database from file
char* replaceUnderscore(char* text)
{
    for(int i=0; i<strlen(text); i++)
    {
        if(text[i] == '_')
        {
            text[i]=' ';
            return text;
        
        }
    }    
    return text;       
}

// simply writes the content of the database to file with some encoding
void GradeBookHandle::store(char* filename)
{
    ofstream push(filename, ios::out);
    if(!push)
    {
        push << "\n";
    }


    for(int i=0; i<nEm; i++)
    {
        push<<replaceSpace((char*)list[i].getName())<<" ";
        push<<list[i].getID()<<" ";
        push<<list[i].getEmail()<<" ";
        push<<list[i].getMark(0)<<" ";
        push<<list[i].getMark(1)<<" ";
        push<<list[i].getMark(2)<<endl;
    }
}

// parses through content of the file and loads it after decoding
void GradeBookHandle::load(char* filename)
{
    int counter=0;
	char name[100], id[10], email[100];	//array of characters
	int marks[3];
    
    ifstream pull(filename, ios::in);
    if (!pull) {
        cout<<"Database File not exist!"<<endl;
        return;
    }
    while(true)
    {
        if(!pull.good()) break;
        
        pull>>name;
        pull>>id;
        pull>>email;
        pull>>marks[0];
        pull>>marks[1];
        pull>>marks[2];
        list[counter].setName(replaceUnderscore(name));
        list[counter].setID(id);
        list[counter].setEmail(email);
        list[counter].setMark(0, marks[0]);
        list[counter].setMark(1, marks[1]);
        list[counter].setMark(2, marks[2]);
        counter++;
    }
    nEm = counter;
}

// continuously shows menu until user wants to exit
void GradeBookHandle::uMenu()
{
	char c; 
	while(true)
	{
        cout << endl;
		cout << "====================" << endl;
		cout << " GradeBook Database" << endl;
		cout << "====================" << endl;
		cout << "1. View Database" << endl;
		cout << "2. Edit GradeBook" << endl;
		cout << "3. Add GradeBook" << endl;
		cout << "4. Validate Database (Part 0)" << endl;
		cout << "5. Store Database (Distinction)" << endl;
		cout << "6. Load Database (Distinction)" << endl;
		cout << "7. Load Dummy Data" << endl;
		cout << "0. Exit" << endl;
		cin >> c;
		if (c!='0' && (c<'1' || c>'7')) cout << "Illegal choice!" << endl;
        if (c=='1') display();
        if (c=='2')
        {
            int serial;
            cout << "Enter Serial: " << endl;
            cin >> serial;
            edit(serial);
        }
        if (c=='3') add();
        if (c=='4') verify();
        if (c=='5' || c=='6')
        {
            char* filename = new char[40];
            cout << "Enter Database Filename: " << endl;
            cin >> filename;

            if (c=='5') store((char*)filename);
            if (c=='6') load((char*)filename);
        }
        if (c=='7') populate();
        if (c=='0') return;
    }
}
