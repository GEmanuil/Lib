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
            std::cin >> command;
        }
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