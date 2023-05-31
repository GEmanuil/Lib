#include "Library.h"
#pragma warning (disable:4996)

Library::Library()
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
    for (int i = 0; i < getCurrentBookSize(); i++)
    {
        bookStream.read(reinterpret_cast<char*>(&this->books[i]), sizeof(Book));
    }


    comicSream.seekg(0, std::ios::beg);
    for (int i = 0; i < getCurrentComicsSize(); i++)
    {
        comicSream.read(reinterpret_cast<char*>(&this->comics[i]), sizeof(Comics));
    }

    periodicalStream.seekg(0, std::ios::beg);
    for (int i = 0; i < getCurrentPeriodicalSize(); i++)
    {
        periodicalStream.read(reinterpret_cast<char*>(&this->periodicals[i]), sizeof(Periodical));
    }

    numOfPaper = getCurrentBookSize() + getCurrentComicsSize() + getCurrentPeriodicalSize();

    userStream.seekg(0, std::ios::beg);
    for (int i = 0; i < getCurrentUserSize(); i++)
    {
        userStream.read(reinterpret_cast<char*>(&this->users[i]), sizeof(User));
        users[i].loadBooks(i);
    }

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
    comics[getCurrentComicsSize() - 1].setGenre();

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


    for (int i = 0; i < newSize; i++)
    {
        this->users[i] = users[i];
    }

    delete[] users;


    setCurrentUserSize(newSize);
}

void Library::addUser(char* input)
{
    std::cout << "Name: ";
    std::cin.getline(input, 1024);
    char name[128];

    //check if user with a name == input exists
    for (size_t i = 0; i < getCurrentUserSize(); i++)
    {
        users[i].getName(name);
        if (!strcmp(input, name))
        {
            std::cout << "User with a name: " << input << " already exists. \n";
            return;
        }
    }

    resizeUserArr(getCurrentUserSize() + 1);
    users[getCurrentUserSize() - 1].setName(input);
}

void Library::removeUser(char* command)
{
    char name1[128];
    char name2[128];
    std::cout << "Name of user: ";
    std::cin >> name1;

    int indexOfUserToRemove = 0;
    for (size_t i = 0; i < getCurrentUserSize(); i++)
    {
        users[i].getName(name2);
        if (!strcmp(name1, name2))
        {
            indexOfUserToRemove = i;
        }
    }

    users[indexOfUserToRemove] = users[getCurrentUserSize() - 1];
    setCurrentUserSize(getCurrentUserSize() - 1);
    std::cout << "The user will be removed when library closed." << std::endl;
}

void Library::giveAPaper(char* command) 
{
    unsigned int libNum;
    unsigned short month;
    char name[128];
    std::cout << "To: ";
    std::cin >> command;

    if (!checkIfUserExists(command))
    {
        std::cout << "User with a name " << command << " doesn't exists. " << std::endl;
        return;
    }

    int targetUser = 0;
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


    if (users[targetUser].getSizeOfBooksInRead() >= 5)
    {
        std::cout << "The user can't have more than 5 papers \n";
        return;
    }


    std::cout << "In which month the paper was taken? :\n month number - ";
    std::cin >> month;
    std::cout << "Library number: ";
    std::cin >> libNum;

    if (!checkIfLibNumExists(libNum))
    {
        std::cout << "Paper with libNum: " << libNum << " doesn't exists";
        return;
    }    

    users[targetUser].setBookInRead(libNum, month);
    
}

void Library::reciveABook(char* command)
{
    unsigned int libNum;
    std::cout << "From: ";
    std::cin >> command;


    int targetUser = 0;
    char name[1024];

    if (!checkIfUserExists(command))
    {
        std::cout << "User with a name " << command << " doesn't exists. " << std::endl;
        return;
    }


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


    if (!checkIfLibNumExists(libNum))
    {
        std::cout << "Paper with libNum: " << libNum << " doesn't exists";
        return;
    }


    users[targetUser].setBookReaded(libNum);
}

void Library::overduePaper(char* command)
{
    int month;
    std::cout << "Month: ";
    std::cin >> month;

    //burkame bazata na vseki user i gledame koi knigi sa zakusneli (na koito currentMonth - 1 > getedMonth)

    //v nai loshiqt sluchai vseki user shte ima po 5 knigi
    int* overduedPaper = new int[getCurrentUserSize()*5];
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
        printBookWithLibNum(overduedPaper[i]);
    }

    delete[] sortedArr;
    delete[] overduedPaper;
}

void Library::overdueUsers(char* command)
{
    int month;
    std::cout << "Month: ";
    std::cin >> month;
    char name[128];
    for (size_t i = 0; i < getCurrentUserSize(); i++)
    {
        for (size_t j = 0; j < users[i].getSizeOfBooksInRead(); j++)
        {
            if (users[i].booksInReadByMonth[j] < month - 1)
            {
                users[i].getName(name);
                std::cout << "Name: " << name << std::endl;
                std::cout << "overdued book: " << users[i].booksInRead[j] << std::endl;
            }
        }
    }
}

void Library::infUsers(char* command)
{
    int* userIndexesSortedArr = new int[getCurrentUserSize()];
    int userIndex = 0;
    int numOfReadedBooks = INT_MAX;
    char name[128];
    for (size_t i = 0; i < getCurrentUserSize(); i++)
    {
        for (size_t j = 0; j < getCurrentUserSize(); j++)
        {
            //tursim usera s nai-malko procheteni knigi
            if (numOfReadedBooks > users[j].getSizeOfReadedBooks() && !libNumExistInArr(userIndexesSortedArr, getCurrentUserSize(), j))
            {
                numOfReadedBooks = users[j].getSizeOfReadedBooks();
                userIndex = j;
            }
        }
        userIndexesSortedArr[i] = userIndex;
        users[userIndex].getName(name);
        numOfReadedBooks = INT_MAX;
        std::cout << "User: " << name << '\n';
        std::cout << "number of readed books: " << users[userIndex].getSizeOfReadedBooks() << '\n';
    }

    delete[] userIndexesSortedArr;
}

