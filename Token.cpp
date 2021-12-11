//
// Created by anthony on 11/2/21.
//

#include "Token.hpp"

void Token::print() {
    if ( eol()             ) std::cout << "EOL";
    else if ( eof()        ) std::cout << "EOF";
    else if ( isTab()      ) std::cout << "TAB";
    else if ( isColon()    ) std::cout << ":";
    else if ( isDep()      ) std::cout << context();
    else if ( isTarget()   ) std::cout << context();
    else if ( isCommand()  ) std::cout << context();
    else {
        std::cout << "Token::print -- Came across an unknown token. Terminating...\n";
        exit(3);
    }
}

bool Token::isNull() {
    return !(_eol || _eof || _isColon || _isTab || _isCommand || _isDep || _isTarget);
}