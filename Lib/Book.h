#pragma once
#include "Paper.h"
class Book : public Paper
{
public:
	char autor[1024];
	char publisher[1024];
	unsigned short genre;
	void setGenre();
};

