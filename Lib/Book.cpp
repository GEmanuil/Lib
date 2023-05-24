#include "Book.h"
#include <iostream>


void Book::setGenre()
{
	unsigned short charcteristic = 0;
	unsigned short type = 0;
	unsigned short audience = 0;
	std::cout << "\n Set the characteristic: \n 1. Fiction \n 2. Thriller \n 3. Crime fiction \n 4. Other \n (enter a num from 1 to 4) \n - ";
	std::cin >> charcteristic;
	std::cout << "\n Set the type: \n 1. Poetry \n 2. Prose \n 3. Drama \n 4. Other \n (enter a num from 1 to 4) \n - ";
	std::cin >> type;
	std::cout << "\n Target audience: \n 1. Children \n 2. Teenangers \n 3. Adults \n (enter a num from 1 to 3) \n - ";
	std::cin >> audience;



	unsigned short genreCode = 0;

	// Set the characteristic bits
	genreCode |= (charcteristic & 0x7F); // 0x7F = 01111111

	// Set the type bits
	genreCode |= ((type & 0x0F) << 7); // 0x0F = 00001111 Shift left 7 bits and set next 4 bits

	// Set the target audience bits
	genreCode |= ((audience & 0x0F) << 11); // Shift left 11 bits and set next 4 bits

	// Calculate and set the parity bit
	unsigned short bitCount = 0;
	unsigned short tempGenreCode = genreCode;
	while (tempGenreCode > 0) {
		bitCount += tempGenreCode & 0x01; // Check if the least significant bit is set
		tempGenreCode >>= 1; // Shift right by 1 bit
	}

	unsigned short parityBit = (bitCount % 2 == 0) ? 0 : 1; // Calculate the parity bit value
	genreCode |= (parityBit << 15); // Set the most significant bit as the parity bit

	genre = genreCode;
}

void Book::getGenre(char* charact, char* type, char* audience)
{
	unsigned short genreCopy = genre;

	unsigned short characteristic = 0;
	unsigned short gType = 0;
	unsigned short gAudience = 0;

	characteristic |= (genreCopy & 0x7F);
	gType |= ((genreCopy >> 7) & 0x0F);
	gAudience |= ((genreCopy >> 11) & 0x0F);
	std::cout << "\nGenre:";
	switch (characteristic)
	{
	case 1:
		std::cout << "\n	- Fiction";
		break;
	case 2:
		std::cout << "\n	- Thriller";
		break;
	case 3:
		std::cout << "\n	- Crime fiction";
		break;
	case 4:
		std::cout << "\n	- Other";
		break;
	default:
		std::cout << "\n	- Genre eror!";
		break;
	}

	switch (gType)
	{
	case 1:
		std::cout << "\n	- Poetry";
		break;
	case 2:
		std::cout << "\n	- Prose";
		break;
	case 3:
		std::cout << "\n	- Drama";
		break;
	case 4:
		std::cout << "\n	- Other";
		break;
	default:
		std::cout << "\n	- Genre eror!";
		break;
	}

	switch (gAudience)
	{
	case 1:
		std::cout << "\n	- Children\n\n";
		break;
	case 2:
		std::cout << "\n	- Teenangers\n\n";
		break;
	case 3:
		std::cout << "\n	- Adults\n\n";
		break;
	default:
		std::cout << "\n	- Genre eror!\n\n";
		break;
	}
}
