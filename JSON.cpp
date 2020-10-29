#include "JSON.h"

#include <fstream>
#include <regex>

JSON JSON::parseFromString(const std::string &inputOrFile)
{
    return parse(inputOrFile);
}

JSON JSON::parseFromFile(const std::string &filename)
{
    std::ifstream jsonFile(filename);
    if (jsonFile.fail())
    {
        throw JSON::ParseException("File cannot be read");
    }

    return parseFromStream(jsonFile);
}

JSON JSON::parseFromStream(std::istream &stream)
{
    return parse(std::string(std::istreambuf_iterator<char>(stream), {}));
}

JSON JSON::parse(const std::string &input)
{
    static const std::regex jsonParseRegex("\\s*\"([a-z_]*)\"\\s*:\\s*([0-9]*\\.?[0-9]+|\"[\\w\\s\\./]+\")\\s*([,}])\\s*");

    bool foundLast = false;
    std::string worker(input);
    std::smatch matches;
    std::map<std::string, std::any> properties;
    while (std::regex_search(worker, matches, jsonParseRegex))
    {
        if (foundLast)
        {
            throw JSON::ParseException("Data found after closing tag");
        }

        if (matches.size() == 4)
        {
            if (matches[3].str() == "}")
            {
                foundLast = true;
            }

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

    if (worker.length() > 0)
    {
        throw JSON::ParseException("Wrong format: Missing key or value");
    }

    return JSON(properties);
}
