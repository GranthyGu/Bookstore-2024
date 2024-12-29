// Created by GranthyGu on 2024/12/25

#ifndef ACCOUNT_MANAGER_HPP
#define ACCOUNT_MANAGER_HPP

/*
 * File: AccountManager.hpp
 * --------------------
 * This file exports a accountmanager class that has functions that we need 
 * when we manage accounts' information.
 */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <unordered_map>
#include "maplist.hpp"
#include "BookManager.hpp"

class Account {
public:
    char UserID[30];
    char Password[30];
    char Username[30];
    int Privilege;
    Account();
    Account(std::string ID);
    Account(std::string ID, std::string password, std::string username);
    Account(std::string ID, std::string password, std::string username, int pri);
    bool operator<(const Account& other);
    bool operator>(const Account& other);
    bool operator==(const Account& other) const;
    Account& operator=(const Account& other);
};

struct tmpAccount {
    Account ac;
    bool selected;
    Book book_selected;
    tmpAccount();
    tmpAccount(Account a);
};

class AccountManagement {
private:
    maplist<Account> mapofUserID;
public:
    std::stack<tmpAccount> log_in_list;
    int cur_privilege;
    AccountManagement();
    void AcInitial();
    void su(std::string ID);
    void su(std::string ID, std::string password);
    void logout();
    void Register(std::string ID, std::string password, std::string username);
    void passwd(std::string ID, std::string password, std::string new_password);
    void passwd(std::string ID, std::string new_password);
    void useradd(std::string ID, std::string password, std::string privilege, std::string username);
    void Delete(std::string ID);
};

#endif      // ACCOUNT_MANAGER_HPP
