/*
 * File: tokenscanner.cpp
 * ----------------------
 * Implementation for the TokenScanner class.
 */

#include "tokenscanner.hpp"

TokenScanner::TokenScanner() {}
TokenScanner::TokenScanner(const std::string& input) : input(input) {}

void TokenScanner::set_input(const std::string& new_input) {
    input.clear();
    input = new_input;
}

bool TokenScanner::containsInvalidCharacters() const {
    for (char c : input) {
        if (c < 32 || c > 126) {
            if (c != ' ') {
                return true;
            }
        }
    }
    return false;
}

bool TokenScanner::QuotedString(int& pos, std::string& token) {
    pos++;
    if (input[pos] == '"') {
        return false;
    }
    while (pos < input.length() && input[pos] != '"') {
        token += input[pos];
        pos++;
    }
    if (input[pos] == '"' && pos != input.length() - 1) {
        if (input[pos + 1] != ' ') {
            return false;
        }
    }
    if (pos >= input.length()) {
        return false;
    }
    pos++;
    return true;
}

bool TokenScanner::Parameter(int& pos, std::string& token) {
    if (pos >= input.length()) {
        return false;
    }
    if (input[pos] == '"') {
        std::string quotedValue;
        if (!QuotedString(pos, quotedValue)) {
            return false;
        }
        token += quotedValue;
    } else {
        if (tokens[tokens.size() - 1] != "ISBN" && tokens[tokens.size() - 1] != "price") {
            return false;
        }
        if (input[pos] == ' ') {
            return false;
        }
        while (pos < input.length() && input[pos] != ' ') {
            token += input[pos];
            pos++;
        }
    }
    return true;
}

void TokenScanner::skipSpaces(int& pos) {
    while (pos < input.length() && input[pos] == ' ') {
        pos++;
    }
}

const std::vector<std::string>& TokenScanner::getTokens() const {
    return tokens;
}

std::string TokenScanner::getCommand() const {
    if (tokens.empty()) {
        throw Error();
    } else {
        return tokens[0];
    }
}

bool TokenScanner::scan() {
    if (containsInvalidCharacters()) {
        throw Error();
    }
    tokens.clear();
    int pos = 0;
    skipSpaces(pos);
    while (pos < input.length()) {
        std::string token;
        if (input[pos] == '-' && tokens.size() > 0 && (tokens[0] == "show" || tokens[0] == "modify")) {
            pos++;
            while (pos < input.length() && input[pos] != '=' && input[pos] != ' ') {
                token += input[pos];
                pos++;
            }
            if (input[pos] == ' ' || pos == input.length()) {
                throw Error();
            }
            tokens.push_back(token);
            token.clear();
            if (pos < input.length() && input[pos] == '=') {
                pos++;
                if (!Parameter(pos, token)) {
                    throw Error();
                    return false;
                }
                tokens.push_back(token);
            }
            skipSpaces(pos);
            continue;
        }
        while (pos < input.length() && input[pos] != ' ') {
            token += input[pos];
            pos++;
        }
        if (!token.empty()) {
            tokens.push_back(token);
        }
        skipSpaces(pos);
    }
    return true;
}