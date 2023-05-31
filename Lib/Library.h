#pragma once
#include <fstream>
#include <iostream>
#include "Book.h"
#include "Comics.h"
#include "Periodical.h"
#include "User.h"

class Library
{
public:
	Library();
	Library(const Library& lib);
	Library& operator=(const Library& lib);
	~Library();

	void addPaper(char* command);
	void removePaper(char* command);
	void addUser(char* command);
	void giveAPaper(char* command);
	void reciveABook(char* command);
	void overduePaper(char* command);
	void overdueUsers(char* command);

	void print();
	void printBookWithLibNum(int libNum);
	void libSave();

	//temp func
	void checkWhatIsInReadedBooksFIle();

private:
	std::fstream bookStream;
	std::fstream comicSream;
	std::fstream periodicalStream;
	std::fstream userStream;

	User* users;
	Book* books;
	Comics* comics;
	Periodical* periodicals;

	void addBook(std::fstream& stream);
	void resizeBooksArr(size_t newSize);
	void addComics(std::fstream& stream);
	void resizeComicsArr(size_t newSize);
	void addPeriodicals(std::fstream& stream);
	void resizePeriodicalssArr(size_t newSize);
	void resizeUserArr(size_t newSize);

	void openStreams();
	void loadBooks();
	void sortOverduedPaper(int* arrOfLibNumsToSort, size_t size, int* sortedArr);
	void getTypeOfPaperFromNum(unsigned int libNum, char* type);
	bool libNumExistInArr(int* arr, int size, int num);

	short sizeOfBookFile(std::fstream& stream);
	short sizeOfComicFile(std::fstream& stream);
	short sizeOfPeriodicalFile(std::fstream& stream);
	short sizeOfUsersFile(std::fstream& stream);

	void setCurrentBookSize(int size);
	int getCurrentBookSize();
	void setCurrentComicsSize(int size);
	int getCurrentComicsSize();
	void setCurrentPeriodicalSize(int size);
	int getCurrentPeriodicalSize();
	void setCurrentUserSize(int size);
	int getCurrentUserSize();


	int currentUsersSize;
	int currentBookSize;
	int currentComicsSize;
	int currentPeriodicalSize;

	int numOfPaper = 0;

};
