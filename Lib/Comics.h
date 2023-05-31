#pragma once
#include "Paper.h"
#include <iostream>
class Comics : public Paper
{
public:
	void setGenre();
	char autor[1024];
	char publisher[1024];
	int genre;
	char periodicity[128];
	int quantity;
};
