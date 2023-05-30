#include "Library.h"
#pragma warning (disable:4996)

Library::Library()
    //:
    //bookStream("books.bin", std::ios::binary, std::ios::in),
    //comicSream("comic.bin", std::ios::binary), 
    //periodicalStream("periodical.bin", std::ios::binary)
{
    openStreams();
    setCurrentBookSize(sizeOfBookFile(bookStream));
    setCurrentComicsSize(sizeOfComicFile(comicSream));
    setCurrentPeriodicalSize(sizeOfPeriodicalFile(periodicalStream));
    setCurrentUserSize(sizeOfUsersFile(userStream));

    users = new User[getCurrentUserSize()];
    books = new Book[getCurrentBookSize()];
    comics = new Comics[getCurrentComicsSize()];
    periodicals = new Periodical[getCurrentPeriodicalSize()];

    loadBooks();
}

//Library::Library(const Library& lib)
//{
//}

//Library& Library::operator=(const Library& lib)
//{
//    // TODO: insert return statement here
//}

void Library::openStreams() 
{
    bookStream.open("books.bin", std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);
    if (!bookStream.is_open())
    {
        std::cout << "Can't open file books.bin!!!";
        return;
    }

    comicSream.open("comic.bin", std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);
    if (!comicSream.is_open())
    {
        std::cout << "Can't open file comic.bin!!!";
        return;
    }

    periodicalStream.open("periodical.bin", std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);
    if (!periodicalStream.is_open())
    {
        std::cout << "Can't open file periodical.bin!!!";
        return;
    }
    
    userStream.open("users.bin", std::ios::binary | std::ios::out | std::ios::in | std::ios::ate);
    if (!periodicalStream.is_open())
    {
        std::cout << "Can't open file users.bin!!!";
        return;
    }

}

void Library::loadBooks()
{
    bookStream.seekg(0, std::ios::beg);
    bookStream.seekp(0, std::ios::beg);
    std::cout << "\n Loading Books...\n";
    for (int i = 0; i < getCurrentBookSize(); i++)
    {
        bookStream.read(reinterpret_cast<char*>(&this->books[i]), sizeof(Book));
    }


    comicSream.seekg(0, std::ios::beg);
    comicSream.seekp(0, std::ios::beg);
    std::cout << "\n Loading Comics...\n";
    for (int i = 0; i < getCurrentComicsSize(); i++)
    {
        comicSream.read(reinterpret_cast<char*>(&this->comics[i]), sizeof(Comics));
    }

    periodicalStream.seekg(0, std::ios::beg);
    periodicalStream.seekp(0, std::ios::beg);
    std::cout << "\n Loading Periodicals...\n";
    for (int i = 0; i < getCurrentPeriodicalSize(); i++)
    {
        periodicalStream.read(reinterpret_cast<char*>(&this->periodicals[i]), sizeof(Periodical));
    }

    numOfPaper = getCurrentBookSize() + getCurrentComicsSize() + getCurrentPeriodicalSize();

    userStream.seekg(0, std::ios::beg);
    userStream.seekp(0, std::ios::beg);
    std::cout << "\n Loading Users...\n";
    for (int i = 0; i < getCurrentUserSize(); i++)
    {
        userStream.read(reinterpret_cast<char*>(&this->users[i]), sizeof(User));
        users[i].loadBooks(i);
    }

    print();

}

void Library::getTypeOfPaperFromNum(unsigned int libNum, char* type)
{

    for (size_t i = 0; i < getCurrentBookSize() && i < getCurrentComicsSize() && i < getCurrentPeriodicalSize(); i++)
    {
        if (i <= getCurrentBookSize())
        {
            if (libNum == books[i].libNumber)
            {
                strcpy(type, "book");
                return;
            }
        }

        if (i <= getCurrentComicsSize())
        {
            if (libNum == comics[i].libNumber)
            {
                strcpy(type, "comics");
                return;
            }
        }

        if (i <= getCurrentPeriodicalSize())
        {
            if (libNum == periodicals[i].libNumber)
            {
                strcpy(type, "periodicals");
                return;
            }
        }
    }
    std::cout << "Error number!!!";
}

