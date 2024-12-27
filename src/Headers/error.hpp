// Created by GranthyGu on 2024/12/23

#ifndef ERROR_HPP
#define ERROR_HPP

/*
 * File: error.h
 * --------------------
 * This file exports an Error class that handle the errors we throw.
 */

#include <iostream>

class Error {
public:
    Error();
    void handle_the_error();
};

#endif      //ERROR_HPP
