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

	void add();			//Task 0, input grade book to the list
	void edit(int i);			//Task 0, input grade book to the list
    void verify();         // actually Task 0
    void populate();

    void load(char* filename);
    void store(char* filename);

    void uMenu();
};
