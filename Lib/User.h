#pragma once
#include "Book.h"
#include <iostream>
#pragma warning(disable:4996)

class User
{
public:
	User();
	User(char* name);
	User(const User& user);
	User& operator=(const User& other);
	~User();

	void setSizeOfBooksInRead(int size);
	void setSizeOfReadedBooks(int size);
	void setName(char name[128]);
	void getName(char* name);

	int getSizeOfBooksInRead();
	int getSizeOfReadedBooks();

	void setBookInRead(int libNum, short month);
	void setBookReaded(int libNum);

	short* booksInReadByMonth;
	int* booksInRead;
	int* readedBooks;

private:
	char name[128];

	void resizeBooksInRead(int newSize);
	void resizeReadedBooks(int newSize);
	void fixBooksInReadArr(int libNum);

	int sizeOfBooksInRead;
	int sizeOfReadedBooks;
};

