// Created by GranthyGu on 2024/12/27

#ifndef LOG_MANAGER_HPP
#define LOG_MANAGER_HPP

/*
 * File: AccountManager.hpp
 * --------------------
 * This file exports a logmanager class that has functions that we need 
 * when we manage logs' information.
 */

#include <iostream>
#include <vector>
#include "error.hpp"

class LogManagement {
public:
    std::vector<double> Finance;
    LogManagement();
    LogManagement& operator=(const LogManagement &other);
    void addinfo(double l);
    double calcincome(int n);
    double calcoutcome(int n);
};

#endif      // LOG_MANAGER_HPP