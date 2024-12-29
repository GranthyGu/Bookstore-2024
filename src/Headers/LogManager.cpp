/*
 * File: BookManager.cpp
 * ----------------------
 * Implementation for the LogManager class.
 */

#include "LogManager.hpp"

LogManagement::LogManagement() {
    Finance.clear();
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
        if (Finance[i] > 0) {
            tmp += Finance[i];
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
        if (Finance[i] < 0) {
            tmp += -Finance[i];
        }
    }
    return tmp;
}

