#include <iostream>
#include <vector>
#include <string>
#include "Lexer.hpp"

void printToken(const Token& token) {
    switch (token.type) {
        case TokenType::Atom:
            std::cout << "Atom(" << token.atom.atomname << ")\n";
            break;
        case TokenType::Operator:
            std::cout << "Operator(" << token.op.operatorname << ")\n";
            break;
        case TokenType::Expression:
            std::cout << "Expression(" << token.expr.expression << ")\n"; // Implement deeper printing if needed
            break;
        case TokenType::Type:
            std::cout << "Type(" << token.dtype.type << ")\n";
    }
}

int main() {
    std::string input = "int a; int a = 1; std.cout; cout; std; using namespace 1; a += 1; ";
    std::vector<Token> tokens = lex(input);

    for (const Token& t : tokens) {
        printToken(t);
    }

    return 0;
}
