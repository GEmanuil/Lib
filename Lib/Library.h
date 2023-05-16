#pragma once
#include <fstream>
#include <iostream>
#include "Book.h"
#include "Comics.h"
#include "Periodical.h"

class Library
{
public:
	Library();
	Library(const Library& lib);
	Library& operator=(const Library& lib);
	~Library();
private:
	std::fstream bookStream;
	std::fstream comicSream;
	std::fstream periodicalStream;

	Book* books;
	Comics* comics;
	Periodical* periodicals;
	

	void openStreams();

	short sizeOfBookFile(std::fstream& stream) const;
	short sizeOfComicFile(std::fstream& stream) const;
	short sizeOfPeriodicalFile(std::fstream& stream) const;


};

