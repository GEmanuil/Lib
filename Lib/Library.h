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

	void addPaper(char* command);
	void addBook(std::fstream& stream);
	void printBook(int libNum);


private:
	std::fstream bookStream;
	std::fstream comicSream;
	std::fstream periodicalStream;

	Book* books; int bCounter = 0;
	Comics* comics; int cCounter = 0;
	Periodical* periodicals; int pCounter = 0;
	
	void openStreams();
	void resizeBooksArr(size_t newSize);

	short sizeOfBookFile(std::fstream& stream);
	short sizeOfComicFile(std::fstream& stream) const;
	short sizeOfPeriodicalFile(std::fstream& stream) const;

	void setCurrentBookSize(int size);
	int getCurrentBookSize();
	int numOfPaper = 1;
	int currentBookSize;
};

