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
    setCurrentComicsSize(sizeOfComicFile(bookStream));

    books = new Book[getCurrentBookSize()];
    comics = new Comics[sizeOfComicFile(comicSream)];
    periodicals = new Periodical[sizeOfPeriodicalFile(periodicalStream)];

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

    numOfPaper = getCurrentBookSize();
    std::cout << "\n couting the authors and titles from obj arr: \n";
    for (int i = 0; i < getCurrentBookSize(); i++)
    {
        std::cout << "Author: " << this->books[i].autor << '\n';
        std::cout << "Num:   " << this->books[i].libNumber << '\n';
        std::cout << "Title: " << this->books[i].title << '\n' << '\n';
    }
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

    std::cout << "Genere: ";
    std::cin >> comics[getCurrentComicsSize() - 1].gener;

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

    //std::cout << "\n couting the authors and titles from obj arr: \n";
    //for (int i = 0; i < getCurrentBookSize(); i++)
    //{
    //    std::cout << "Author: " << this->books[i].autor << '\n';
    //    std::cout << "Title: " << this->books[i].title << '\n';
    //}

    setCurrentComicsSize(newSize);
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


Library::~Library()
{
    bookStream.close();
    comicSream.close();
    periodicalStream.close();
    delete[] books;
    delete[] comics;
    delete[] periodicals;
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

    std::cout << "Genere: ";
    std::cin >> books[getCurrentBookSize() - 1].gener;

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

void Library::printBook(int libNum)
{
    //Book book;
    //bookStream.seekg(libNum);
    //bookStream.read(reinterpret_cast<char*>(&book), sizeof(Book));

    std::cout << "Book charachteristics: " << books[0].autor << '\n' << books[0].dateOfIssue << '\n' << books[0].gener << '\n'
        << books[0].libNumber << '\n' << books[0].publisher << '\n' << books[0].shortDescription << '\n' << books[0].title << '\n';
}
