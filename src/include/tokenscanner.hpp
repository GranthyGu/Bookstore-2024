// Created by GranthyGu on 2024/12/23

#ifndef TOKEN_SCANNER_HPP
#define TOKEN_SCANNER_HPP

/*
 * File: tokenscanner.h
 * --------------------
 * This file exports a <code>TokenScanner</code> class that divides
 * a string into individual logical units called <b><i>tokens</i></b>.
 */

#include <iostream>
#include <string>
#include <vector>

/*
 * class TokenScanner:
 * This class can divide a string into several logical tokens, and save them into a vector.
 * QuotedString can read the entire string within quotation marks.
 * Parameter can judge the string whether within quotation marks or not, and read them.
 * Scan can divide the string into different parts and save them.
 * getTokens is for getting the vector saving the tokens.
 * getCommand is for getting the first token, which is the command.
 * set_input can change the input, and we can scan the new input again.
 * 
 * Caution: for commands "show" and "modify", the tokens will be divided by '=' and ' '!
 */
class TokenScanner {
private:
    std::string input;
    std::vector<std::string> tokens;
    bool QuotedString(int& pos, std::string& token);
    bool Parameter(int& pos, std::string& token);
    void skipSpaces(int& pos);
public:
    TokenScanner(const std::string& input);
    void set_input(const std::string& new_input);
    bool scan();
    const std::vector<std::string>& getTokens() const;
    std::string getCommand() const;
};

#endif      //TOKEN_SCANNER_HPP