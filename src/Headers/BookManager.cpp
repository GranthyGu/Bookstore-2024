/*
 * File: BookManager.cpp
 * ----------------------
 * Implementation for the BookManager class.
 */

#include "BookManager.hpp"

ISBN::ISBN() {
    std::memset(Info, 0, sizeof(Info));
}

ISBN::ISBN(std::string str) {
    if (str.length() > 20) {
        return;
    }
    for (int i = 0; i < str.length(); i++) {
        Info[i] = str[i];
    }
}

bool ISBN::operator<(const ISBN& other) {
    for (int i = 0; i < 20; i++) {
        if (Info[i] != other.Info[i]) {
            return Info[i] < other.Info[i];
        }
    }
    return false;
}
bool ISBN::operator>(const ISBN& other) {
    for (int i = 0; i < 20; i++) {
        if (Info[i] != other.Info[i]) {
            return Info[i] > other.Info[i];
        }
    }
    return false;
}
bool ISBN::operator==(const ISBN& other) const {
    for (int i = 0; i < 20; i++) {
        if (Info[i] != other.Info[i]) {
            return false;
        }
    }
    return true;
}
ISBN& ISBN::operator=(const ISBN& other) {
    for (int i = 0; i < 20; i++) {
        Info[i] = other.Info[i];
    }
    return *this;
}

Book::Book() : Inventory(0), Price(0.0) {
    std::memset(BookName, 0, sizeof(BookName));
    std::memset(Author, 0, sizeof(Author));
    std::memset(Keyword, 0, sizeof(Keyword));
}

Book::Book(ISBN isbn) : isbn(isbn), Inventory(0), Price(0.0) {
    std::memset(BookName, 0, sizeof(BookName));
    std::memset(Author, 0, sizeof(Author));
    std::memset(Keyword, 0, sizeof(Keyword));
}

Book::Book(std::string str) : isbn(str), Inventory(0), Price(0.0) {
    std::memset(BookName, 0, sizeof(BookName));
    std::memset(Author, 0, sizeof(Author));
    std::memset(Keyword, 0, sizeof(Keyword));
}

std::vector<std::string> Book::scanKeywords() {
    std::vector<std::string> tmp;
    int i = 0;
    std::string token;
    while (true) {
        if (i >= 60 || Keyword[i] == '\0') {
            break;
        }
        if (Keyword[i] != '|') {
            token += Keyword[i];
        } else {
            tmp.push_back(token);
            token.clear();
        }
        i++;
    }
    std::unordered_set<std::string> seen;
    for (auto num : tmp) {
        if (seen.count(num)) {
            throw Error();
        }
        seen.insert(num);
    }
    return tmp;
}

bool Book::operator<(const Book& other) {
    return isbn < other.isbn;
}
bool Book::operator>(const Book& other) {
    return isbn > other.isbn;
}
bool Book::operator==(const Book& other) const {
    return isbn == other.isbn;
}
Book& Book::operator=(const Book& other) {
    isbn = other.isbn;
    return *this;
}

const Book m(" ");
const Book M("~~~~~~~~~~~~~~~~~~~~");

BookManager::BookManager() : selected(false) {
    mapofISBN.set_file_names("File_of_ISBN", "File_of_ISBN_");
    mapofISBN.openfile();
    mapofName.set_file_names("File_of_Name", "File_of_Name_");
    mapofName.openfile();
    mapofAuthor.set_file_names("File_of_Author", "File_of_Author_");
    mapofAuthor.openfile();
    mapofKeywords.set_file_names("File_of_Key", "File_of_Key_");
    mapofKeywords.openfile();
}

void BookManager::Show() {
    Node<Book> minimal = mapofISBN.Findminimal();
    Node<Book> maximal = mapofISBN.Findmaximal();
    std::vector<Node<Book>> tmp = mapofISBN.Find(maximal, minimal);
    for (int i = 0; i < tmp.size(); i++) {
        std::cout << tmp[i].value.isbn.Info << "\t" << tmp[i].value.BookName << "\t" << tmp[i].value.Author << "\t" 
        << tmp[i].value.Keyword << "\t" << tmp[i].value.Price << "\t" << tmp[i].value.Inventory;
    }
    std::cout << "\n";
    return;
}

