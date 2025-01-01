/*
 * File: BookManager.cpp
 * ----------------------
 * Implementation for the BookManager class.
 */

#include "BookManager.hpp"

ISBN::ISBN() {
    memset(Info, 0, sizeof(Info));
}

ISBN::ISBN(std::string str) {
    if (str.length() > 20) {
        throw Error();
        return;
    }
    for (int i = 0; i < str.length(); i++) {
        Info[i] = str[i];
    }
    for (int i = str.length(); i < 20; i++) {
        Info[i] = '\0';
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

Book::Book() : Inventory(0), Price1(0), Price2(0) {
    memset(BookName, 0, sizeof(BookName));
    memset(Author, 0, sizeof(Author));
    memset(Keyword, 0, sizeof(Keyword));
}

Book::Book(ISBN isbn) : isbn(isbn), Inventory(0), Price1(0), Price2(0) {
    memset(BookName, 0, sizeof(BookName));
    memset(Author, 0, sizeof(Author));
    memset(Keyword, 0, sizeof(Keyword));
}

Book::Book(std::string str) : isbn(str), Inventory(0), Price1(0), Price2(0) {
    if (str.length() > 20) {
        throw Error();
    }
    memset(BookName, 0, sizeof(BookName));
    memset(Author, 0, sizeof(Author));
    memset(Keyword, 0, sizeof(Keyword));
}

std::vector<std::string> Book::scanKeywords(std::string str) {
    std::vector<std::string> tmp;
    int i = 0;
    std::string token;
    if (str.length() > 60) {
        throw Error();
    }
    while (true) {
        if (i >= str.length() || str[i] == '\0') {
            break;
        }
        if (str[i] != '|') {
            token += str[i];
        } else {
            if (token.empty()) {
                throw Error();
            }
            tmp.push_back(token);
            token.clear();
        }
        i++;
    }
    tmp.push_back(token);
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
    for (int i = 0; i < 60; i++) {
        BookName[i] = other.BookName[i];
        Author[i] = other.Author[i];
        Keyword[i] = other.Keyword[i];
    }
    Inventory = other.Inventory;
    Price1 = other.Price1;
    Price2 = other.Price2;
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

void BookManager::setLogManagement(LogManagement& lm) {
    LM = lm;
}

void BookManager::Show() {
    Node<Book> minimal = mapofISBN.Findminimal();
    Node<Book> maximal = mapofISBN.Findmaximal();
    std::vector<Node<Book>> tmp = mapofISBN.Find(maximal, minimal);
    for (int i = 0; i < tmp.size(); i++) {
        std::cout << tmp[i].value.isbn.Info << "\t" << tmp[i].value.BookName << "\t" << tmp[i].value.Author << "\t" 
        << tmp[i].value.Keyword << "\t";
        long long summ = (long long)tmp[i].value.Price1 + (long long)tmp[i].value.Price2 * INT_MAX;
        double divi = summ / 100.0;
        std::cout << std::fixed << std::setprecision(2);
        std::cout << divi << "\t";
        std::cout << std::fixed << std::setprecision(0);
        std::cout << tmp[i].value.Inventory;
        std::cout << "\n";
    }
    if (tmp.size() == 0) {
        std::cout << "\n";
    }
    return;
}

void BookManager::show(std::string str, int i) {
    if (i == 0) {     // ISBN
        if (str.length() > 20) {
            throw Error();
            return;
        }
        for (int i = str.length(); i < 20; i++) {
            str += '\0';
        }
        Book m(str);
        Node<Book> minimal(str, m);
        std::vector<Node<Book>> tmp = mapofISBN.Find(minimal, minimal);
        for (int i = 0; i < tmp.size(); i++) {
            std::cout << tmp[i].value.isbn.Info << "\t" << tmp[i].value.BookName << "\t" << tmp[i].value.Author << "\t" 
            << tmp[i].value.Keyword << "\t";
            long long summ = (long long)tmp[i].value.Price1 + (long long)tmp[i].value.Price2 * INT_MAX;
            double divi = summ / 100.0;
            std::cout << std::fixed << std::setprecision(2);
            std::cout << divi << "\t";
            std::cout << std::fixed << std::setprecision(0);
            std::cout << tmp[i].value.Inventory;
        }
        std::cout << "\n";
        return;
    }
    if (i == 1) {     // BookName
        if (str.length() > 60) {
            throw Error();
            return;
        }
        ISBN mm(" ");
        ISBN MM("~~~~~~~~~~~~~~~~~~~~");
        Node<ISBN> minimal(str, mm);
        Node<ISBN> maximal(str, MM);
        std::vector<Node<ISBN>> tmp = mapofName.Find(maximal, minimal);
        for (int i = 0; i < tmp.size(); i++) {
            std::string strr;
            for (int j = 0; j < 20; j++) {
                strr += tmp[i].value.Info[j];
            }
            show(strr, 0);
        }
        if (tmp.size() == 0) {
            std::cout << "\n";
        }
        return;
    }
    if (i == 2) {     // Author
        if (str.length() > 60) {
            throw Error();
            return;
        }
        ISBN mm(" ");
        ISBN MM("~~~~~~~~~~~~~~~~~~~~");
        Node<ISBN> minimal(str, mm);
        Node<ISBN> maximal(str, MM);
        std::vector<Node<ISBN>> tmp = mapofAuthor.Find(maximal, minimal);
        for (int i = 0; i < tmp.size(); i++) {
            std::string strr;
            for (int j = 0; j < 20; j++) {
                strr += tmp[i].value.Info[j];
            }
            show(strr, 0);
        }
        if (tmp.size() == 0) {
            std::cout << "\n";
        }
        return;
    }
    if (i == 3) {     // Keyword
        if (str.length() > 60) {
            throw Error();
            return;
        }
        Book t;
        std::vector<std::string> numofkey = t.scanKeywords(str);
        if (numofkey.size() != 1) {
            throw Error();
            return;
        }
        ISBN mm(" ");
        ISBN MM("~~~~~~~~~~~~~~~~~~~~");
        Node<ISBN> minimal(str,mm);
        Node<ISBN> maximal(str, MM);
        std::vector<Node<ISBN>> tmp = mapofKeywords.Find(maximal, minimal);
        for (int i = 0; i < tmp.size(); i++) {
            std::string strr;
            for (int j = 0; j < 20; j++) {
                strr += tmp[i].value.Info[j];
            }
            show(strr, 0);
        }
        if (tmp.size() == 0) {
            std::cout << "\n";
        }
    }
}

void BookManager::buy(std::string str, std::string quant) {
    try {
        if (quant.length() > 10) {
            throw Error();
            return;
        }
        int quantity = std::stoi(quant);
        if (str.length() > 20 || quantity <= 0) {
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
                mapofISBN.insert(str, item);
                throw Error();
                return;
            } else {
                item.Inventory -= quantity;
                long long summ = (long long)item.Price1 + (long long)item.Price2 * INT_MAX;
                long long total = (long long)quantity * summ;
                std::cout << std::fixed << std::setprecision(2);
                std::cout << total / 100.00 << "\n";
                LM.addinfo(total / 100.00);
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
        for (int i = str.length(); i < 20; i++) {
            str += '\0';
        }
        Book mm(str);
        ISBN mmm(str);
        Node<Book> minimal(str, mm);
        std::vector<Node<Book>> tmp = mapofISBN.Find(minimal, minimal);
        if (tmp.empty()) {
            mapofISBN.insert(str, mm);
            bookselected_ = mmm;
        } else {
            bookselected_ = tmp[0].value.isbn;
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
        std::string str_of_isbn;
        for (int i = 0; i < 20; i++) {
            str_of_isbn += bookselected_.Info[i];
        }
        if (str == str_of_isbn) {
            throw Error();
            return;
        }
        Book bk(str);
        Node<Book> t(str, bk);
        std::vector<Node<Book>> tt = mapofISBN.Find(t, t);
        if (tt.size() > 0) {
            throw Error();
            return;
        }
        Book bkk(bookselected_);
        std::string string_of_isbn;
        for (int i = 0; i < 20; i++) {
            string_of_isbn += bookselected_.Info[i];
        }
        Node<Book> node_of_book(string_of_isbn, bkk);
        std::vector<Node<Book>> vector_of_book = mapofISBN.Find(node_of_book, node_of_book);
        Book bookselected = vector_of_book[0].value;
        mapofISBN.remove(str_of_isbn, bookselected);
        mapofAuthor.remove(bookselected.Author, bookselected.isbn);
        mapofName.remove(bookselected.BookName, bookselected.isbn);
        std::string strr;
        for (int i = 0; i < 60; i++) {
            strr += bookselected.Keyword[i];
        }
        std::vector<std::string> tmp = bookselected.scanKeywords(strr);
        for (int j = 0; j < tmp.size(); j++) {
            mapofKeywords.remove(tmp[j], bookselected.isbn);
        }
        ISBN new_isbn(str);
        bookselected.isbn = new_isbn;
        bookselected_ = new_isbn;
        mapofISBN.insert(str, bookselected);
        mapofAuthor.insert(bookselected.Author, bookselected.isbn);
        mapofName.insert(bookselected.BookName, bookselected.isbn);
        for (int j = 0; j < tmp.size(); j++) {
            mapofKeywords.insert(tmp[j], bookselected.isbn);
        }
    }
    if (i == 1) {       // BookName
        if (str.length() > 60) {
            throw Error();
            return;
        }
        Book bkk(bookselected_);
        std::string string_of_isbn;
        for (int i = 0; i < 20; i++) {
            string_of_isbn += bookselected_.Info[i];
        }
        Node<Book> node_of_book(string_of_isbn, bkk);
        std::vector<Node<Book>> vector_of_book = mapofISBN.Find(node_of_book, node_of_book);
        Book bookselected = vector_of_book[0].value;
        mapofISBN.remove(bookselected.isbn.Info, bookselected);
        mapofName.remove(bookselected.BookName, bookselected.isbn);
        memset(bookselected.BookName, 0, sizeof(bookselected.BookName));
        for (int i = 0; i < str.length(); i++) {
            bookselected.BookName[i] = str[i];
        }
        mapofISBN.insert(bookselected.isbn.Info, bookselected);
        mapofName.insert(bookselected.BookName, bookselected.isbn);
    }
    if (i == 2) {       // Author
        if (str.length() > 60) {
            throw Error();
            return;
        }
        Book bkk(bookselected_);
        std::string string_of_isbn;
        for (int i = 0; i < 20; i++) {
            string_of_isbn += bookselected_.Info[i];
        }
        Node<Book> node_of_book(string_of_isbn, bkk);
        std::vector<Node<Book>> vector_of_book = mapofISBN.Find(node_of_book, node_of_book);
        Book bookselected = vector_of_book[0].value;
        mapofISBN.remove(bookselected.isbn.Info, bookselected);
        mapofAuthor.remove(bookselected.Author, bookselected.isbn);
        memset(bookselected.Author, 0, sizeof(bookselected.Author));
        for (int i = 0; i < str.length(); i++) {
            bookselected.Author[i] = str[i];
        }
        mapofISBN.insert(bookselected.isbn.Info, bookselected);
        mapofAuthor.insert(bookselected.Author, bookselected.isbn);
    }
    if (i == 3) {       // Keyword
        if (str.length() > 60) {
            throw Error();
            return;
        }
        Book bkk(bookselected_);
        std::vector<std::string> new_keyword = bkk.scanKeywords(str);
        std::string string_of_isbn;
        for (int i = 0; i < 20; i++) {
            string_of_isbn += bookselected_.Info[i];
        }
        Node<Book> node_of_book(string_of_isbn, bkk);
        std::vector<Node<Book>> vector_of_book = mapofISBN.Find(node_of_book, node_of_book);
        Book bookselected = vector_of_book[0].value;
        mapofISBN.remove(bookselected.isbn.Info, bookselected);
        std::string strr;
        for (int i = 0; i < 60; i++) {
            strr += bookselected.Keyword[i];
        }
        std::vector<std::string> tmp = bookselected.scanKeywords(strr);
        for (int j = 0; j < tmp.size(); j++) {
            mapofKeywords.remove(tmp[j], bookselected.isbn);
        }
        for (int k = 0; k < str.length(); k++) {
            bookselected.Keyword[k] = str[k];
        }
        for (int k = str.length(); k < 60; k++) {
            bookselected.Keyword[k] = '\0';
        }
        for (int j = 0; j < new_keyword.size(); j++) {
            mapofKeywords.insert(new_keyword[j], bookselected.isbn);
        }
        mapofISBN.insert(bookselected.isbn.Info, bookselected);
    }
    if (i == 4) {       //Price
        try {
            if (str.length() > 13) {
                throw Error();
            }
            int dotCount = 0;
            for (char ch : str) {
                if (ch == '.') {
                    ++dotCount;
                }
                if (!isdigit(ch) && ch != '.') {
                    throw Error();
                }
            }
            if (dotCount > 1) {
                throw Error();
            }
            std::string integerPart, fractionalPart;
            auto dotPos = str.find('.');
            if (dotPos != std::string::npos) {
                integerPart = str.substr(0, dotPos);
                fractionalPart = str.substr(dotPos + 1);
                if (fractionalPart.length() > 2) {
                    throw Error();
                }
            } else {
                integerPart = str;
            }
            while (fractionalPart.length() < 2) {
                fractionalPart += '0';
            }
            std::string combined = integerPart + fractionalPart;
            long long new_price = std::stoll(combined);
            if (new_price <= 0){
                throw Error();
                return;
            }
            Book bkk(bookselected_);
            std::string string_of_isbn;
            for (int i = 0; i < 20; i++) {
                string_of_isbn += bookselected_.Info[i];
            }
            Node<Book> node_of_book(string_of_isbn, bkk);
            std::vector<Node<Book>> vector_of_book = mapofISBN.Find(node_of_book, node_of_book);
            Book bookselected = vector_of_book[0].value;
            mapofISBN.remove(bookselected.isbn.Info, bookselected);
            bookselected.Price1 = new_price % INT_MAX;
            bookselected.Price2 = new_price / INT_MAX;
            mapofISBN.insert(bookselected.isbn.Info, bookselected);
        }
        catch(const std::exception& e) {
            throw Error();
        }
    }
}

void BookManager::import(std::string quantity, std::string totalcost) {
    if (!selected) {
        throw Error();
        return;
    }
    if (quantity[0] == '-') {
        throw Error();
        return;
    }
    std::string string_of_isbn;
    for (int i = 0; i < 20; i++) {
        string_of_isbn += bookselected_.Info[i];
    }
    try {
        int num = std::stoi(quantity);
        double total = std::stod(totalcost);
        if (num <= 0 || total <= 0) {
            throw Error();
            return;
        }
        Book bkk(string_of_isbn);
        Node<Book> node_of_book(string_of_isbn, bkk);
        std::vector<Node<Book>> vector_of_book = mapofISBN.Find(node_of_book, node_of_book);
        Book bookselected = vector_of_book[0].value;
        mapofISBN.remove(bookselected.isbn.Info, bookselected);
        LM.addinfo(-total);
        bookselected.Inventory += num;
        mapofISBN.insert(bookselected.isbn.Info, bookselected);
    }
    catch(const std::exception& e) {
        throw Error();
    }
}
