#include "User.h"

User::User()
{
    //char name[16] = "none";
    //setName(name);

	setSizeOfReadedBooks(0);
	setSizeOfBooksInRead(0);
	booksInRead = new int[getSizeOfBooksInRead()];
    booksInReadByMonth = new short[getSizeOfBooksInRead()];

	readedBooks = new int[getSizeOfReadedBooks()];

}

User::User(char* name)
{
	setName(name);

	setSizeOfReadedBooks(0);
	setSizeOfBooksInRead(0);
	booksInRead = new int [getSizeOfBooksInRead()];
    booksInReadByMonth = new short[getSizeOfBooksInRead()];

	readedBooks = new int[getSizeOfReadedBooks()];
}

//TODO cctor
User::User(const User& other)
{
    sizeOfBooksInRead = other.sizeOfBooksInRead;
    if (sizeOfBooksInRead > 0) {
        booksInRead = new int[sizeOfBooksInRead];
        booksInReadByMonth = new short[sizeOfBooksInRead];
        for (int i = 0; i < sizeOfBooksInRead; ++i) {
            booksInRead[i] = other.booksInRead[i]; 
            booksInReadByMonth[i] = other.booksInReadByMonth[i];
        }
    }

    sizeOfReadedBooks = other.sizeOfReadedBooks;
    if (sizeOfReadedBooks > 0) {
        readedBooks = new int[sizeOfReadedBooks];
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
        delete[] booksInReadByMonth;

        sizeOfBooksInRead = other.sizeOfBooksInRead;
        if (sizeOfBooksInRead > 0) {
            booksInRead = new int[sizeOfBooksInRead];
            booksInReadByMonth = new short[sizeOfBooksInRead];
            for (int i = 0; i < sizeOfBooksInRead; ++i) {
                booksInRead[i] = other.booksInRead[i];
                booksInReadByMonth[i] = other.booksInReadByMonth[i];
            }
        }
        else
        {
            booksInRead = nullptr;
            booksInReadByMonth = nullptr;
        }

        sizeOfReadedBooks = other.sizeOfReadedBooks;
        if (sizeOfReadedBooks > 0) {
            readedBooks = new int[sizeOfReadedBooks];
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
    delete[] booksInReadByMonth;
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

void User::setBookInRead(int libNum, short month)
{
    resizeBooksInRead(getSizeOfBooksInRead() + 1);

    booksInRead[getSizeOfBooksInRead() - 1] = libNum;
    booksInReadByMonth[getSizeOfBooksInRead() - 1] = month;
}

void User::setBookReaded(int libNum)
{
    resizeReadedBooks(getSizeOfReadedBooks() + 1);
    readedBooks[getSizeOfReadedBooks() - 1] = libNum;

    //func to get out the book which was readed and fix the array
    fixBooksInReadArr(libNum);
}

void User::fixBooksInReadArr(int libNum)
{
    size_t indexOfArrToRemove = 0;

    for (int i = 0; i < getSizeOfBooksInRead(); i++)
    {
        if (booksInRead[i] == libNum)
        {
            indexOfArrToRemove = i;
        }
    }

    for (int i = indexOfArrToRemove; i < getSizeOfBooksInRead() - 1; i++)
    {
        booksInRead[i] = booksInRead[i + 1];
        booksInReadByMonth[i] = booksInReadByMonth[i + 1];
    }
    setSizeOfBooksInRead(getSizeOfBooksInRead() - 1);
    


    int* rBooks = new int[getSizeOfBooksInRead()];
    short* bInReadByMonth = new short[getSizeOfBooksInRead()];

    for (size_t i = 0; i < getSizeOfBooksInRead(); i++)
    {
        rBooks[i] = booksInRead[i];
        bInReadByMonth[i] = booksInReadByMonth[i];
    }

    //TODO shallow copy
    delete[] booksInRead;
    delete[] booksInReadByMonth;

    for (size_t i = 0; i < getSizeOfBooksInRead(); i++)
    {
        booksInRead[i] = rBooks[i];
        booksInReadByMonth[i] = bInReadByMonth[i];
    }

    delete[] rBooks;
    delete[] bInReadByMonth;
}


void User::resizeBooksInRead(int newSize)
{
    int* books = new int[newSize];
    short* booksInReadByMonth = new short[newSize];
    for (int i = 0; i < getSizeOfBooksInRead(); i++)
    {
        if (i <= newSize)
        {
            books[i] = this->booksInRead[i];
            booksInReadByMonth[i] = this->booksInReadByMonth[i];
        }
    }

    delete[] this->booksInRead;
    delete[] this->booksInReadByMonth;
    this->booksInRead = new int[newSize];
    this->booksInReadByMonth = new short[newSize];

    for (int i = 0; i < newSize; i++)
    {
        this->booksInRead[i] = books[i];
        this->booksInReadByMonth[i] = booksInReadByMonth[i];
    }

    delete[] books;
    delete[] booksInReadByMonth;

    setSizeOfBooksInRead(newSize);
}

void User::resizeReadedBooks(int newSize)
{
    int* books = new int[newSize];
    for (int i = 0; i < getSizeOfReadedBooks(); i++)
    {
        if (i <= newSize)
        {
            books[i] = this->readedBooks[i];
        }
    }

    delete[] this->readedBooks;
    this->readedBooks = new int[newSize];

    for (int i = 0; i < newSize; i++)
    {
        this->readedBooks[i] = books[i];
    }

    delete[] books;

    setSizeOfReadedBooks(newSize);
}
