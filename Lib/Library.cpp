#include "Library.h"

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