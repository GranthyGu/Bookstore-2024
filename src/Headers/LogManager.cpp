/*
 * File: BookManager.cpp
 * ----------------------
 * Implementation for the LogManager class.
 */

#include "LogManager.hpp"

LogManagement::LogManagement() {
    Finance.clear();
    std::fstream tmp;
    filename = "File_of_Log";
    tmp.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!tmp) {
        tmp.close();
        tmp.clear(); 
        tmp.open(filename, std::ios::out | std::ios::binary);
        tmp.close();
        tmp.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    }
    double value;
    while (tmp.read(reinterpret_cast<char*>(&value), sizeof(double))) {
        Finance.push_back(value);
    }
}

LogManagement& LogManagement::operator=(const LogManagement &other) {
    Finance.clear();
    for (int i = 0; i < other.Finance.size(); i++){
        Finance.push_back(other.Finance[i]);
    }
    return *this;
}

void LogManagement::addinfo(double l) {
    Finance.push_back(l);
}

double LogManagement::calcincome(int n) {
    if (n > Finance.size()) {
        throw Error();
    }
    double tmp = 0;
    for (int i = 0; i < n; i++) {
        if (Finance[Finance.size() - 1 - i] > 0) {
            tmp += Finance[Finance.size() - 1 - i];
        }
    }
    return tmp;
}

double LogManagement::calcoutcome(int n) {
    if (n > Finance.size()) {
        throw Error();
    }
    double tmp = 0;
    for (int i = 0; i < n; i++) {
        if (Finance[Finance.size() - 1 - i] < 0) {
            tmp += -Finance[Finance.size() - 1 - i];
        }
    }
    return tmp;
}

void LogManagement::writetofile() {
    std::fstream tmp;
    tmp.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    if (!tmp) {
        tmp.close();
        tmp.clear(); 
        tmp.open(filename, std::ios::out | std::ios::binary);
        tmp.close();
        tmp.open(filename, std::ios::in | std::ios::out | std::ios::binary);
    }
    tmp.clear();
    for (int i = 0; i < Finance.size(); i++) {
        tmp.write(reinterpret_cast<char*>(&Finance[i]), sizeof(double));
    }
}