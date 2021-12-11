//
// Created by anthony on 11/2/21.
//

#ifndef MAKESTUDENTFILES_TOKEN_HPP
#define MAKESTUDENTFILES_TOKEN_HPP

#include <string>
#include <iostream>

class Token {
public:
    Token(): _eof(false),
             _eol(false),
             _isColon(false),
             _isTab(false),
             _isCommand(false),
             _isDep(false),
             _isTarget(false),
             _context("") {}

    bool& isColon()    { return _isColon; }
    bool& isTab()      { return _isTab; }
    bool& eol()        { return _eol; }
    bool& eof()        { return _eof; }
    bool& isDep()      { return _isDep; }
    bool& isTarget()   { return _isTarget; }
    bool& isCommand()  { return _isCommand; }

    bool isNull();

    void context(const std::string &str)  { _context = str;  }
    std::string context() const { return _context; }

    void print();
private:
    std::string _context;
    bool _eol, _eof, _isColon, _isTab, _isCommand, _isDep, _isTarget;
};


#endif //MAKESTUDENTFILES_TOKEN_HPP