void BookManager::show(std::string str, int i) {
    if (i == 0) {     // ISBN
        if (str.length() > 20) {
            throw Error();
            return;
        }
        Book m(str);
        Node<Book> minimal(str, m);
        std::vector<Node<Book>> tmp = mapofISBN.Find(minimal, minimal);
        for (int i = 0; i < tmp.size(); i++) {
            std::cout << tmp[i].value.isbn.Info << "\t" << tmp[i].value.BookName << "\t" << tmp[i].value.Author << "\t" 
            << tmp[i].value.Keyword << "\t" << tmp[i].value.Price << "\t" << tmp[i].value.Inventory;
        }
        std::cout << "\n";
        return;
    }
    if (i == 1) {     // BookName
        if (str.length() > 60) {
            throw Error();
            return;
        }
        Node<Book> minimal(str, m);
        Node<Book> maximal(str, M);
        std::vector<Node<Book>> tmp = mapofName.Find(maximal, minimal);
        for (int i = 0; i < tmp.size(); i++) {
            std::cout << tmp[i].value.isbn.Info << "\t" << tmp[i].value.BookName << "\t" << tmp[i].value.Author << "\t" 
            << tmp[i].value.Keyword << "\t" << tmp[i].value.Price << "\t" << tmp[i].value.Inventory;
        }
        std::cout << "\n";
        return;
    }
    if (i == 2) {     // Author
        if (str.length() > 60) {
            throw Error();
            return;
        }
        Node<Book> minimal(str, m);
        Node<Book> maximal(str, M);
        std::vector<Node<Book>> tmp = mapofAuthor.Find(maximal, minimal);
        for (int i = 0; i < tmp.size(); i++) {
            std::cout << tmp[i].value.isbn.Info << "\t" << tmp[i].value.BookName << "\t" << tmp[i].value.Author << "\t" 
            << tmp[i].value.Keyword << "\t" << tmp[i].value.Price << "\t" << tmp[i].value.Inventory;
        }
        std::cout << "\n";
        return;
    }
    if (i == 3) {     // Keyword
        if (str.length() > 60) {
            throw Error();
            return;
        }
        ISBN mm(" ");
        ISBN MM("~~~~~~~~~~~~~~~~~~~~");
        Node<ISBN> minimal(str,mm);
        Node<ISBN> maximal(str, MM);
        std::vector<Node<ISBN>> tmp = mapofKeywords.Find(maximal, minimal);
        for (int i = 0; i < tmp.size(); i++) {
            std::string str;
            for (int j = 0; j < 20; j++) {
                str += tmp[i].value.Info[j];
            }
            show(str, 0);
        }
        if (tmp.size() == 0) {
            std::cout << "\n";
        }
    }
}

void BookManager::buy(std::string str, std::string quant) {
    try {
        int quantity = std::stoi(quant);
        if (str.length() > 20) {
            throw Error();
            return;
        }
        if (quantity <= 0) {
            throw Error();
            return;
        }
        Book certain(str);
        Node<Book> minimal(str, certain);
        std::vector<Node<Book>> tmp = mapofISBN.Find(minimal, minimal);
        if (tmp.size() != 1) {
            throw Error();
            return;
        } else {
            mapofISBN.remove(str, tmp[0].value);
            Book item = tmp[0].value;
            if (quantity > item.Inventory) {
                throw Error();
                return;
            } else {
                item.Inventory -= quantity;
                double total = (double)quantity * item.Price;
                std::cout << std::fixed << std::setprecision(2);
                std::cout << total << "\n";
            }
            mapofISBN.insert(str, item);
        }
        return;
    }
    catch(const std::exception& e) {
        throw Error();
    }
}

void BookManager::select(std::string str) {
    if (str.length() > 20) {
        throw Error();
        return;
    } else {
        selected = true;
        Book mm(str);
        Node<Book> minimal(str, mm);
        std::vector<Node<Book>> tmp = mapofISBN.Find(minimal, minimal);
        if (tmp.empty()) {
            mapofISBN.insert(str, mm);
            bookselected = mm;
        } else {
            bookselected = tmp[0].value;
        }
    }
}