void Library::resizeBooksArr(size_t newSize)
{
    Book* books = new Book[newSize];
    for (int i = 0; i < getCurrentBookSize(); i++)
    {
        if (i <= newSize)
        {
           books[i] = this->books[i];
        }
    }

    delete[] this->books;
    this->books = new Book[newSize];

    for (int i = 0; i < newSize; i++)
    {
        this->books[i] = books[i];
    }

    delete[] books;

    //std::cout << "\n couting the authors and titles from obj arr: \n";
    //for (int i = 0; i < getCurrentBookSize(); i++)
    //{
    //    std::cout << "Author: " << this->books[i].autor << '\n';
    //    std::cout << "Title: " << this->books[i].title << '\n';
    //}

    setCurrentBookSize(newSize);
}

void Library::addComics(std::fstream& stream)
{
    char input[1024];
    int in;
    std::cout << "Title: ";
    std::cin.ignore();
    std::cin.getline(input, 1024);
    strcpy(comics[getCurrentComicsSize() - 1].title, input);

    std::cout << "Author: ";
    std::cin.getline(input, 1024);
    strcpy(comics[getCurrentComicsSize() - 1].autor, input);

    std::cout << "Publisher: ";
    std::cin.getline(input, 1024);
    strcpy(comics[getCurrentComicsSize() - 1].publisher, input);

    std::cout << "Genre: ";
    std::cin >> comics[getCurrentComicsSize() - 1].genre;

    std::cout << "Short description about the book: ";
    std::cin.ignore();
    std::cin.getline(input, 1024);
    strcpy(comics[getCurrentComicsSize() - 1].shortDescription, input);

    
    std::cout << "Periodicity: \n 1. Every week \n 2. Every month \n 3.Every year \n Enter with charchters (week, month or year) \n";

    while (strcmp(input, "week") && strcmp(input, "year") && strcmp(input, "month"))
    {
        std::cin.getline(input, 1024);
    }
    strcpy(comics[getCurrentComicsSize() - 1].periodicity, input);


    std::cout << "Quantity: ";
    std::cin >> in;
    comics[getCurrentComicsSize() - 1].quantity = in;

    std::cout << "Year of issue: ";
    std::cin >> in;
    comics[getCurrentComicsSize() - 1].dateOfIssue = in;

    ++numOfPaper;
    comics[getCurrentComicsSize() - 1].libNumber = numOfPaper;

    //stream.seekg(0, std::ios::end);
    //stream.seekp(0, std::ios::end);
    //stream.write(reinterpret_cast<const char*>(&books[getCurrentComicsSize() - 1]), sizeof(Book));
}

void Library::resizeComicsArr(size_t newSize)
{
    Comics* comics = new Comics[newSize];
    for (int i = 0; i < getCurrentComicsSize(); i++)
    {
        if (i <= newSize)
        {
            comics[i] = this->comics[i];
        }
    }

    delete[] this->comics;
    this->comics = new Comics[newSize];

    for (int i = 0; i < newSize; i++)
    {
        this->comics[i] = comics[i];
    }

    delete[] comics;

    std::cout << "\n couting the authors and titles from obj arr: \n";
    for (int i = 0; i < getCurrentComicsSize(); i++)
    {
        std::cout << "Author: " << this->comics[i].autor << '\n';
        std::cout << "Num:   " << this->comics[i].libNumber << '\n';
        std::cout << "Title: " << this->comics[i].title << '\n' << '\n';
    }

    setCurrentComicsSize(newSize);
}

