#include "TokenTypes.hpp"

Token::Token(const Token& other) : type(other.type) {
    switch (type) {
        case TokenType::Atom:
            new (&atom) Atom(other.atom);
            break;
        case TokenType::Operator:
            new (&op) Operator(other.op);
            break;
        case TokenType::Expression:
            new (&expr) Expression(other.expr);
            break;
        case TokenType::Type:
            new (&dtype) Type(other.dtype);
            break;
    }
}

Token::Token(Token&& other) noexcept : type(other.type) {
    switch (type) {
        case TokenType::Atom:
            new (&atom) Atom(std::move(other.atom));
            break;
        case TokenType::Operator:
            new (&op) Operator(std::move(other.op));
            break;
        case TokenType::Expression:
            new (&expr) Expression(std::move(other.expr));
            break;
        case TokenType::Type:
            new (&dtype) Type(std::move(other.dtype));
            break;
    }
}

Token& Token::operator=(const Token& other) {
    if (this != &other) {
        this->~Token();
        type = other.type;
        switch (type) {
            case TokenType::Atom:
                new (&atom) Atom(other.atom);
                break;
            case TokenType::Operator:
                new (&op) Operator(other.op);
                break;
            case TokenType::Expression:
                new (&expr) Expression(other.expr);
                break;
            case TokenType::Type:
                new (&dtype) Type(other.dtype);
                break;
        }
    }
    return *this;
}

Token& Token::operator=(Token&& other) noexcept {
    if (this != &other) {
        this->~Token();
        type = other.type;
        switch (type) {
            case TokenType::Atom:
                new (&atom) Atom(std::move(other.atom));
                break;
            case TokenType::Operator:
                new (&op) Operator(std::move(other.op));
                break;
            case TokenType::Expression:
                new (&expr) Expression(std::move(other.expr));
                break;
            case TokenType::Type:
                new (&dtype) Type(std::move(other.dtype));
                break;
        }
    }
    return *this;
}

Token::~Token() {
    switch (type) {
        case TokenType::Operator:
            op.~Operator();
            break;
        case TokenType::Expression:
            expr.~Expression();
            break;
        case TokenType::Atom:
        case TokenType::Type:
        default:
            break;
    }
}