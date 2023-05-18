#include "User.h"

User::User()
{
	setSizeOfReadedBooks(0);
	setSizeOfBooksInRead(0);
	booksInRead = new Book[getSizeOfBooksInRead()];
	readedBooks = new Book[getSizeOfReadedBooks()];

    char name[16] = "none";
    setName(name);
}

User::User(char* name)
{
	setName(name);

	setSizeOfReadedBooks(0);
	setSizeOfBooksInRead(0);
	booksInRead = new Book[getSizeOfBooksInRead()];
	readedBooks = new Book[getSizeOfReadedBooks()];
}

User::~User()
{
	delete[] booksInRead;
	delete[] readedBooks;
}

void User::setSizeOfBooksInRead(int size)
{
	this->sizeOfBooksInRead = size;
}

void User::setSizeOfReadedBooks(int size)
{
	this->sizeOfReadedBooks = size;
}

void User::setName(char name[128])
{
    strcpy(this->name, name);
}

int User::getSizeOfBooksInRead()
{
	return sizeOfBooksInRead;
}

int User::getSizeOfReadedBooks()
{
	return sizeOfReadedBooks;
}

void User::resizeBooksInRead(int newSize)
{
    Book* books = new Book[newSize];
    for (int i = 0; i < getSizeOfBooksInRead(); i++)
    {
        if (i <= newSize)
        {
            books[i] = this->booksInRead[i];
        }
    }

    delete[] this->booksInRead;
    this->booksInRead = new Book[newSize];

    for (int i = 0; i < newSize; i++)
    {
        this->booksInRead[i] = books[i];
    }

    delete[] books;

    setSizeOfBooksInRead(newSize);
}

void User::resizeReadedBooks(int newSize)
{
    Book* books = new Book[newSize];
    for (int i = 0; i < getSizeOfReadedBooks(); i++)
    {
        if (i <= newSize)
        {
            books[i] = this->readedBooks[i];
        }
    }

    delete[] this->readedBooks;
    this->readedBooks = new Book[newSize];

    for (int i = 0; i < newSize; i++)
    {
        this->readedBooks[i] = books[i];
    }

    delete[] books;

    setSizeOfReadedBooks(newSize);
}
