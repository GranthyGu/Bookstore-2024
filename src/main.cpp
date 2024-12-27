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
    TokenScanner scanner;
    BookManager BM;
    AccountManagement AM;
    while (true) {
        try {
            std::string str;
            getline(std::cin, str);
            scanner.set_input(str);
            scanner.scan();
            if (scanner.getCommand() == "quit" || scanner.getCommand() == "exit") {
                break;
            }
            if (scanner.getCommand() == "su") {
                if (scanner.tokens.size() != 2 || scanner.tokens.size() != 3) {
                    throw Error();
                    continue;
                }
                if (scanner.tokens.size() == 2) {
                    AM.su(scanner.tokens[1]);
                }
                if (scanner.tokens.size() == 3) {
                    AM.su(scanner.tokens[1], scanner.tokens[2]);
                }
                continue;
            }
            if (scanner.getCommand() == "logout") {
                if (scanner.tokens.size() != 1) {
                    throw Error();
                    continue;
                }
                AM.logout();
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
                if (scanner.tokens.size() != 4 || scanner.tokens.size() != 3) {
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
                /* code */
                continue;
            }
            if (scanner.getCommand() == "buy") {
                /* code */
                continue;
            }
            if (scanner.getCommand() == "select") {
                /* code */
                continue;
            }
            if (scanner.getCommand() == "modify") {
                /* code */
                continue;
            }
            if (scanner.getCommand() == "import") {
                /* code */
                continue;
            }
            if (scanner.getCommand() == "log") {
                /* code */
                continue;
            }
        }
        catch(const std::exception& e) {
            std::cerr << e.what() << '\n';
        }
    }
}