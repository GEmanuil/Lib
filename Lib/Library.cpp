#include "Library.h"
#pragma warning (disable:4996)

Library::Library()
    //:
    //bookStream("books.bin", std::ios::binary, std::ios::in),
    //comicSream("comic.bin", std::ios::binary), 
    //periodicalStream("periodical.bin", std::ios::binary)
{
    openStreams();
    books = new Book[sizeOfBookFile(bookStream)];
    comics = new Comics[sizeOfComicFile(comicSream)];
    periodicals = new Periodical[sizeOfPeriodicalFile(periodicalStream)];
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
    bookStream.open("books.bin", std::ios::binary | std::ios::in);
    if (!bookStream.is_open())
    {
        std::cout << "Can't open file books.bin!!!";
        return;
    }

    comicSream.open("comic.bin", std::ios::binary | std::ios::in);
    if (!comicSream.is_open())
    {
        std::cout << "Can't open file comic.bin!!!";
        return;
    }

    periodicalStream.open("periodical.bin", std::ios::binary | std::ios::in);
    if (!periodicalStream.is_open())
    {
        std::cout << "Can't open file periodical.bin!!!";
        return;
    }
    
}

short Library::sizeOfBookFile(std::fstream& stream) const
{
    stream.seekg(0, std::ios::end);
    short size = stream.tellg() / sizeof(Book);

    stream.seekg(0, std::ios::beg);
    stream.clear();
    return size;
}

short Library::sizeOfComicFile(std::fstream& stream) const
{
    stream.seekg(0, std::ios::end);
    short size = stream.tellg() / sizeof(Comics);

    stream.seekg(0, std::ios::beg);
    stream.clear();
    return size;
}

short Library::sizeOfPeriodicalFile(std::fstream& stream) const
{
    stream.seekg(0, std::ios::end);
    short size = stream.tellg() / sizeof(Periodical);

    stream.seekg(0, std::ios::beg);
    stream.clear();
    return size;
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
        addBook(bookStream);
    }
    else if (!strcmp(command, "Comics"))
    {

    }
    else if (!strcmp(command, "Periodical"))
    {

    }
}

void Library::addBook(std::fstream& stream)
{ 
    char input[1024];
    std::cout << "Title: ";
    std::cin.ignore();
    std::cin.getline(input, 1024);
    strcpy(books[bCounter].title, input);

    std::cout << "Author: ";
    std::cin.getline(input, 1024);
    strcpy(books[bCounter].autor, input);

    std::cout << "Publisher: ";
    //std::cin.ignore();
    std::cin.getline(input, 1024);
    strcpy(books[bCounter].publisher, input);

    std::cout << "Genere: ";
    std::cin >> books[bCounter].gener;

    std::cout << "Short description about the book: ";
    std::cin.ignore();
    std::cin.getline(input, 1024);
    strcpy(books[bCounter].shortDescription, input);

    std::cout << "Date of issue: ";
    std::cin >> books[bCounter].dateOfIssue;

    books[bCounter].libNumber = numOfPaper;
    ++numOfPaper;

    stream.seekg(0, std::ios::end);
    stream.write(reinterpret_cast<const char*>(&books[bCounter]), sizeof(Book));

    ++bCounter;
}
