#pragma warning(disable:4996)
#include <iostream>
#include "String.h"
#include "Library.h"

using namespace std;


//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
//
//                      RAZQSNENIQ    
// 
//   failove koito se izpolzvat v koda: books.bin, booksInRead.bin, booksInReadByMonth.bin, comic.bin, periodical.bin, readedBooks.bin, users.bin
//  
//   znam che ne e napraveno domashnoto po nai-dobiq nachin + ima nqkoi ne sintaktichni greshki na angliiski (koito mogat da draznqt) no mi trqbvat 5-6 tochki
//   znam che ne e napraveno domashnoto po nai-dobiq nachin + ima nqkoi ne sintaktichni greshki na angliiski (koito mogat da draznqt) no mi trqbvat 5-6 tochki
//   znam che ne e napraveno domashnoto po nai-dobiq nachin + ima nqkoi ne sintaktichni greshki na angliiski (koito mogat da draznqt) no mi trqbvat 5-6 tochki
//   znam che ne e napraveno domashnoto po nai-dobiq nachin + ima nqkoi ne sintaktichni greshki na angliiski (koito mogat da draznqt) no mi trqbvat 5-6 tochki
//   znam che ne e napraveno domashnoto po nai-dobiq nachin + ima nqkoi ne sintaktichni greshki na angliiski (koito mogat da draznqt) no mi trqbvat 5-6 tochki
//   znam che ne e napraveno domashnoto po nai-dobiq nachin + ima nqkoi ne sintaktichni greshki na angliiski (koito mogat da draznqt) no mi trqbvat 5-6 tochki
//  
//
//-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

int main()
{
    char command[1024];
    std::cout << "Enter command (open - opens the library): ";
    std::cin >> command;
    std::cout << '\n';


    if (!strcmp(command, "open"))
    {
        Library lib;
        lib.help();
        while (strcmp(command, "close"))
        {
            if (!strcmp(command, "add paper"))
            {
                lib.addPaper(command);
            }
            else if (!strcmp(command, "print"))
            {
                lib.print();
            }
            else if (!strcmp(command, "remove paper"))
            {
                lib.removePaper(command);
            }
            else if (!strcmp(command, "create user"))
            {
                lib.addUser(command);
            }
            else if (!strcmp(command, "remove user"))
            {
                lib.removeUser(command);
            }
            else if (!strcmp(command, "give"))
            {
                lib.giveAPaper(command);
            }
            else if (!strcmp(command, "recive"))
            {
                lib.reciveABook(command);
            }
            else if (!strcmp(command, "overdue"))
            {
                lib.overduePaper(command);
            }
            else if (!strcmp(command, "overdue users"))
            {
                lib.overdueUsers(command);
            }
            else if (!strcmp(command, "information about users"))
            {
                lib.infUsers(command);
            }

            std::cin.getline(command, 1024);
        }
        lib.libSave();
    }

    else if (!strcmp(command, "close"))
    {
        std::cout << "The library is not opened!!!" << endl;
    }
    else
    {
        std::cout << "Invalid command!!!" << endl;
    }
}