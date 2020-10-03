#include "json.h"

#include <fstream>
#include <regex>

// Can accept json as parameter or a filename which will be read from the filesystem
// The parameter will be threated as Json if includes a { character
std::map<std::string, std::string> Json::ParseJson(const std::string &inputOrFile)
{
    if (inputOrFile.find_first_of("{", 0) != std::string::npos)
    {
        return parseFromString(inputOrFile);
    }

    std::ifstream jsonFile(inputOrFile);
    if (jsonFile.fail())
    {
        const std::string errMessage("Error: No such file: " + inputOrFile);
        throw std::runtime_error(errMessage);
    }

    return ParseJson(jsonFile);
}

std::map<std::string, std::string> Json::ParseJson(std::istream &stream)
{
    return parseFromString(std::string(std::istreambuf_iterator<char>(stream), {}));
}

std::map<std::string, std::string> Json::parseFromString(const std::string &input)
{
    static const std::regex jsonParseRegex("\\s*\"([a-z]*)\"\\s*:\\s*\"?(\\w*)\"?\\s*[,}]\\s*");

    std::string worker(input);
    std::smatch matches;
    std::map<std::string, std::string> properties;
    while (std::regex_search(worker, matches, jsonParseRegex))
    {
        if (matches.size() == 3)
        {
            properties[matches[1]] = matches[2];
        }
        worker = matches.suffix();
    }

    return properties;
}