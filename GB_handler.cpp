#include "GB_handler.h"
#include <cstring>
#include <iostream>
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
	cout << "------------------------------------------\n";
	cout << "|Name: " << sName << endl;
	cout << "|Email:" << sEmail << endl;
	cout << "|ID:   " << sIDno << endl;
	cout << "|Marks:" << sMarks[0] << ", " << sMarks[1] << ", " << sMarks[2] << endl;
	cout << "------------------------------------------\n";
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
	for (int i=0; i<nEm; i++) display(i);
}

//display the i th grade book in the list
void GradeBookHandle::display(int i) const
{
	if (i<nEm)
	{
	    list[i].display();
	}
}

//find a name from the list, -1 means not found
int GradeBookHandle::findName(const char *nn)		
{
	for (int i=0; i<nEm; i++)
		if (strcmp(list[i].getName(), nn) == 0) return i;

	return -1;
}

//find an email from the list, -1 means not found
int GradeBookHandle::findEmail(const char *em)	
{
	for (int i=0; i<nEm; i++)
		if (strcmp(list[i].getEmail(), em) == 0) return i;

	return -1;
}

//find a student id from the list, -1 means not found
int GradeBookHandle::findID(const char *id)		
{
	for (int i=0; i<nEm; i++)
		if (strcmp(list[i].getID(), id) == 0) return i;

	return -1;
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
	else cout << "No such grade book!\a\n";

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
		cout << "Name = ";
		cin.getline(name, 100);
		if (checkName(name)) return name;
        cout << "Illegal input!\a\n";
    }
}

//input student email and check the format
const char* inputEmail()
{
	static char email[100];
	while(true)
	{
		cout << "Email = ";
		cin.getline(email, 100);
		if (checkEmail(email)) return email;
        cout << "Illegal input!\a\n";
	}
}

//input student id and check the format
const char* inputID()
{
	static char id[100];
	while(true)
	{
		cout << "ID = ";
		cin.getline(id, 100);
		if (checkID(id)) return id;
        cout << "Illegal input!\a\n";
	}
}

//input quiz mark
int inputMark()
{
	int mark;
	while(true)
	{
		cout << "Mark = ";
        cin >> mark;
		if (checkMark(mark)) return mark;
        cout << "Illegal input!\a\n";
	}
}

//Task 0, input grade book to the list
void GradeBookHandle::input()
{
	list[nEm].setName( inputName() );
	list[nEm].setEmail( inputEmail() );
	list[nEm].setID( inputID() );
	for (int i=0; i<3; i++) list[nEm].setMark(i, inputMark() );
	nEm++;
/*
	list[nEm].setName( "Peter Lee" );		//preset data
	list[nEm].setEmail( "p@peter.lee" );
	list[nEm].setID( "12345678D" );
	list[nEm].setMark(0, 0 ); list[nEm].setMark(1, 10 ); list[nEm].setMark(2, 20 );
	nEm++;

	list[nEm].setName( "Mary Lie" );
	list[nEm].setEmail( "m@lie.org" );
	list[nEm].setID( "12345675D" );
	list[nEm].setMark(0, 100 ); list[nEm].setMark(1, 90 ); list[nEm].setMark(2, 80 );
	nEm++;

	list[nEm].setName( "Ester Wong" );
	list[nEm].setEmail( "e@wo-ng.ee" );
	list[nEm].setID( "12345679D" );
	list[nEm].setMark(0, 50 ); list[nEm].setMark(1, 60 ); list[nEm].setMark(2, 70 );
	nEm++;
*/
}

void GradeBookHandle::verify()
{
    for(int i=0; i<nEm; i++)
    {
        if (!checkName((char*)list[i].getName())) list[i].setName(inputName()); 
        if (!checkID((char*)list[i].getID())) list[i].setID(inputID()); 
        if (!checkEmail((char*)list[i].getEmail())) list[i].setEmail(inputEmail()); 
        for (int j=0; j<3; j++){
            if (!checkMark(list[i].getMark(i))) list[i].setMark(i, inputMark()); 
        }
    }
}    


char uMenu()
{
	char c; 
	while(true)
	{
		cout << "1. Choose name\n"
			    "2. Choose email\n"
				"3. Choose id\n"
				"Your choice: ";
		cin >> c;
		if (c<'1' || c>'3') cout << "Illegal choice!\a\n";
		else return c;
	}
}
