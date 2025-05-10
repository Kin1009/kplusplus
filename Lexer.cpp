#include "Lexer.hpp"
#include <unordered_set>
#include <sstream>
#include <cctype>
#include <stdexcept>

#define BIND_LEFT 0
#define BIND_RIGHT 1

float getbindingpower(const std::string& op, int mode) {
    if (op == "+" || op == "-") {
        return (mode == BIND_LEFT) ? 1.1f : 1.0f;
    } else if (op == "*" || op == "/") {
        return (mode == BIND_LEFT) ? 2.1f : 2.0f;
    }
    return 0.0f;
}

bool isType(const std::string& str) {
    return str == "int" || str == "string" || str == "list" || str == "void";
}

bool isAtom(const std::string& str) {
    if (str.empty()) return false;
    for (char c : str) {
        if (!isalnum(c) && c != '.' && c != '_') return false;
    }
    return true;
}

bool isOperator(const std::string& str) {
    static const std::unordered_set<char> validSymbols = {'!', '#', '$', '%', '&', '(', ')', '*', '+', ',', '-', '.', '/', ':', ';', '<', '=', '>', '?', '@', '[', ']', '^', '_', '`', '{', '}', '|', '~'};
    for (char c : str) {
        if (validSymbols.find(c) == validSymbols.end()) return false;
    }
    return true;
}

bool isExpression(const std::string& str) {
    return str.size() > 1 && ((str.front() == '{' && str.back() == '}') || (str.front() == '[' && str.back() == ']') || (str.front() == '(' && str.back() == ')'));
}

std::vector<std::string> split(const std::string& input) {
    std::string text;
    std::vector<std::string> lines;
    size_t start = 0;
    for (size_t i = 0; i <= input.size(); ++i) {
        if (i == input.size() || input[i] == '\n') {
            std::string line = input.substr(start, i - start);
            size_t comment = line.find('#');
            if (comment != std::string::npos)
                line = line.substr(0, comment);
            lines.push_back(line);
            start = i + 1;
        }
    }
    for (const auto& line : lines)
        text += line + ' ';
    std::vector<std::string> res;
    std::string a;
    std::string type = "str";
    int layer = 0;
    const std::string openm = "([{";
    const std::string closem = ")]}";
    bool in_string = false;
    char string_char = 0;
    for (char i : text) {
        if (layer == 0) {
            if (in_string) {
                a += i;
                if (i == string_char) {
                    res.push_back(a);
                    a.clear();
                    in_string = false;
                }
                continue;
            }
            if (i == '\'' || i == '"') {
                if (!a.empty()) res.push_back(a);
                a = i;
                in_string = true;
                string_char = i;
            }
            else if (openm.find(i) != std::string::npos) {
                if (!a.empty()) res.push_back(a);
                a = i;
                layer++;
            }
            else if (isalnum(i) || i == '_' || i == ':' || i == '.') {
                if (type == "str") {
                    a += i;
                } else {
                    if (!a.empty()) res.push_back(a);
                    a = i;
                    type = "str";
                }
            }
            else if (ispunct(i) && openm.find(i) == std::string::npos) {
                if (type == "punc") {
                    a += i;
                } else {
                    if (!a.empty()) res.push_back(a);
                    a = i;
                    type = "punc";
                }
            }
            else if (i == ' ') {
                if (!a.empty()) res.push_back(a);
                a.clear();
            }
            else if (closem.find(i) != std::string::npos) {
                throw std::runtime_error(std::string("Unexpected closing delimiter '") + i + "'");
            }
        } else {
            a += i;
            if (openm.find(i) != std::string::npos) {
                layer++;
            } else if (closem.find(i) != std::string::npos) {
                layer--;
                if (layer == 0) {
                    res.push_back(a);
                    a.clear();
                    type = "str";
                }
            }
        }
    }
    if (!a.empty()) res.push_back(a);
    return res;
}

std::unordered_map<int, std::vector<int>> splitline(const std::string& text) {
    std::vector<std::string> tokens = split(text);
    std::unordered_map<int, std::vector<int>> res;
    int idx = 0, c = 0, b = 0;
    for (size_t i = 0; i < tokens.size(); ++i) {
        const std::string& token = tokens[i];
        if (token == ";" || (!token.empty() && token.back() == '}')) {
            std::vector<int> indices;
            for (int j = 0; j < b; ++j)
                indices.push_back(idx + j);
            res[c++] = indices;
            idx += b;
            b = 0;
        } else {
            b++;
        }
    }
    return res;
}

std::vector<Token> lex(const std::string& text) {
    std::vector<Token> tokens;
    std::vector<std::string> splitText = split(text);
    for (size_t i = 0; i < splitText.size(); ++i) {
        const std::string& token = splitText[i];
        if (isType(token)) {
            tokens.push_back(Token(Type(token)));
        } else if (isAtom(token)) {
            tokens.push_back(Token(Atom(token)));
        } else if (isOperator(token)) {
            tokens.push_back(Token(Operator(token, getbindingpower(token, BIND_LEFT), getbindingpower(token, BIND_RIGHT))));
        } else {
            tokens.push_back(Token(Expression(token)));
        }
    }
    return tokens;
}
