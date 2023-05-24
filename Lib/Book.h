#pragma once
#include "Paper.h"
class Book : public Paper
{
public:
	char autor[1024];
	char publisher[1024];

	void setGenre();
	void getGenre(char* charact, char* type, char* audience);
	
private:
	unsigned short genre;
};

