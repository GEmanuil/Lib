#pragma once
#include "Paper.h"
class Comics : public Paper
{
public:
	char autor[1024];
	char publisher[1024];
	int gener;
	char periodicity[128];
	int quantity;
};
