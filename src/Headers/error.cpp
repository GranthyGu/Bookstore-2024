/*
 * File: error.cpp
 * ----------------------
 * Implementation for the Error class.
 */

#include "error.hpp"

Error::Error() {}

void Error::handle_the_error() {
    std::cout << "Invalid\n";
    return;
}
