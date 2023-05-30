#include "User.h"

User::User()
{
    //char name[16] = "none";
    //setName(name);

	setSizeOfReadedBooks(0);
	setSizeOfBooksInRead(0);
	booksInRead = new int[getSizeOfBooksInRead()];
    booksInReadByMonth = new int[getSizeOfBooksInRead()];

	readedBooks = new int[getSizeOfReadedBooks()];

}

User::User(char* name)
{
	setName(name);

	setSizeOfReadedBooks(0);
	setSizeOfBooksInRead(0);
	booksInRead = new int [getSizeOfBooksInRead()];
    booksInReadByMonth = new int[getSizeOfBooksInRead()];

	readedBooks = new int[getSizeOfReadedBooks()];
}

//TODO cctor
User::User(const User& other)
{
    sizeOfBooksInRead = other.sizeOfBooksInRead;
    if (sizeOfBooksInRead > 0) {
        booksInRead = new int[sizeOfBooksInRead];
        booksInReadByMonth = new int[sizeOfBooksInRead];
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
            booksInReadByMonth = new int[sizeOfBooksInRead];
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

    std::fstream stream("booksInRead.bin", std::ios::binary | std::ios::in | std::ios::out);
    if (!stream.is_open())
    {
        std::cout << "Cant open file!!\n";
    }

    //purvo mestim file pointera na index-a
    //ama mai trqbva prosto da go prestim nai nakraq kato chetem size danni, size danni .. (ili prosto seekp(0, std::ios::end))
    // ILI PUK NE SHTOT MOJE SUSHTESTVUVASHT USER DA ISKA DA VZEME KNIGA I TOGAVA VSICHKO SHTE SE RAZVALI
    //i sled tova da vzemem size-a da go slojim v nachaloto i da pishem kolkoto e size-a

    int size = 5;

    stream.seekg((index) * (sizeof(int)*(5 + 1) /*5 za danni 1 za size*/), std::ios::beg);
    stream.seekp((index) * (sizeof(int) * (5 + 1)), std::ios::beg);


    size = getSizeOfBooksInRead();
    stream.write(reinterpret_cast<const char*>(&size), sizeof(int));


    for (int i = 0; i < 5; i++)
    {
        stream.write(reinterpret_cast<const char*>(&this->booksInRead[i]), sizeof(int));
    }

    stream.close();

    //sushtoto s booksInReadByMonth trqbva da TODO getrs i seters na SizeOfBooksInRead
    std::fstream stream1("booksInReadByMonth.bin", std::ios::binary | std::ios::in | std::ios::end);
    if (!stream1.is_open())
    {
        std::cout << "Cant open file!!\n";
    }

    size = 5;


    stream1.seekg((index) * (sizeof(int) * (5 + 1) /*5 za danni 1 za size*/), std::ios::beg);
    stream1.seekp((index) * (sizeof(int) * (5 + 1)), std::ios::beg);

    size = getSizeOfBooksInRead();

    stream1.write(reinterpret_cast<const char*>(&size), sizeof(int));
    for (int i = 0; i < 5; i++)
    {
        stream1.write(reinterpret_cast<const char*>(&this->booksInReadByMonth[i]), sizeof(int));
    }

    stream1.close();



    //almost same for readedBooks
    std::ofstream readedBooksStream("readedBooks.bin", std::ios::binary);
    if (!readedBooksStream.is_open())
    {
        std::cout << "Cant open file!!\n";
    }

    readedBooksStream.seekp(0, std::ios::end);

    size = getSizeOfReadedBooks();

    readedBooksStream.write(reinterpret_cast<const char*>(&size), sizeof(int));

    for (int i = 0; i < size; i++)
    {
        readedBooksStream.write(reinterpret_cast<const char*>(&this->readedBooks[i]), sizeof(int));
    }


    readedBooksStream.close();
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
        stream.seekg(sizeof(int), std::ios::cur);

        stream.seekg(sizeof(int) * 5, std::ios::cur);
    }

    //stigaiki zapochvame da chetem
    stream.read(reinterpret_cast<char*>(&size), sizeof(int));

    setSizeOfBooksInRead(size);

    booksInRead = new int[5];

    for (size_t i = 0; i < 5; i++)
    {
        stream.read(reinterpret_cast<char*>(&this->booksInRead[i]), sizeof(int));
    }

    stream.close();



    //sushtoto no za booksInReadByMonth
    std::ifstream stream1("booksInReadByMonth.bin", std::ios::binary);

    if (!stream1.is_open())
    {
        std::cout << "Cant open file!!\n";
    }

    //pochvame 
    stream1.seekg(0, std::ios::beg);

    //chetem do kato ne stignem do index-a (masiva ot knigi za tozi user)
    for (size_t i = 0; i < index; i++)
    {
        stream1.seekg(sizeof(int), std::ios::cur);

        stream1.seekg(sizeof(int) * 5, std::ios::cur);
    }

    //stigaiki zapochvame da chetem

    //TODO tuka mai neshto ne se chete kot trqqqq ili ne mai

    booksInReadByMonth = new int[5];
    stream1.seekg(sizeof(int), std::ios::cur);

    for (size_t i = 0; i < 5; i++)
    {
        stream1.read(reinterpret_cast<char*>(&this->booksInReadByMonth[i]), sizeof(int));
        //stream.read(reinterpret_cast<char*>(&size), sizeof(int));
    }

    stream1.close();


    std::ifstream readedBooksStream("readedBooks.bin", std::ios::binary);
    for (size_t i = 0; i < index; i++)
    {
        readedBooksStream.read(reinterpret_cast<char*>(&size), sizeof(int));
        readedBooksStream.seekg(sizeof(int)*size, std::ios::cur);
    }

    readedBooksStream.read(reinterpret_cast<char*>(&size), sizeof(int));
    readedBooks = new int[size];

    for (size_t i = 0; i < size; i++)
    {
        readedBooksStream.read(reinterpret_cast<char*>(&this->readedBooks[i]), sizeof(int));
    }

    readedBooksStream.close();

    printReadBooks();
}

