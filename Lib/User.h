#pragma once
#include "Book.h"
#include <iostream>
#pragma warning(disable:4996)

class User
{
public:
	User();
	User(char* name);
	~User();

	void setSizeOfBooksInRead(int size);
	void setSizeOfReadedBooks(int size);
	void setName(char* name);

	int getSizeOfBooksInRead();
	int getSizeOfReadedBooks();

	Book* booksInRead;
	Book* readedBooks;

private:
	char name[128];

	void resizeBooksInRead(int newSize);
	void resizeReadedBooks(int newSize);

	int sizeOfBooksInRead;
	int sizeOfReadedBooks;
};

