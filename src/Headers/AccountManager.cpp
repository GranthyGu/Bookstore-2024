/*
 * File: AccountManager.cpp
 * ----------------------
 * Implementation for the AccountManager class.
 */

#include "AccountManager.hpp"

Account::Account() : Privilege(-1) {
    memset(UserID, 0, sizeof(UserID));
    memset(Password, 0, sizeof(Password));
    memset(Username, 0, sizeof(Username));
}
Account::Account(std::string ID) : Privilege(1) {
    if (ID.length() > 30) {
        throw Error();
    } else {
        for (int i = 0; i < ID.length(); i++) {
            UserID[i] = ID[i];
        }
        for (int i = ID.length(); i < 30; i++) {
            UserID[i] = '\0';
        }
    }
}
Account::Account(std::string ID, std::string password, std::string username) : Privilege(1) {
    if (ID.length() > 30 || password.length() > 30 || username.length() > 30) {
        throw Error();
    }
    for (int i = 0; i < ID.length(); i++) {
        UserID[i] = ID[i];
    }
    for (int i = ID.length(); i < 30; i++)
    {
        UserID[i] = '\0';
    }
    for (int i = 0; i < password.length(); i++) {
        Password[i] = password[i];
    }
    for (int i = password.length(); i < 30; i++)
    {
        Password[i] = '\0';
    }
    for (int i = 0; i < username.length(); i++) {
        Username[i] = username[i];
    }
    for (int i = username.length(); i < 30; i++)
    {
        Username[i] = '\0';
    }
}
Account::Account(std::string ID, std::string password, std::string username, int pri) : Privilege(pri) {
    if (ID.length() > 30 || password.length() > 30 || username.length() > 30) {
        throw Error();
    }
    for (int i = 0; i < ID.length(); i++) {
        UserID[i] = ID[i];
    }
    for (int i = ID.length(); i < 30; i++)
    {
        UserID[i] = '\0';
    }
    for (int i = 0; i < password.length(); i++) {
        Password[i] = password[i];
    }
    for (int i = password.length(); i < 30; i++)
    {
        Password[i] = '\0';
    }
    for (int i = 0; i < username.length(); i++) {
        Username[i] = username[i];
    }
    for (int i = username.length(); i < 30; i++)
    {
        Username[i] = '\0';
    }
}
bool Account::operator<(const Account& other) {
    for (int i = 0; i < 30; i++) {
        if (UserID[i] != other.UserID[i]) {
            return UserID[i] < other.UserID[i];
        }
    }
    return false;
}
bool Account::operator>(const Account& other) {
    for (int i = 0; i < 30; i++) {
        if (UserID[i] != other.UserID[i]) {
            return UserID[i] > other.UserID[i];
        }
    }
    return false;
}
bool Account::operator==(const Account& other) const {
    for (int i = 0; i < 30; i++) {
        if (UserID[i] != other.UserID[i]) {
            return false;
        }
    }
    return true;
}
Account& Account::operator=(const Account& other) {
    Privilege = other.Privilege;
    for (int i = 0; i < 30; i++) {
        UserID[i] = other.UserID[i];
        Password[i] = other.Password[i];
        Username[i] = other.Username[i];
    }
    return *this;
}

tmpAccount::tmpAccount() : selected(false) {}
tmpAccount::tmpAccount(Account a) : ac(a), selected(false) {}

