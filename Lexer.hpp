#pragma once
#include <vector>
#include <string>
#include <unordered_map>
#include "TokenTypes.hpp"

std::vector<Token> lex(const std::string& text);
bool isType(const std::string& str);
bool isAtom(const std::string& str);
bool isOperator(const std::string& str);
bool isExpression(const std::string& str);
float getbindingpower(const std::string& op, int mode);
std::vector<std::string> split(const std::string& input);
std::unordered_map<int, std::vector<int>> splitline(const std::string& text);
