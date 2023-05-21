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

User::User(const User& other)
{
    sizeOfBooksInRead = other.sizeOfBooksInRead;
    if (sizeOfBooksInRead > 0) {
        booksInRead = new Book[sizeOfBooksInRead];
        for (int i = 0; i < sizeOfBooksInRead; ++i) {
            booksInRead[i] = other.booksInRead[i]; 
        }
    }

    sizeOfReadedBooks = other.sizeOfReadedBooks;
    if (sizeOfReadedBooks > 0) {
        readedBooks = new Book[sizeOfReadedBooks];
        for (int i = 0; i < sizeOfReadedBooks; ++i) {
            readedBooks[i] = other.readedBooks[i];
        }
    }

    strcpy(name, other.name);
}

User& User::operator=(const User& other)
{
    if (this != &other)
    {
        delete[] booksInRead;
        delete[] readedBooks;

        sizeOfBooksInRead = other.sizeOfBooksInRead;
        if (sizeOfBooksInRead > 0) {
            booksInRead = new Book[sizeOfBooksInRead];
            for (int i = 0; i < sizeOfBooksInRead; ++i) {
                booksInRead[i] = other.booksInRead[i];
            }
        }
        else
        {
            booksInRead = nullptr;
        }

        sizeOfReadedBooks = other.sizeOfReadedBooks;
        if (sizeOfReadedBooks > 0) {
            readedBooks = new Book[sizeOfReadedBooks];
            for (int i = 0; i < sizeOfReadedBooks; ++i) {
                readedBooks[i] = other.readedBooks[i];
            }
        }
        else
        {
            readedBooks = nullptr;
        }

        strcpy(name, other.name);
    }
    return *this;
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

void User::getName(char* name)
{
    strcpy(name, this->name);
}

int User::getSizeOfBooksInRead()
{
	return sizeOfBooksInRead;
}

int User::getSizeOfReadedBooks()
{
	return sizeOfReadedBooks;
}

void User::setBookInRead(Book& book)
{
    resizeBooksInRead(getSizeOfBooksInRead() + 1);
    setSizeOfBooksInRead(getSizeOfBooksInRead() + 1);

    booksInRead[getSizeOfBooksInRead() - 1] = book;
}

void User::setBookReaded(Book& book)
{
    resizeReadedBooks(getSizeOfReadedBooks() + 1);
    setSizeOfReadedBooks(getSizeOfReadedBooks() + 1);

    readedBooks[getSizeOfReadedBooks() - 1] = book;
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
