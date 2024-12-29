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

int main() {
    // freopen("in.txt", "r", stdin);   // 读入in.dat文件作为输入 
	// freopen("out.dat", "w", stdout);  // 将输入写入out.dat文件中 
    TokenScanner scanner;
    BookManager BM;
    AccountManagement AM;
    AM.AcInitial();
    LogManagement LM;
    BM.setLogManagement(LM);
    while (true) {
        try {
            std::string str;
            if (!getline(std::cin, str)) {
                break;
            }
            scanner.set_input(str);
            scanner.scan();
            if (scanner.getCommand() == "quit" || scanner.getCommand() == "exit") {
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
                    BM.bookselected = tmp;
                }
                if (scanner.tokens.size() == 3) {
                    AM.su(scanner.tokens[1], scanner.tokens[2]);
                    BM.selected = false;
                    Book tmp;
                    BM.bookselected = tmp;
                }
                continue;
            }
            if (scanner.getCommand() == "logout") {
                if (scanner.tokens.size() != 1) {
                    throw Error();
                    continue;
                }
                AM.logout();
                if (AM.cur_privilege == -1) {
                    BM.selected = false;
                    Book tmp;
                    BM.bookselected = tmp;
                    continue;
                }
                tmpAccount tmp = AM.log_in_list.top();
                BM.selected = tmp.selected;
                BM.bookselected = tmp.book_selected;
                continue;
            }
            if (scanner.getCommand() == "register") {
                if (scanner.tokens.size() != 4) {
                    throw Error();
                    continue;
                }
                AM.Register(scanner.tokens[1], scanner.tokens[2], scanner.tokens[3]);
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
                continue;
            }
            if (scanner.getCommand() == "useradd") {
                if (scanner.tokens.size() != 5) {
                    throw Error();
                    continue;
                }
                AM.useradd(scanner.tokens[1], scanner.tokens[2], scanner.tokens[3], scanner.tokens[4]);
                continue;
            }
            if (scanner.getCommand() == "delete") {
                if (scanner.tokens.size() != 2) {
                    throw Error();
                    continue;
                }
                AM.Delete(scanner.tokens[1]);
                continue;
            }
            if (scanner.getCommand() == "show") {
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
                        double income = BM.LM.calcincome(num);
                        double outcome = BM.LM.calcoutcome(num);
                        std::cout << std::fixed << std::setprecision(2);
                        std::cout << "+ " << income << " - " << outcome << std::endl;
                    }
                    if (scanner.tokens.size() == 2) {
                        int num = BM.LM.Finance.size();
                        double income = BM.LM.calcincome(num);
                        double outcome = BM.LM.calcoutcome(num);
                        std::cout << std::fixed << std::setprecision(2);
                        std::cout << "+ " << income << " - " << outcome << std::endl;
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
                        continue;
                    }
                    if (scanner.tokens[1] == "name")
                    {
                        BM.show(scanner.tokens[2], 1);
                        continue;
                    }
                    if (scanner.tokens[1] == "author")
                    {
                        BM.show(scanner.tokens[2], 2);
                        continue;
                    }
                    if (scanner.tokens[1] == "keyword")
                    {
                        BM.show(scanner.tokens[2], 3);
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
                tmp.book_selected = BM.bookselected;
                tmp.selected = BM.selected;
                AM.log_in_list.pop();
                AM.log_in_list.push(tmp);
                continue;
            }
            if (scanner.getCommand() == "modify") {
                if (AM.cur_privilege < 3 || scanner.tokens.size() < 3) {
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
                }
                continue;
            }
            if (scanner.getCommand() == "import") {
                if (AM.cur_privilege < 3 || scanner.tokens.size() != 3) {
                    throw Error();
                    continue;
                }
                BM.import(scanner.tokens[1], scanner.tokens[2]);
                continue;
            }
            if (scanner.getCommand() == "log") {
                /* code */
                continue;
            }
            throw Error();
            continue;
        }
        catch(const Error& e) {
            std::cout << "Invalid" << std::endl;
        }
    }
}