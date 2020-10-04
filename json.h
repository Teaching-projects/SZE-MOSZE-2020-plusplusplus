#pragma once

#include <map>
#include <string>
#include <any>

class Json
{
public:
    static std::map<std::string, std::any> ParseJson(const std::string &inputOrFile);
    static std::map<std::string, std::any> ParseJson(std::istream &stream);

private:
    static std::map<std::string, std::any> parseFromString(const std::string &input);
};