void Library::addPeriodicals(std::fstream& stream)
{
    char input[1024];
    int in;
    std::cout << "Title: ";
    std::cin.ignore();
    std::cin.getline(input, 1024);
    strcpy(periodicals[getCurrentPeriodicalSize() - 1].title, input);

    std::cout << "Short description about the book: ";
    std::cin.ignore();
    std::cin.getline(input, 1024);
    strcpy(periodicals[getCurrentPeriodicalSize() - 1].shortDescription, input);


    std::cout << "Periodicity: \n 1. Every week \n 2. Every month \n 3.Every year \n Enter with charchters (week, month or year) \n";

    while (strcmp(input, "week") && strcmp(input, "year") && strcmp(input, "month"))
    {
        std::cin.getline(input, 1024);
    }
    strcpy(periodicals[getCurrentPeriodicalSize() - 1].periodicity, input);


    std::cout << "Quantity: ";
    std::cin >> in;
    periodicals[getCurrentPeriodicalSize() - 1].quantity = in;


    std::cout << "Year of issue: ";
    std::cin >> in;
    periodicals[getCurrentPeriodicalSize() - 1].dateOfIssue = in;

    ++numOfPaper;
    periodicals[getCurrentPeriodicalSize() - 1].libNumber = numOfPaper;

    //stream.seekg(0, std::ios::end);
    //stream.seekp(0, std::ios::end);
    //stream.write(reinterpret_cast<const char*>(&books[getCurrentPeriodicalSize() - 1]), sizeof(Book));
}

void Library::resizePeriodicalssArr(size_t newSize)
{
    Periodical* periodicals = new Periodical[newSize];
    for (int i = 0; i < getCurrentPeriodicalSize(); i++)
    {
        if (i <= newSize)
        {
            periodicals[i] = this->periodicals[i];
        }
    }

    delete[] this->periodicals;
    this->periodicals = new Periodical[newSize];

    for (int i = 0; i < newSize; i++)
    {
        this->periodicals[i] = periodicals[i];
    }

    delete[] periodicals;

    std::cout << "\n couting the authors and titles from obj arr: \n";
    for (int i = 0; i < getCurrentPeriodicalSize(); i++)
    {
        std::cout << "Num:   " << this->periodicals[i].libNumber << '\n';
        std::cout << "Title: " << this->periodicals[i].title << '\n' << '\n';
    }

    setCurrentPeriodicalSize(newSize);
}

void Library::resizeUserArr(size_t newSize)
{
    User* users = new User[newSize];
    for (int i = 0; i < getCurrentUserSize(); i++)
    {
        if (i <= newSize)
        {
            users[i] = this->users[i];
        }
    }



    delete[] this->users;
    this->users = new User[newSize];


    //TODO moje bi tuk e problema shtot user nqma operatr= i copy constructor

    for (int i = 0; i < newSize; i++)
    {
        this->users[i] = users[i];
    }

    delete[] users;

    std::cout << "\n couting the users: \n";
    for (int i = 0; i < getCurrentUserSize(); i++)
    {
        char name[128];
        this->users[i].getName(name);
        std::cout << "Num:   " << name << '\n';
    }

    setCurrentUserSize(newSize);
}

void Library::addUser(char* input)
{
    std::cout << "Name: ";
    std::cin.getline(input, 1024);

    resizeUserArr(getCurrentUserSize() + 1);
    users[getCurrentUserSize() - 1].setName(input);
}

void Library::giveABook(char* command)
{
    unsigned int libNum;
    unsigned short month;
    std::cout << "To: ";
    std::cin >> command;
   

    int targetUser = 0;
    char name[1024];
    //TODO if username doesnt exist
    for (size_t i = 0; i < getCurrentUserSize(); i++)
    {
        users[i].getName(name);
        if (!strcmp(name, command))
        {
            strcpy(name, command);
            targetUser = i;
            break;
        }
    }

    std::cout << "In which month the book was taken? :\n month number - ";
    std::cin >> month;
    std::cout << "Library number: ";
    std::cin >> libNum;
    
    //TODO if such paper exists than is it a book or a comic ..
    
    users[targetUser].printBooksInRead();
    users[targetUser].setBookInRead(libNum, month);

    //getTypeOfPaperFromNum(libNum, typeOfPaper);

}