void User::setBookInRead(int libNum, short month)
{
    //TODO FIX THE FUNC THE PURPOSE OF IT FOR NOW IT IS ONLY TO INITIALIZE !!!!!!!!!
    intializeBooksInRead(getSizeOfBooksInRead());

    booksInRead[getSizeOfBooksInRead()] = libNum;
    booksInReadByMonth[getSizeOfBooksInRead()] = month;
    
    setSizeOfBooksInRead(getSizeOfBooksInRead() + 1);
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
    //trqbva da fixnem booksInRead masiva
    size_t indexOfArrToRemove = 0;

    for (int i = 0; i < 5; i++)
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
    
}


void User::printReadBooks()
{

    std::cout << "Book In Read: " << std::endl;

    for (int i = 0; i < getSizeOfBooksInRead(); i++)
    {
        std::cout << "LibNum: " << booksInRead[i] << std::endl;
        std::cout << "Month: " << booksInReadByMonth[i] << std::endl;
        std::cout << std::endl;
    }

    std::cout << std::endl << std::endl << "Read books: " << std::endl;

    for (int i = 0; i < getSizeOfReadedBooks(); i++)
    {
        std::cout << "LibNum: " << readedBooks[i] << std::endl;
        std::cout << std::endl;
    }
    std::cout << std::endl << std::endl << std::endl;
}


//TODO
void User::intializeBooksInRead(int newSize)
{
    int* books = new int[newSize];
    int* booksInReadByMonth = new int[newSize];
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
    this->booksInRead = new int[5];
    this->booksInReadByMonth = new int[5];

    //from newSize to getSizeOfBooksInRead()
    for (int i = 0; i < getSizeOfBooksInRead(); i++)
    {
        this->booksInRead[i] = books[i];
        this->booksInReadByMonth[i] = booksInReadByMonth[i];
    }

    delete[] books;
    delete[] booksInReadByMonth;


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
