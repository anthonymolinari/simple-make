//
// Created by anthony on 11/2/21.
//

#ifndef MAKESTUDENTFILES_READERTOTOKENIZER_HPP
#define MAKESTUDENTFILES_READERTOTOKENIZER_HPP

#include "Token.hpp"
#include <fstream>
#include <iostream>
#include <string>

class ReaderToTokenizer {
public:
    ReaderToTokenizer( std::string );
    Token* getToken();
    ~ReaderToTokenizer();

private:
    std::ifstream _inStream;
    std::string nameOfInput;
    Token *lastToken;

    static void errorExit(std::string);
    static bool isValidFilename ( std::string );
    static bool isCommandChar ( char );
};

#endif //MAKESTUDENTFILES_READERTOTOKENIZER_HPP
