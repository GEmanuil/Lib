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
	~Library();

	void addPaper(char* command);
	void removePaper(char* command);
	void addUser(char* command);
	void removeUser(char* command);
	void giveAPaper(char* command);
	void reciveABook(char* command);
	void overduePaper(char* command);
	void overdueUsers(char* command);
	void infUsers(char* command);

	void print();
	void printBookWithLibNum(int libNum);
	void libSave();
	void help() const;

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
	bool libNumExistInArr(int* arr, int size, int num) const;
	bool checkIfLibNumExists(int libNUm) const;
	bool checkIfUserExists(char* name) const;

	short sizeOfBookFile(std::fstream& stream) const;
	short sizeOfComicFile(std::fstream& stream) const;
	short sizeOfPeriodicalFile(std::fstream& stream) const;
	short sizeOfUsersFile(std::fstream& stream) const;

	void setCurrentBookSize(int size);
	int getCurrentBookSize() const;
	void setCurrentComicsSize(int size);
	int getCurrentComicsSize() const;
	void setCurrentPeriodicalSize(int size);
	int getCurrentPeriodicalSize() const;
	void setCurrentUserSize(int size);
	int getCurrentUserSize() const;


	int currentUsersSize;
	int currentBookSize;
	int currentComicsSize;
	int currentPeriodicalSize;

	int numOfPaper = 0;

};
