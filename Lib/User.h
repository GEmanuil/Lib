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

	//trqbva da  gi napravq da zaemat samo bibiotechnite nomera
	void setBookInRead(Book& book);
	void setBookReaded(Book& book);

	Book* booksInRead;
	Book* readedBooks;

private:
	char name[128];

	void resizeBooksInRead(int newSize);
	void resizeReadedBooks(int newSize);

	int sizeOfBooksInRead;
	int sizeOfReadedBooks;
};

