#pragma once
#include "Book.h"
#include <iostream>
#pragma warning(disable:4996)

class User
{
public:
	User(char* name);
	char name[128];
	Book* booksInRead;
	Book* readedBooks;
};