void Library::reciveABook(char* command)
{
    unsigned int libNum;
    std::cout << "From: ";
    std::cin >> command;


    int targetUser = 0;
    char name[1024];
    //TODO if username doesnt exist
    for (size_t i = 0; i < getCurrentUserSize(); i++)
    {
        users[i].getName(name);
        if (!strcmp(name, command))
        {
            strcpy(name, command);
            targetUser = i;
            break;
        }
    }

    std::cout << "Library number: ";
    std::cin >> libNum;

    users[targetUser].setBookReaded(libNum);
}

void Library::overduePaper(char* command)
{
    unsigned short month;
    std::cout << "Month: ";
    std::cin >> month;

    //burkame bazata na vseki user i gledame koi knigi sa zakusneli (na koito currentMonth - 1 > getedMonth)

    //v nai loshiqt sluchai shte sa vzeti vsichki knigi
    int* overduedPaper = new int[getCurrentBookSize() + getCurrentComicsSize() + getCurrentPeriodicalSize()];
    size_t overduedPaperIndex = 0;
    for (size_t i = 0; i < getCurrentUserSize(); i++)
    {
        for (size_t j = 0; j < users[i].getSizeOfBooksInRead(); j++)
        {
            //ako e knigata e presorochena q zapisvai v overduedPaper[]
            if (users[i].booksInReadByMonth[j] < month - 1)
            {
                //pulni overduedPaper s libNum-ovete koito sa presrocheni
                overduedPaper[overduedPaperIndex] = users[i].booksInRead[j];
                ++overduedPaperIndex;
            }
        }
    }
    int* sortedArr = new int[getCurrentBookSize()];
    sortOverduedPaper(overduedPaper, overduedPaperIndex, sortedArr);


    //printeing sorted Book by their year

    for (size_t i = 0; i < overduedPaperIndex; i++)
    {
        printBookWithLibNum(sortedArr[i]);
    }

    delete[] sortedArr;
    delete[] overduedPaper;
}

void Library::sortOverduedPaper(int* arrOfLibNumsToSort, size_t size, int* sortedArr)
{
    //trqbva da sortirame vsichki bookove po godina i da gi cout-nem
    // sled tova da gi izkaram po zaglavie book-ovete
    //sled tova trqq da sortirame periodicalite i comicsite po quantyty a ako e ednakvo po zaglavie



    //1. mianavame prez vsichki book-ove i gi sravnqvame sus arrOfLibNumsToSort i tezi koito suvpadat

    //TODO 1. ako libNuma e kniga 2. i ako e nai malkata 3. q pisha

    int newest = 0;
    int indexOFsorterdArr = 0;
    char type[16];
    for (size_t i = 0; i < size; i++)
    {
        for (int j = 0; j < getCurrentBookSize(); j++)
        {
            getTypeOfPaperFromNum(arrOfLibNumsToSort[j], type);
            if (!strcmp("book", type) && !libNumExistInArr(sortedArr, indexOFsorterdArr, arrOfLibNumsToSort[j]) && newest <= arrOfLibNumsToSort[j])
            {
                newest = arrOfLibNumsToSort[j];
            }
        }

        sortedArr[indexOFsorterdArr] = newest;
        ++indexOFsorterdArr;
    }

}

bool Library::libNumExistInArr(int* arr, int size, int num)
{
    for (size_t i = 0; i < size; i++)
    {
        if (arr[i] == num)
        {
            return true;
        }
    }
    return false;
}

