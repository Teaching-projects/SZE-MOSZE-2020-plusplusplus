#include "json.h"
#include "jsonFileReadError.h"

#include <fstream>
#include <regex>

std::map<std::string, std::any> Json::ParseString(const std::string &inputOrFile)
{
    return parseFromString(inputOrFile);
}

std::map<std::string, std::any> Json::ParseFile(const std::string &filename)
{
    std::ifstream jsonFile(filename);
    if (jsonFile.fail())
    {
        throw JsonFileReadError(filename);
    }

    return ParseStream(jsonFile);
}

std::map<std::string, std::any> Json::ParseStream(std::istream &stream)
{
    return parseFromString(std::string(std::istreambuf_iterator<char>(stream), {}));
}

std::map<std::string, std::any> Json::parseFromString(const std::string &input)
{
    static const std::regex jsonParseRegex("\\s*\"([a-z]*)\"\\s*:\\s*([0-9]*\\.?[0-9]+|\"[\\w\\s]*\")\\s*[,}]\\s*");

    std::string worker(input);
    std::smatch matches;
    std::map<std::string, std::any> properties;
    while (std::regex_search(worker, matches, jsonParseRegex))
    {
        if (matches.size() == 3)
        {
            std::string value = matches[2].str();
            if (value.at(0) == '"')
            {
                value.erase(value.begin());
                value.erase(value.end() - 1);
                properties[matches[1]] = value;
            }
            else if (value.find_first_of('.') != std::string::npos)
            {
                properties[matches[1]] = stof(value);
            }
            else
            {
                properties[matches[1]] = stoi(value);
            }
        }
        worker = matches.suffix();
    }

    return properties;
}