void Library::sortOverduedPaper(int* arrOfLibNumsToSort, size_t size, int* sortedArr)
{

    int newest = 0;
    int indexOFsorterdArr = 0;
    char type[16];
    for (size_t i = 0; i < size; i++)
    {
        for (int j = 0; j < getCurrentBookSize(); j++)
        {
            if (!libNumExistInArr(sortedArr, indexOFsorterdArr, arrOfLibNumsToSort[j]) && newest <= arrOfLibNumsToSort[j])
            {
                newest = arrOfLibNumsToSort[j];
            }
        }

        sortedArr[indexOFsorterdArr] = newest;
        ++indexOFsorterdArr;
    }

}

bool Library::libNumExistInArr(int* arr, int size, int num) const
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

bool Library::checkIfLibNumExists(int libNUm) const
{
    for (size_t i = 0; i < getCurrentBookSize(); i++)
    {
        if (books[i].libNumber == libNUm)
        {
            return true;
        }
    }

    for (size_t i = 0; i < getCurrentComicsSize(); i++)
    {
        if (comics[i].libNumber == libNUm)
        {
            return true;
        }
    }

    for (size_t i = 0; i < getCurrentPeriodicalSize(); i++)
    {
        if (periodicals[i].libNumber == libNUm)
        {
            return true;
        }
    }
    return false;
}

bool Library::checkIfUserExists(char* name) const
{
    char name2[128];
    for (size_t i = 0; i < getCurrentUserSize(); i++)
    {
        users[i].getName(name2);
        if (!strcmp(name, name2))
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

    //truncing  readedBooks.bin file
    std::fstream readedBooksStream("readedBooks.bin", std::ios::binary | std::ios::trunc | std::ios::in | std::ios::out);
    readedBooksStream.close();

    for (int i = 0; i < getCurrentUserSize(); i++)
    {
        if (users[i].getSizeOfBooksInRead() != 0 || users[i].getSizeOfReadedBooks() != 0)
        {
            users[i].saveBooks(i);
        }

        userStream.write(reinterpret_cast<const char*>(&users[i]), sizeof(User));

    }


    //std::cout << "Printing end:: \n";
    //print();
}

void Library::help() const
{
    std::cout << "open - opens the library (must enter do to use the other commands)\n";
    std::cout << "\tAvailable commands:\n";
    std::cout << "\tadd paper: Add a new paper to the library.\n";
    std::cout << "\tprint: Print the list of papers and users in the library.\n";
    std::cout << "\tremove paper: Remove a paper from the library.\n";
    std::cout << "\tcreate user: Add a new user to the library.\n";
    std::cout << "\tremove user: Remove a user from the library.\n";
    std::cout << "\tgive: Assign a paper to a user.\n";
    std::cout << "\treceive: Receive a paper from a user.\n";
    std::cout << "\toverdue: overdue papers.\n";
    std::cout << "\toverdue users: List users with overdue papers.\n";
    std::cout << "\thelp: show help.\n";
    std::cout << "\tinformation about users: Display information about all users for their books.\n";
    std::cout << "close - closes the library\n";

}

void Library::checkWhatIsInReadedBooksFIle()
{

    std::ifstream stream("readedBooks.bin", std::ios::binary);
    if (!stream.is_open())
    {
        std::cout << "Cant open file!!!";
    }

    int size = 0;
    int var = 0;
    stream.seekg(0, std::ios::beg);

    while (stream.read(reinterpret_cast<char*>(&size), sizeof(int)))
    {
        std::cout << "Size of User: " << size << std::endl;

        for (size_t i = 0; i < size; i++)
        {
            stream.read(reinterpret_cast<char*>(&var), sizeof(int));
            std::cout << "read book: " << var << std::endl;

        }
    }
    stream.close();
}

short Library::sizeOfBookFile(std::fstream& stream) const
{
    stream.seekg(0, std::ios::end);
    short size = stream.tellg() / sizeof(Book);

    stream.clear();
    
    return size;
}

short Library::sizeOfComicFile(std::fstream& stream) const
{
    stream.seekg(0, std::ios::end);
    short size = stream.tellg() / sizeof(Comics);

    stream.clear();
    return size;
}

short Library::sizeOfPeriodicalFile(std::fstream& stream) const
{
    stream.seekg(0, std::ios::end);
    short size = stream.tellg() / sizeof(Periodical);

    stream.clear();
    return size;
}

short Library::sizeOfUsersFile(std::fstream& stream) const
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

int Library::getCurrentBookSize() const
{
    return currentBookSize;
}

void Library::setCurrentComicsSize(int size)
{
    this->currentComicsSize = size;
}

int Library::getCurrentComicsSize() const
{
    return currentComicsSize;
}

void Library::setCurrentPeriodicalSize(int size)
{
    this->currentPeriodicalSize = size;
}

int Library::getCurrentPeriodicalSize() const
{
    return currentPeriodicalSize;
}

void Library::setCurrentUserSize(int size)
{
    this->currentUsersSize = size;
}

int Library::getCurrentUserSize() const
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
        this->users[i].printReadBooks();
    }
}

void Library::printBookWithLibNum(int libNum)
{
    for (size_t i = 0; i < getCurrentBookSize(); i++)
    {
        if (libNum == books->libNumber)
        {
            std::cout << '\n' << books[i].title << '\n';
            std::cout << '\n' << books[i].autor << '\n';
            std::cout << "\n YEAR : " << books[i].dateOfIssue << '\n';
        }
    }
}