AccountManagement::AccountManagement() : cur_privilege(7) {
    mapofUserID.set_file_names("File_of_UserID", "File_of_UserID_");
    mapofUserID.openfile();
}
void AccountManagement::AcInitial() {
    Account manager("root", "sjtu", "root", 7);
    mapofUserID.insert("root", manager);
    return;
}
void AccountManagement::su(std::string ID) {
    if (log_in_list.empty() || ID.length() > 30) {
        throw Error();
        return;
    }
    Account certain(ID);
    Node<Account> tmp(ID, certain);
    std::vector<Node<Account>> outcome = mapofUserID.Find(tmp, tmp);
    if (outcome.size() != 1) {
        throw Error();
        return;
    }
    if (outcome[0].value.Privilege >= log_in_list.top().ac.Privilege) {
        throw Error();
        return;
    } else {
        tmpAccount cur(outcome[0].value);
        log_in_list.push(cur);
        cur_privilege = outcome[0].value.Privilege;
    }
}
void AccountManagement::su(std::string ID, std::string password) {
    if (ID.length() > 30 || password.length() > 30) {
        throw Error();
        return;
    }
    for (int i = password.length(); i < 30; i++) {
        password += '\0';
    }
    Account certain(ID);
    Node<Account> tmp(ID, certain);
    std::vector<Node<Account>> outcome = mapofUserID.Find(tmp, tmp);
    if (outcome.size() != 1) {
        throw Error();
        return;
    }
    for (int i = 0; i < 30; i++) {
        if (password[i] != outcome[0].value.Password[i]) {
            throw Error();
            return;
        }
    }
    tmpAccount cur(outcome[0].value);
    log_in_list.push(cur);
    cur_privilege = outcome[0].value.Privilege;
}
void AccountManagement::logout() {
    if (log_in_list.empty()) {
        throw Error();
        return;
    } else {
        log_in_list.pop();
        if (log_in_list.empty()) {
            cur_privilege = -1;
            return;
        }
        tmpAccount tmp = log_in_list.top();
        cur_privilege = tmp.ac.Privilege;
        return;
    }
}
void AccountManagement::Register(std::string ID, std::string password, std::string username) {
    if (ID.length() > 30 || password.length() > 30 || username.length() > 30)
    {
        throw Error();
        return;
    }
    Account certain(ID, password, username);
    Node<Account> tmp(ID, certain);
    std::vector<Node<Account>> outcome = mapofUserID.Find(tmp, tmp);
    if (outcome.size() != 0) {
        throw Error();
        return;
    }
    mapofUserID.insert(ID, certain);
}
void AccountManagement::passwd(std::string ID, std::string new_password) {
    if (ID.length() > 30 || new_password.length() > 30) {
        throw Error();
        return;
    }
    if (log_in_list.empty()) {
        throw Error();
        return;
    } 
    Account tmp = log_in_list.top().ac;
    if (tmp.Privilege != 7) {
        throw Error();
        return;
    } else {
        Account certain(ID);
        Node<Account> tmp(ID, certain);
        std::vector<Node<Account>> outcome = mapofUserID.Find(tmp, tmp);
        if (outcome.size() != 1) {
            throw Error();
            return;
        }
        mapofUserID.remove(ID, outcome[0].value);
        memset(outcome[0].value.Password, 0, sizeof(outcome[0].value.Password));
        for (int i = 0; i < new_password.length(); i++) {
            outcome[0].value.Password[i] = new_password[i];
        }
        mapofUserID.insert(ID, outcome[0].value);
    }
}
void AccountManagement::passwd(std::string ID, std::string password, std::string new_password) {
    if (ID.length() > 30 || password.length() > 30 || new_password.length() > 30) {
        throw Error();
        return;
    }
    for (int i = password.length(); i < 30; i++) {
        password += '\0';
    }
    if (log_in_list.empty()) {
        throw Error();
        return;
    } else {
        Account certain(ID);
        Node<Account> tmp(ID, certain);
        std::vector<Node<Account>> outcome = mapofUserID.Find(tmp, tmp);
        if (outcome.size() != 1) {
            throw Error();
            return;
        }
        for (int i = 0; i < 30; i++) {
            if (password[i] != outcome[0].value.Password[i]) {
                throw Error();
                return;
            }
        }
        mapofUserID.remove(ID, outcome[0].value);
        memset(outcome[0].value.Password, 0, sizeof(outcome[0].value.Password));
        for (int i = 0; i < new_password.length(); i++) {
            outcome[0].value.Password[i] = new_password[i];
        }
        mapofUserID.insert(ID, outcome[0].value);
    }
}
void AccountManagement::useradd(std::string ID, std::string password, std::string privilege, std::string username) {
    int num = -1;
    try {
        num = std::stoi(privilege);
    }
    catch(const std::exception& e) {
        throw Error();
    }
    if (ID.length() > 30 || password.length() > 30 || username.length() > 30 || log_in_list.empty()) {
        throw Error();
        return;
    }
    Account tmp = log_in_list.top().ac;
    if (tmp.Privilege < 3 || (num != 0 && num != 1 && num != 3) || num >= tmp.Privilege) {
        throw Error();
        return;
    }
    Account certain(ID);
    Node<Account> tmpp(ID, certain);
    std::vector<Node<Account>> outcome = mapofUserID.Find(tmpp, tmpp);
    if (outcome.size() != 0) {
        throw Error();
        return;
    } else {
        Account cur(ID, password, username, num);
        mapofUserID.insert(ID, cur);
        return;
    }
}
void AccountManagement::Delete(std::string ID) {
    if (ID.length() > 30 || log_in_list.empty()) {
        throw Error();
        return;
    }
    Account tmp = log_in_list.top().ac;
    if (tmp.Privilege != 7) {
        throw Error();
        return;
    } else {
        Account certain(ID);
        Node<Account> tmp(ID, certain);
        std::vector<Node<Account>> outcome = mapofUserID.Find(tmp, tmp);
        if (outcome.size() != 1) {
            throw Error();
            return;
        }
        std::stack<tmpAccount> tempStack;
        bool found = false;
        while (!log_in_list.empty()) {
            if (log_in_list.top().ac == certain) {
                found = true;
                break;
            }
            tempStack.push(log_in_list.top());
            log_in_list.pop();
        }
        while (!tempStack.empty()) {
            log_in_list.push(tempStack.top());
            tempStack.pop();
        }
        if (found) {
            throw Error();
            return;
        }
        mapofUserID.remove(ID, certain);
        return;
    }
}