void BookManager::modify(std::string str, int i) {
    if (!selected) {
        throw Error();
        return;
    }
    if (i == 0) {       // ISBN
        if (str.length() > 20) {
            throw Error();
            return;
        }
        std::string str_of_isbn(bookselected.isbn.Info, sizeof(bookselected.isbn.Info));
        if (str == str_of_isbn) {
            throw Error();
            return;
        }
        mapofISBN.remove(bookselected.isbn.Info, bookselected);
        mapofAuthor.remove(bookselected.Author, bookselected);
        mapofName.remove(bookselected.BookName, bookselected);
        std::vector<std::string> tmp = bookselected.scanKeywords();
        for (int j = 0; j < tmp.size(); j++) {
            mapofKeywords.remove(tmp[j], bookselected.isbn);
        }
        ISBN new_isbn(str);
        bookselected.isbn = new_isbn;
        mapofISBN.insert(bookselected.isbn.Info, bookselected);
        mapofAuthor.insert(bookselected.Author, bookselected);
        mapofName.insert(bookselected.BookName, bookselected);
        for (int j = 0; j < tmp.size(); j++) {
            mapofKeywords.insert(tmp[j], bookselected.isbn);
        }
    }
    if (i == 1) {       // BookName
        if (str.length() > 60) {
            throw Error();
            return;
        }
        mapofISBN.remove(bookselected.isbn.Info, bookselected);
        mapofAuthor.remove(bookselected.Author, bookselected);
        mapofName.remove(bookselected.BookName, bookselected);
        std::memset(bookselected.BookName, 0, sizeof(bookselected.BookName));
        for (int i = 0; i < str.length(); i++) {
            bookselected.BookName[i] = str[i];
        }
        mapofISBN.insert(bookselected.isbn.Info, bookselected);
        mapofAuthor.insert(bookselected.Author, bookselected);
        mapofName.insert(bookselected.BookName, bookselected);
    }
    if (i == 2) {       // Author
        if (str.length() > 60) {
            throw Error();
            return;
        }
        mapofISBN.remove(bookselected.isbn.Info, bookselected);
        mapofAuthor.remove(bookselected.Author, bookselected);
        mapofName.remove(bookselected.BookName, bookselected);
        std::memset(bookselected.Author, 0, sizeof(bookselected.Author));
        for (int i = 0; i < str.length(); i++) {
            bookselected.Author[i] = str[i];
        }
        mapofISBN.insert(bookselected.isbn.Info, bookselected);
        mapofAuthor.insert(bookselected.Author, bookselected);
        mapofName.insert(bookselected.BookName, bookselected);
    }
    if (i == 3) {       // Keyword
        if (str.length() > 60) {
            throw Error();
            return;
        }
        mapofISBN.remove(bookselected.isbn.Info, bookselected);
        mapofAuthor.remove(bookselected.Author, bookselected);
        mapofName.remove(bookselected.BookName, bookselected);
        std::vector<std::string> tmp = bookselected.scanKeywords();
        for (int j = 0; j < tmp.size(); j++) {
            mapofKeywords.remove(tmp[j], bookselected.isbn);
        }
        for (int k = 0; k < str.length(); k++) {
            bookselected.Keyword[k] = str[k];
        }
        std::vector<std::string> new_keyword = bookselected.scanKeywords();
        for (int j = 0; j < tmp.size(); j++) {
            mapofKeywords.insert(new_keyword[j], bookselected.isbn);
        }
        mapofISBN.insert(bookselected.isbn.Info, bookselected);
        mapofAuthor.insert(bookselected.Author, bookselected);
        mapofName.insert(bookselected.BookName, bookselected);
    }
    if (i == 4) {       //Price
        if (str.length() > 13) {
            throw Error();
            return;
        }
        mapofISBN.remove(bookselected.isbn.Info, bookselected);
        mapofAuthor.remove(bookselected.Author, bookselected);
        mapofName.remove(bookselected.BookName, bookselected);
        try {
            double new_price = std::stod(str);
            bookselected.Price = new_price;
            mapofISBN.insert(bookselected.isbn.Info, bookselected);
            mapofAuthor.insert(bookselected.Author, bookselected);
            mapofName.insert(bookselected.BookName, bookselected);
        }
        catch(const std::exception& e) {
            throw Error();
        }
    }
}

void BookManager::import(std::string quantity) {
    if (!selected) {
        throw Error();
        return;
    }
    if (quantity[0] == '-') {
        throw Error();
        return;
    }
    mapofISBN.remove(bookselected.isbn.Info, bookselected);
    mapofAuthor.remove(bookselected.Author, bookselected);
    mapofName.remove(bookselected.BookName, bookselected);
    try {
        int num = std::stoi(quantity);
        if (num <= 0) {
            throw Error();
            return;
        }
        bookselected.Inventory += num;
        mapofISBN.insert(bookselected.isbn.Info, bookselected);
        mapofAuthor.insert(bookselected.Author, bookselected);
        mapofName.insert(bookselected.BookName, bookselected);
    }
    catch(const std::exception& e) {
        throw Error();
    }
}
