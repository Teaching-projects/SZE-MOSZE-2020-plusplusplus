#pragma once

#include <map>
#include <string>

class Json
{
public:
    static std::map<std::string, std::string> ParseJson(const std::string &inputOrFile);
    static std::map<std::string, std::string> ParseJson(std::istream &stream);

private:
    static std::map<std::string, std::string> parseFromString(const std::string &input);
};