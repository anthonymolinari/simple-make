//
// Created by anthony on 11/2/21.
//

#include "ReaderToTokenizer.hpp"

ReaderToTokenizer::ReaderToTokenizer(std::string filename): nameOfInput(filename) {
    _inStream = std::ifstream(nameOfInput,std::ios::in);
    if (!_inStream.is_open()) {
        std::cout << "Unable to open " << filename << ". Terminating...";
        exit(1);
    }
    lastToken = new Token();
}
ReaderToTokenizer::~ReaderToTokenizer() {
    this->_inStream.close(); // close file, done reading
}

// maybe change or remove this. Can source files have numbers in their names?
bool ReaderToTokenizer::isValidFilename(std::string filename) {
    for (auto c : filename) {
        if (!std::isalpha(c) && c != '.')
            return false;
    }
    return true;
}

void ReaderToTokenizer::errorExit(std::string msg) {
    std::cout << msg;
    exit(2);
}

Token* ReaderToTokenizer::getToken() {
    char c;

    // discard c, it is a whitespace char but not end of line
    while(_inStream.get(c) && c != '\n' && isspace(c) && c != '\t');

    Token *token = new Token();

    if (_inStream.eof()) {
        token->eof() = true;
    } else if (c == '\n') {
        token->eol() = true;
    } else if (c == '\t') {
        // make sure previous token is eol
        if (lastToken->eol())
            token->isTab() = true;
        else
            errorExit("Misplaces TAB character. Terminating...");
    } else if (c == ':') {
        // make sure previous token is a target
        token->isColon() = true;
    } else if (std::isalpha(c)) {
        // either command or filename
        if (lastToken->isTab()) {
            // command line
            _inStream.putback(c);
            std::string command = "";
            // read entire command into string
            while(_inStream.peek() != '\n' && _inStream.get(c)) {
                command.push_back(c);
            }
            token->isCommand() = true;
            token->context(command);
        } else if (lastToken->isColon() || lastToken->isDep()) {
            // dep found
            _inStream.putback(c);
            std::string filename = "";
            // parse filename (possibly change to while not null && not space chars)
            while((std::isalpha(_inStream.peek()) || _inStream.peek() == '.'  || _inStream.peek() == '_') && _inStream.get(c)) {
                filename.push_back(c);
            }
            if (!isValidFilename(filename)) {
                std::cout << "Syntax Error: invalid filename " << filename << ". Terminating...";
                exit(2);
            }
            token->isDep() = true;
            token->context(filename);
        } else if (lastToken->eol() || lastToken->isNull()) {
            // target found - later combine with dep to make code less verbose
            _inStream.putback(c);
            std::string filename = "";
            while((std::isalpha(_inStream.peek()) || _inStream.peek() == '.' ) && _inStream.get(c)) {
                filename.push_back(c);
            }
            token->isTarget() = true;
            token->context(filename);
        }
    } else {
        std::cout << "Syntax Error: misplaced character " << c << ". Terminating...";
        exit(2);
    }
    // save last token;
    lastToken = token;
    return token;
}

