#define _CRT_SECURE_NO_WARNINGS

// class for grade book
class GradeBook
{
	//char *name, *email, *id; but you need "new char[]" in constructor and "delete []" in destructor
	char sName[100], sEmail[100], sIDno[10];	//array of characters
	int sMarks[3];

public:
	GradeBook(); //constructor for setting data to zero

	//~GB(); destructor is not needed for array

    // setters and getters for 
    // sName
	void setName(const char *name);
	const char* getName() const;

    // sEmail
	void setEmail(const char *email);
	const char* getEmail() const;

    // sIDno
	void setID(const char *id );
	const char* getID() const;

    // sMarks
	void setMark(int i, int mark);
	int getMark(int i) const;
	const int* getMarks() const;

	void display() const;
};


class GradeBookHandle		//class for grade book handler
{
	GradeBook list[100];	//list of grade book, max 100 records
	int nEm;			//number of elements

public:
	GradeBookHandle();				//Constructor set number of elements to zero

	//~Em_Han(); destructor is not needed for array

	void display() const;			//display all grade books in the list
	void display(int i) const;		//display a grade book in the list
	void delGradeBook(int i); 			//delete the i th grade book from the list

	void nameSort();		//sort based on the names in ascending order
	void emailSort();		//sort based on the emails in ascending order
	void idSort();		//sort based on the ids in ascending order 

	int findName(const char *nn);		//find a name from the list, -1 means not found
	int findEmail(const char *em);	//find an email from the list, -1 means not found
	int findID(const char *nn);		//find a student id from the list, -1 means not found

	void input();			//Task 0, input grade book to the list

	void delGradeBook();			//Task 1, delete a grade book from the list based on user input of name, email, or ID.  

	void sortGradeBook();			//Task 2, sort in ascending order based on user input of name, email, or ID.  

	void avgGrade();		//Task 3, calculation of average grade of each student grade book marks

	void searchGradeBook();		//Task 4, search of students?record based on user input of name, email, or ID.  
};
