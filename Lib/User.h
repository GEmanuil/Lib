#pragma once
#include "Book.h"
#include <iostream>
#include <fstream>
#pragma warning(disable:4996)

class User
{
public:
	User();
	User(char* name);
	User(const User& user);

	User& operator=(const User& other);
	bool operator==(const User& other);
	bool operator!=(const User& other);
	bool operator<(const User& other);
	bool operator<=(const User& other);
	bool operator>(const User& other);
	bool operator>=(const User& other);
	int operator[](const int libNum);
	User& operator+=(const int libNum);
	User& operator-=(const int libNum);

	~User();

	void setSizeOfBooksInRead(int size);
	void setSizeOfReadedBooks(int size);
	void setName(char name[128]);
	void setBookInRead(int libNum, short month);
	void setBookReaded(int libNum);

	//TODO make geters const
	void getName(char* name);
	int getSizeOfBooksInRead();
	int getSizeOfReadedBooks() const;

	void saveBooks(int index);
	void loadBooks(int index);

	int* booksInReadByMonth;
	int* booksInRead;
	int* readedBooks;

	void printReadBooks();

private:
	char name[128];

	void intializeBooksInRead(int newSize);
	void resizeReadedBooks(int newSize);
	void fixBooksInReadArr(int libNum);

	int sizeOfBooksInRead;
	int sizeOfReadedBooks;
};

