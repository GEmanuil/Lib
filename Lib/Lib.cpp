#pragma warning(disable:4996)
#include <iostream>
#include "String.h"
#include "Library.h"

using namespace std;

int main()
{
    //String str;
    char command[1024];
    std::cout << "Enter command: ";
    std::cin >> command;
    std::cout << '\n';


    if (!strcmp(command, "open"))
    {
        Library lib;
        while (strcmp(command, "close"))
        {
            if (!strcmp(command, "add paper"))
            {
                lib.addPaper(command);
                lib.printBook(0);
            }
            else if (!strcmp(command, "remove paper"))
            {
                lib.removePaper(command);
            }
            std::cin.ignore();
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