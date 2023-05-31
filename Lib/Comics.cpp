#include "Comics.h"

void Comics::setGenre()
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
