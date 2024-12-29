// Created by GranthyGu on 2024/12/23

#ifndef BOOK_MANAGER_HPP
#define BOOK_MANAGER_HPP

/*
 * File: BookManager.hpp
 * --------------------
 * This file exports a bookmanager class that has functions that we need 
 * when we manage books' information.
 */

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <unordered_set>
#include <cstring>
#include "maplist.hpp"
#include "error.hpp"
#include "LogManager.hpp"

/*
 * class ISBN:
 * This class saves an ISBN string or to say it is equivalent to a char[20].
 */

class ISBN {
public:
    char Info[20];
    ISBN();
    ISBN(std::string str);
    bool operator<(const ISBN& other);
    bool operator>(const ISBN& other);
    bool operator==(const ISBN& other) const;
    ISBN& operator=(const ISBN& other);
};

/*
 * class Book:
 * This class saves the information of a book, include its isbn, bookname, author, keywords, inventory, price etc.
 * We can use scanKeywords to seperate the keyword of a book, and save it into a vector of string.
 * We can input a string or an ISBN to construct a Book.
 */

class Book {
public:
    ISBN isbn;
    char BookName[60];
    char Author[60];
    char Keyword[60];
    int Inventory;
    float Price;
    Book();
    Book(ISBN isbn);
    Book(std::string str);
    std::vector<std::string> scanKeywords(std::string str);
    bool operator<(const Book& other);
    bool operator>(const Book& other);
    bool operator==(const Book& other) const;
    Book& operator=(const Book& other);
};

struct bbb {
    char ooo[256];
    char iii[100];
    int i;
    double t;
};
/*
 * class BookManager:
 * This class saves several maps.
 * Selected records whether there is a book selected.
 * Bookselected stores the book we save.
 * It has functions show, buy, select, modify, and import.
 * The int in function show and modify limits which information it will show or modify.
 */

class BookManager {
private:
    maplist<Book> mapofISBN;
    maplist<ISBN> mapofName;
    maplist<ISBN> mapofAuthor;
    maplist<ISBN> mapofKeywords;
public:
    ISBN bookselected_;
    bool selected;
    LogManagement LM;
    BookManager();
    void setLogManagement(LogManagement& lm);
    void Show();
    void show(std::string str, int i);
    void buy(std::string str, std::string quant);
    void select(std::string str);
    void modify(std::string str, int i);
    void import(std::string quantity, std::string totalcost);
};

#endif      //BOOK_MANAGER_HPP