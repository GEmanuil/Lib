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
	void removePaper(char* command);

	void printBook(int libNum);
	void libSave();

private:
	std::fstream bookStream;
	std::fstream comicSream;
	std::fstream periodicalStream;

	Book* books;
	Comics* comics;
	Periodical* periodicals;

	void addBook(std::fstream& stream);
	void resizeBooksArr(size_t newSize);
	void addComics(std::fstream& stream);
	void resizeComicsArr(size_t newSize);

	void openStreams();
	void loadBooks();

	short sizeOfBookFile(std::fstream& stream);
	short sizeOfComicFile(std::fstream& stream);
	short sizeOfPeriodicalFile(std::fstream& stream);

	void setCurrentBookSize(int size);
	int getCurrentBookSize();
	void setCurrentComicsSize(int size);
	int getCurrentComicsSize();


	int currentBookSize;
	int currentComicsSize;
	int currentPeriodicals;

	int numOfPaper = 0;

};