void Library::libSave()
{

    //std::cout << "\n couting the authors and titles from obj arr: \n";
    //for (int i = 0; i < getCurrentBookSize(); i++)
    //{
    //    std::cout << "Author: " << this->books[i].autor << '\n';
    //    std::cout << "Num:   " << this->books[i].libNumber << '\n';
    //    std::cout << "Title: " << this->books[i].title << '\n' << '\n';
    //}

    //restarting the stream with trunc
    bookStream.close();
    bookStream.open("books.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);

    for (int i = 0; i < getCurrentBookSize(); i++)
    {
        if (books[i].libNumber != 0)
        {
            bookStream.write(reinterpret_cast<const char*>(&books[i]), sizeof(Book));
        }
    }

    comicSream.close();
    comicSream.open("comic.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);

    for (int i = 0; i < getCurrentComicsSize(); i++)
    {
        if (comics[i].libNumber != 0)
        {
            comicSream.write(reinterpret_cast<const char*>(&comics[i]), sizeof(Comics));
        }
    }

    periodicalStream.close();
    periodicalStream.open("periodical.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);

    for (int i = 0; i < getCurrentPeriodicalSize(); i++)
    {
        if (periodicals[i].libNumber != 0)
        {
            periodicalStream.write(reinterpret_cast<const char*>(&periodicals[i]), sizeof(Periodical));
        }
    }

    userStream.close();
    userStream.open("users.bin", std::ios::in | std::ios::out | std::ios::binary | std::ios::trunc);

    for (int i = 0; i < getCurrentUserSize(); i++)
    {
        users[i].saveBooks(i);
        userStream.write(reinterpret_cast<const char*>(&users[i]), sizeof(User));
    }
    

    std::cout << "Printing end:: \n";
    print();
}

short Library::sizeOfBookFile(std::fstream& stream)
{
    stream.seekg(0, std::ios::end);
    short size = stream.tellg() / sizeof(Book);

    stream.clear();
    
    return size;
}

short Library::sizeOfComicFile(std::fstream& stream)
{
    stream.seekg(0, std::ios::end);
    short size = stream.tellg() / sizeof(Comics);

    stream.clear();
    return size;
}

short Library::sizeOfPeriodicalFile(std::fstream& stream)
{
    stream.seekg(0, std::ios::end);
    short size = stream.tellg() / sizeof(Periodical);

    stream.clear();
    return size;
}

short Library::sizeOfUsersFile(std::fstream& stream)
{
    stream.seekg(0, std::ios::end);
    short size = stream.tellg() / sizeof(User);

    stream.clear();
    return size;
}

void Library::setCurrentBookSize(int size)
{
    this->currentBookSize = size;
}

int Library::getCurrentBookSize()
{
    return currentBookSize;
}

void Library::setCurrentComicsSize(int size)
{
    this->currentComicsSize = size;
}

int Library::getCurrentComicsSize()
{
    return currentComicsSize;
}

void Library::setCurrentPeriodicalSize(int size)
{
    this->currentPeriodicalSize = size;
}

int Library::getCurrentPeriodicalSize()
{
    return currentPeriodicalSize;
}

void Library::setCurrentUserSize(int size)
{
    this->currentUsersSize = size;
}

int Library::getCurrentUserSize()
{
    return currentUsersSize;
}


Library::~Library()
{
    bookStream.close();
    comicSream.close();
    periodicalStream.close();
    
    delete[] books;
    delete[] comics;
    delete[] periodicals;
    delete[] users;
}

void Library::addPaper(char* command)
{

    std::cout << "What do you want to add: \n 1. Book \n 2. Comics \n 3. Periodical \n (enter with letters) \n - ";
    std::cin >> command;
    std::cout << std::endl;
    if (!strcmp(command, "Book"))
    {
        resizeBooksArr(getCurrentBookSize() + 1);
        addBook(bookStream);
    }
    else if (!strcmp(command, "Comics"))
    {
        resizeComicsArr(getCurrentComicsSize() + 1);
        addComics(comicSream);
    }
    else if (!strcmp(command, "Periodical"))
    {
        resizePeriodicalssArr(getCurrentPeriodicalSize() + 1);
        addPeriodicals(periodicalStream);
    }
}

void Library::removePaper(char* command)
{
    int num;
    std::cout << "Remove paper number: ";
    std::cin >> num;
    if (num > numOfPaper || num <= 0)
    {
        std::cout << "The paper with a num:" << num << " doesn't exist \n";
    }
    else
    {
        //trq da markirame book-a s nnomer = num s libnum = 0

        for (int i = 0; i < getCurrentBookSize(); i++)
        {
            if (books[i].libNumber == num)
            {
                //marking it with 0 => it will be ignored when saving the arr to the file
                this->books[i].libNumber = 0;
                return;
            }
        }

        for (int i = 0; i < getCurrentComicsSize(); i++)
        {
            if (comics[i].libNumber == num)
            {
                //marking it with 0 => it will be ignored when saving the arr to the file
                this->comics[i].libNumber = 0;
                return;
            }
        }

        for (int i = 0; i < getCurrentPeriodicalSize(); i++)
        {
            if (periodicals[i].libNumber == num)
            {
                //marking it with 0 => it will be ignored when saving the arr to the file
                this->periodicals[i].libNumber = 0;
                return;
            }
        }
    }
}

void Library::addBook(std::fstream& stream)
{ 
    char input[1024];
    std::cout << "Title: ";
    std::cin.ignore();
    std::cin.getline(input, 1024);
    strcpy(books[getCurrentBookSize() - 1].title, input);

    std::cout << "Author: ";
    std::cin.getline(input, 1024);
    strcpy(books[getCurrentBookSize() - 1].autor, input);

    std::cout << "Publisher: ";
    std::cin.getline(input, 1024);
    strcpy(books[getCurrentBookSize() - 1].publisher, input);

    std::cout << "Genre: ";
    books[getCurrentBookSize() - 1].setGenre();

    std::cout << "Short description about the book: ";
    std::cin.ignore();
    std::cin.getline(input, 1024);
    strcpy(books[getCurrentBookSize() - 1].shortDescription, input);

    std::cout << "Date of issue: ";
    std::cin >> books[getCurrentBookSize() - 1].dateOfIssue;

    ++numOfPaper;
    books[getCurrentBookSize() - 1].libNumber = numOfPaper;

    //stream.seekg(0, std::ios::end);
    //stream.seekp(0, std::ios::end);
    //stream.write(reinterpret_cast<const char*>(&books[getCurrentBookSize() - 1]), sizeof(Book));
    
}

void Library::print()
{
    std::cout << "\n \n BOOKS: \n";
    char ch[16];
    char ty[16];
    char au[16];
    for (int i = 0; i < getCurrentBookSize(); i++)
    {
        std::cout << "Author: " << this->books[i].autor << '\n';
        std::cout << "Num:   " << this->books[i].libNumber << '\n';
        std::cout << "Short Description: " << this->books[i].shortDescription << '\n';
        std::cout << "Title: " << this->books[i].title;
        books[i].getGenre(ch, ty, au);
    }

    std::cout << "COMICS: \n";
    for (int i = 0; i < getCurrentComicsSize(); i++)
    {
        std::cout << "Author: " << this->comics[i].autor << '\n';
        std::cout << "Num:   " << this->comics[i].libNumber << '\n';
        std::cout << "Title: " << this->comics[i].title << '\n' << '\n';
    }

    std::cout << "PERIODICALS: \n";
    for (int i = 0; i < getCurrentPeriodicalSize(); i++)
    {
        std::cout << "Num:   " << this->periodicals[i].libNumber << '\n';
        std::cout << "Title: " << this->periodicals[i].title << '\n' << '\n';
    }

    std::cout << "USERS: \n";
    char name[128];
    for (int i = 0; i < getCurrentUserSize(); i++)
    {
        this->users[i].getName(name);
        std::cout << "Name:   " << name << '\n';
    }
}

void Library::printBookWithLibNum(int libNum)
{
    for (size_t i = 0; i < getCurrentBookSize(); i++)
    {
        if (libNum == books->libNumber)
        {
            std::cout << '\n' << books[i].title << '\n';
            std::cout << '\n' << books[i].autor<< '\n';
            std::cout << "\n YEAR : " << books[i].title << '\n';
        }
    }
    std::cout << "\n Book with libNum: " << libNum << " NOT FOUND!!!";
}
