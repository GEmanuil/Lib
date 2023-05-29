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
                //tuk gurmi sled kato sum dobavil kniga koqto se chete
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

void User::saveBooks(int index)
{
    //trqbva da zapazim na user[i] readed bookovete v fail 

    std::ofstream stream("booksInRead.bin", std::ios::binary);
    if (!stream.is_open())
    {
        std::cout << "Cant open file!!\n";
    }

    //purvo mestim file pointera na index-a
    //ama mai trqbva prosto da go prestim nai nakraq kato chetem size danni, size danni .. (ili prosto seekp(0, std::ios::end))
    //i sled tova da vzemem size-a da go slojim v nachaloto i da pishem kolkoto e size-a

    stream.seekp(0, std::ios::end);
    int size = getSizeOfBooksInRead();

    stream.write(reinterpret_cast<const char*>(&size), sizeof(int));
    for (int i = 0; i < size; i++)
    {
        stream.write(reinterpret_cast<const char*>(&booksInRead[i]), sizeof(int));
    }

    //sushtoto s booksInReadByMonth trqbva da TODO getrs i seters na SizeOfBooksInRead
    stream.open("booksInReadByMonth", std::ios::binary);
    if (!stream.is_open())
    {
        std::cout << "Cant open file!!\n";
    }
    stream.seekp(0, std::ios::end);

    stream.write(reinterpret_cast<const char*>(&size), sizeof(int));
    for (int i = 0; i < size; i++)
    {
        stream.write(reinterpret_cast<const char*>(&booksInReadByMonth[i]), sizeof(short));
    }

    stream.close();
}

void User::loadBooks(int index)
{

    std::ifstream stream("booksInRead.bin", std::ios::binary);

    int size = 0;

    if (!stream.is_open())
    {
        std::cout << "Cant open file!!\n";
    }

    //pochvame 
    stream.seekg(0, std::ios::beg);

    //chetem do kato ne stignem do index-a (masiva ot knigi za tozi user)
    for (size_t i = 0; i < index; i++)
    {
        stream.read(reinterpret_cast<char*>(&size), sizeof(int));
        //int pointerToGo = sizeof(int) * size;
        stream.seekg(sizeof(int) * size, std::ios::beg);
    }

    //stigaiki zapochvame da chetem
    stream.read(reinterpret_cast<char*>(&size), sizeof(int));
    booksInRead = new int[size];

    for (size_t i = 0; i < size; i++)
    {

        // GURMI NESHTO MAI SHTOT NE E INICIALIZIRAN ARRAY-A



        stream.read(reinterpret_cast<char*>(&this->booksInRead[i]), sizeof(int));


        setSizeOfBooksInRead(i + 1);
    }

    stream.close();
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


void User::printBooksInRead()
{

    std::cout << "Book In Read: " << std::endl;

    for (int i = 0; i < getSizeOfBooksInRead(); i++)
    {
        std::cout << booksInRead[i] << std::endl;
    }
}

void User::resizeBooksInRead(int newSize)
{
    int* books = new int[newSize];
    short* booksInReadByMonth = new short[newSize];
    for (int i = 0; i < getSizeOfBooksInRead(); i++)
    {
        if (i < newSize)
        {
            books[i] = this->booksInRead[i];
            booksInReadByMonth[i] = this->booksInReadByMonth[i];
        }
    }

    delete[] this->booksInRead;
    delete[] this->booksInReadByMonth;
    this->booksInRead = new int[newSize];
    this->booksInReadByMonth = new short[newSize];

    //from newSize to getSizeOfBooksInRead()
    for (int i = 0; i < getSizeOfBooksInRead(); i++)
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
