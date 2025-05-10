#pragma once
#include <string>

enum class TokenType {
    Atom,
    Operator,
    Expression,
    Type
};

struct Atom {
    std::string atomname;
    Atom(const std::string& atomname) : atomname(atomname) {}
};

struct Operator {
    std::string operatorname;
    int lbind;
    int rbind;
    Operator(const std::string& operatorname, int lbind, int rbind)
        : operatorname(operatorname), lbind(lbind), rbind(rbind) {}
};

struct Expression {
    std::string expression;
    Expression(const std::string& expression) : expression(expression) {}
};

struct Type {
    std::string type;
    Type(const std::string& type) : type(type) {}
};

struct Token {
    TokenType type;
    union {
        Atom atom;
        Operator op;
        Expression expr;
        Type dtype;
    };

    Token(const Atom& a) : type(TokenType::Atom), atom(a) {}
    Token(const Operator& o) : type(TokenType::Operator), op(o) {}
    Token(const Expression& e) : type(TokenType::Expression), expr(e) {}
    Token(const Type& t) : type(TokenType::Type), dtype(t) {}

    Token(const Token& other);
    Token(Token&& other) noexcept;
    Token& operator=(const Token& other);
    Token& operator=(Token&& other) noexcept;
    ~Token();
};