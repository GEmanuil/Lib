#pragma once
#include "Paper.h"
class Book : public Paper
{
protected:
	char* autor;
	char* publisher;
	int gener;
};

