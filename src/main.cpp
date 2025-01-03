/*
 * File: Basic.cpp
 * ---------------
 * This file is the starter project for the BookStore Management.
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include "Headers/AccountManager.hpp"
#include "Headers/BookManager.hpp"
#include "Headers/error.hpp"
#include "Headers/LogManager.hpp"
#include "Headers/maplist.hpp"
#include "Headers/tokenscanner.hpp"

class Log {
public:
    int num;
    char userID_[30];
    char command[230];
    Log() {}
    Log(std::string str, int num) : num(num) {
        for (int i = 0; i < str.length(); i++) {
            command[i] = str[i];
        }
    }
    bool operator<(const Log& other) {
        return num < other.num;
    }
    bool operator>(const Log& other) {
        return num > other.num;
    }
    bool operator==(const Log& other) const {
        return num == other.num;
    }
    Log& operator=(const Log& other) {
        num = other.num;
        for (int i = 0; i < 30; i++) {
            userID_[i] = other.userID_[i];
        }
        for (int i = 0; i < 230; i++) {
            command[i] = other.command[i];
        }
        return *this;
    }
};

int main() {
    // freopen("in.txt", "r", stdin);   // 读入in.dat文件作为输入 
	// freopen("out.dat", "w", stdout);  // 将输入写入out.dat文件中 
    maplist<Log> mapoffinance("File_of_finance", "File_of_finance_");
    maplist<Log> mapofemployee("File_of_employee", "File_of_employee_");
    maplist<Log> mapoflog("File_of_logs", "File_of_logs_");
    mapoffinance.openfile();
    mapofemployee.openfile();
    mapoflog.openfile();
    TokenScanner scanner;
    BookManager BM;
    AccountManagement AM;
    AM.AcInitial();
    LogManagement LM;
    BM.setLogManagement(LM);
    int num = 0;
    while (true) {
        try {
            std::string str;
            if (!getline(std::cin, str)) {
                BM.LM.writetofile();
                break;
            }
            if (str.empty()) {
                continue;
            }
            Log l(str, num);
            num++;
            scanner.set_input(str);
            scanner.scan();
            if (scanner.getCommand() == "quit" || scanner.getCommand() == "exit") {
                BM.LM.writetofile();
                break;
            }
            if (scanner.getCommand() == "su") {
                if (scanner.tokens.size() != 2 && scanner.tokens.size() != 3) {
                    throw Error();
                    continue;
                }
                if (scanner.tokens.size() == 2) {
                    AM.su(scanner.tokens[1]);
                    BM.selected = false;
                    Book tmp;
                    BM.bookselected_ = tmp.isbn;
                }
                if (scanner.tokens.size() == 3) {
                    AM.su(scanner.tokens[1], scanner.tokens[2]);
                    BM.selected = false;
                    Book tmp;
                    BM.bookselected_ = tmp.isbn;
                }
                mapoflog.insert(std::to_string(num), l);
                continue;
            }
            if (scanner.getCommand() == "logout") {
                if (scanner.tokens.size() != 1) {
                    throw Error();
                    continue;
                }
                AM.logout();
                mapoflog.insert(std::to_string(num), l);
                if (AM.cur_privilege == -1) {
                    BM.selected = false;
                    Book tmp;
                    BM.bookselected_ = tmp.isbn;
                    continue;
                }
                tmpAccount tmp = AM.log_in_list.top();
                BM.selected = tmp.selected;
                BM.bookselected_ = tmp.book_selected;
                continue;
            }
            if (scanner.getCommand() == "register") {
                if (scanner.tokens.size() != 4) {
                    throw Error();
                    continue;
                }
                AM.Register(scanner.tokens[1], scanner.tokens[2], scanner.tokens[3]);
                mapoflog.insert(std::to_string(num), l);
                continue;
            }
            if (scanner.getCommand() == "passwd") {
                if (scanner.tokens.size() != 4 && scanner.tokens.size() != 3) {
                    throw Error();
                    continue;
                }
                if (scanner.tokens.size() == 3) {
                    AM.passwd(scanner.tokens[1], scanner.tokens[2]);
                }
                if (scanner.tokens.size() == 4) {
                    AM.passwd(scanner.tokens[1], scanner.tokens[2], scanner.tokens[3]);
                }
                for (int i = 0; i < 30; i++) {
                    l.userID_[i] = AM.log_in_list.top().ac.UserID[i];
                }
                mapoflog.insert(std::to_string(num), l);
                if (AM.log_in_list.top().ac.Privilege >= 3) {
                    mapofemployee.insert(std::to_string(num), l);
                }
                continue;
            }
            if (scanner.getCommand() == "useradd") {
                if (scanner.tokens.size() != 5) {
                    throw Error();
                    continue;
                }
                AM.useradd(scanner.tokens[1], scanner.tokens[2], scanner.tokens[3], scanner.tokens[4]);
                for (int i = 0; i < 30; i++) {
                    l.userID_[i] = AM.log_in_list.top().ac.UserID[i];
                }
                mapoflog.insert(std::to_string(num), l);
                if (AM.log_in_list.top().ac.Privilege >= 3) {
                    mapofemployee.insert(std::to_string(num), l);
                }
                continue;
            }
            if (scanner.getCommand() == "delete") {
                if (scanner.tokens.size() != 2) {
                    throw Error();
                    continue;
                }
                AM.Delete(scanner.tokens[1]);
                for (int i = 0; i < 30; i++) {
                    l.userID_[i] = AM.log_in_list.top().ac.UserID[i];
                }
                mapoflog.insert(std::to_string(num), l);
                if (AM.log_in_list.top().ac.Privilege >= 3) {
                    mapofemployee.insert(std::to_string(num), l);
                }
                continue;
            }
            if (scanner.getCommand() == "show") {
                if (AM.log_in_list.empty()) {
                    throw Error();
                    continue;
                }
                if (scanner.tokens.size() == 1) {
                    BM.Show();
                    continue;
                }
                if (scanner.tokens[1] == "finance") {
                    if (AM.cur_privilege < 7) {
                        throw Error();
                        continue;
                    }
                    if (scanner.tokens.size() == 3) {
                        int num;
                        try {
                            num = std::stoi(scanner.tokens[2]);
                        }
                        catch(const std::exception& e) {
                            throw Error();
                            continue;
                        }
                        if (num == 0) {
                            std::cout << std::endl;
                        }
                        if (num < 0) {
                            throw Error();
                            continue;
                        }
                        double income = BM.LM.calcincome(num);
                        double outcome = BM.LM.calcoutcome(num);
                        std::cout << std::fixed << std::setprecision(2);
                        std::cout << "+ " << income << " - " << outcome << std::endl;
                        for (int i = 0; i < 30; i++) {
                            l.userID_[i] = AM.log_in_list.top().ac.UserID[i];
                        }
                        mapoflog.insert(std::to_string(num), l);
                        if (AM.log_in_list.top().ac.Privilege >= 3) {
                            mapofemployee.insert(std::to_string(num), l);
                        }
                    }
                    if (scanner.tokens.size() == 2) {
                        if (scanner.tokens.size() == 0) {
                            std::cout << std::endl;
                            continue;
                        }
                        int num = BM.LM.Finance.size();
                        double income = BM.LM.calcincome(num);
                        double outcome = BM.LM.calcoutcome(num);
                        std::cout << std::fixed << std::setprecision(2);
                        std::cout << "+ " << income << " - " << outcome << std::endl;
                        for (int i = 0; i < 30; i++) {
                            l.userID_[i] = AM.log_in_list.top().ac.UserID[i];
                        }
                        mapoflog.insert(std::to_string(num), l);
                        if (AM.log_in_list.top().ac.Privilege >= 3) {
                            mapofemployee.insert(std::to_string(num), l);
                        }
                    }
                    if (scanner.tokens.size() > 3) {
                        throw Error();
                        continue;
                    }
                    continue;
                } else {
                    if (scanner.tokens.size() != 3 || AM.cur_privilege == -1) {
                        throw Error();
                        continue;
                    }
                    if (scanner.tokens[1] == "ISBN")
                    {
                        BM.show(scanner.tokens[2], 0);
                        for (int i = 0; i < 30; i++) {
                            l.userID_[i] = AM.log_in_list.top().ac.UserID[i];
                        }
                        mapoflog.insert(std::to_string(num), l);
                        if (AM.log_in_list.top().ac.Privilege >= 3) {
                            mapofemployee.insert(std::to_string(num), l);
                        }
                        continue;
                    }
                    if (scanner.tokens[1] == "name")
                    {
                        BM.show(scanner.tokens[2], 1);
                        for (int i = 0; i < 30; i++) {
                            l.userID_[i] = AM.log_in_list.top().ac.UserID[i];
                        }
                        mapoflog.insert(std::to_string(num), l);
                        if (AM.log_in_list.top().ac.Privilege >= 3) {
                            mapofemployee.insert(std::to_string(num), l);
                        }
                        continue;
                    }
                    if (scanner.tokens[1] == "author")
                    {
                        BM.show(scanner.tokens[2], 2);
                        for (int i = 0; i < 30; i++) {
                            l.userID_[i] = AM.log_in_list.top().ac.UserID[i];
                        }
                        mapoflog.insert(std::to_string(num), l);
                        if (AM.log_in_list.top().ac.Privilege >= 3) {
                            mapofemployee.insert(std::to_string(num), l);
                        }
                        continue;
                    }
                    if (scanner.tokens[1] == "keyword")
                    {
                        BM.show(scanner.tokens[2], 3);
                        for (int i = 0; i < 30; i++) {
                            l.userID_[i] = AM.log_in_list.top().ac.UserID[i];
                        }
                        mapoflog.insert(std::to_string(num), l);
                        if (AM.log_in_list.top().ac.Privilege >= 3) {
                            mapofemployee.insert(std::to_string(num), l);
                        }
                        continue;
                    }
                    throw Error();
                    continue;
                }
            }
            if (scanner.getCommand() == "buy") {
                if (AM.cur_privilege == -1 || scanner.tokens.size() != 3)
                {
                    throw Error();
                    continue;
                }
                BM.buy(scanner.tokens[1], scanner.tokens[2]);
                for (int i = 0; i < 30; i++) {
                    l.userID_[i] = AM.log_in_list.top().ac.UserID[i];
                }
                mapoflog.insert(std::to_string(num), l);
                if (AM.log_in_list.top().ac.Privilege >= 3) {
                    mapofemployee.insert(std::to_string(num), l);
                }
                mapoffinance.insert(std::to_string(num), l);
                continue;
            }
            if (scanner.getCommand() == "select") {
                if (AM.cur_privilege < 3 || scanner.tokens.size() != 2)
                {
                    throw Error();
                    continue;
                }
                BM.select(scanner.tokens[1]);
                tmpAccount tmp = AM.log_in_list.top();
                tmp.book_selected = BM.bookselected_;
                tmp.selected = BM.selected;
                AM.log_in_list.pop();
                AM.log_in_list.push(tmp);
                for (int i = 0; i < 30; i++) {
                    l.userID_[i] = AM.log_in_list.top().ac.UserID[i];
                }
                mapoflog.insert(std::to_string(num), l);
                if (AM.log_in_list.top().ac.Privilege >= 3) {
                    mapofemployee.insert(std::to_string(num), l);
                }
                continue;
            }
            if (scanner.getCommand() == "modify") {
                if (AM.cur_privilege < 3 || scanner.tokens.size() < 3 || scanner.tokens.size() % 2 == 0) {
                    throw Error();
                    continue;
                }
                bool ISBNmodify = false;
                bool NAMEmodify = false;
                bool AUTHORmodify = false;
                bool KEYWORDmodify = false;
                bool PRICEmodify = false;
                for (int i = 1; i < scanner.tokens.size() - 1; i++)
                {
                    if (scanner.tokens[i] == "ISBN") {
                        if (ISBNmodify) {
                            throw Error();
                        }
                        i++;
                        if (!BM.selected) {
                            throw Error();
                        }
                        ISBN bb = BM.bookselected_;
                        ISBN ii(scanner.tokens[i]);
                        std::stack<tmpAccount> tempStack;
                        bool found = false;
                        while (!AM.log_in_list.empty()) {
                            if (AM.log_in_list.top().book_selected == bb) {
                                AM.log_in_list.top().book_selected = ii;
                            }
                            tempStack.push(AM.log_in_list.top());
                            AM.log_in_list.pop();
                        }
                        while (!tempStack.empty()) {
                            AM.log_in_list.push(tempStack.top());
                            tempStack.pop();
                        }
                        BM.modify(scanner.tokens[i], 0);
                        ISBNmodify = true;
                        continue;
                    }
                    if (scanner.tokens[i] == "name") {
                        if (NAMEmodify) {
                            throw Error();
                        }
                        i++;
                        BM.modify(scanner.tokens[i], 1);
                        NAMEmodify = true;
                        continue;
                    }
                    if (scanner.tokens[i] == "author") {
                        if (AUTHORmodify) {
                            throw Error();
                        }
                        i++;
                        BM.modify(scanner.tokens[i], 2);
                        AUTHORmodify = true;
                        continue;
                    }
                    if (scanner.tokens[i] == "keyword") {
                        if (KEYWORDmodify) {
                            throw Error();
                        }
                        i++;
                        BM.modify(scanner.tokens[i], 3);
                        KEYWORDmodify = true;
                        continue;
                    }
                    if (scanner.tokens[i] == "price") {
                        if (PRICEmodify) {
                            throw Error();
                        }
                        i++;
                        BM.modify(scanner.tokens[i], 4);
                        PRICEmodify = true;
                        continue;
                    }
                    throw Error();
                }
                for (int i = 0; i < 30; i++) {
                    l.userID_[i] = AM.log_in_list.top().ac.UserID[i];
                }
                mapoflog.insert(std::to_string(num), l);
                if (AM.log_in_list.top().ac.Privilege >= 3) {
                    mapofemployee.insert(std::to_string(num), l);
                }
                continue;
            }
            if (scanner.getCommand() == "import") {
                if (AM.cur_privilege < 3 || scanner.tokens.size() != 3) {
                    throw Error();
                    continue;
                }
                BM.import(scanner.tokens[1], scanner.tokens[2]);
                for (int i = 0; i < 30; i++) {
                    l.userID_[i] = AM.log_in_list.top().ac.UserID[i];
                }
                mapoflog.insert(std::to_string(num), l);
                if (AM.log_in_list.top().ac.Privilege >= 3) {
                    mapofemployee.insert(std::to_string(num), l);
                }
                mapoffinance.insert(std::to_string(num), l);
                continue;
            }
            if (scanner.getCommand() == "log") {
                if (AM.cur_privilege < 7) {
                    throw Error();
                    continue;
                }
                Node<Log> minimal = mapoflog.Findminimal();
                Node<Log> maximal = mapoflog.Findmaximal();
                std::vector<Node<Log>> tmp = mapoflog.Find(maximal, minimal);
                for (int i = 0; i < tmp.size(); i++) {
                    std::cout << tmp[i].value.userID_ << ' ' << tmp[i].value.command << std::endl;
                }
                continue;
            }
            if (scanner.getCommand() == "report") {
                if (scanner.tokens[1] == "finance") {
                    Node<Log> minimal = mapoffinance.Findminimal();
                    Node<Log> maximal = mapoffinance.Findmaximal();
                    std::vector<Node<Log>> tmp = mapoffinance.Find(maximal, minimal);
                    for (int i = 0; i < tmp.size(); i++) {
                        std::cout << tmp[i].value.userID_ << ' ' << tmp[i].value.command << std::endl;
                    }
                }
                if (scanner.tokens[1] == "employee") {
                    Node<Log> minimal = mapofemployee.Findminimal();
                    Node<Log> maximal = mapofemployee.Findmaximal();
                    std::vector<Node<Log>> tmp = mapofemployee.Find(maximal, minimal);
                    for (int i = 0; i < tmp.size(); i++) {
                        std::cout << tmp[i].value.userID_ << ' ' << tmp[i].value.command << std::endl;
                    }
                }
                continue;
            }
            throw Error();
            continue;
        }
        catch(const Error& e) {
            std::cout << "Invalid" << std::endl;
        }
    }
    while (!AM.log_in_list.empty()) {
        AM.log_in_list.pop();
    }
    return 0;
}