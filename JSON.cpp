#include "JSON.h"

#include <fstream>

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
    //                                              key                 int     double       string                 array            jsonend
    static const std::regex jsonParseRegex("\\s*\"([a-z_]*)\"\\s*:\\s*([0-9]*\\.?[0-9]+|\"[\\w\\s\\.\\/]+\")?(\\[([\\S\\s]*)\\])?\\s*([,}])\\s*");

    bool foundLast = false;
    std::string worker(input);
    std::smatch matches;
    std::map<std::string, listedValueVariant> properties;
    while (std::regex_search(worker, matches, jsonParseRegex))
    {
        if (foundLast)
        {
            throw JSON::ParseException("Data found after closing tag");
        }

        if (matches.size() == 6)
        {
            if (matches[5].str() == "}")
            {
                foundLast = true;
            }

            if (matches[2].str().size() > 0)
            {
                properties[matches[1]] = variant_cast(simpleTypeParse(matches[2]));
            }
            else
            {
                properties[matches[1]] = arrayParse(matches[4]);
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

JSON::valueVariant JSON::simpleTypeParse(const std::string &match)
{
    if (match.at(0) == '"')
    {
        std::string value = match;
        value.erase(value.begin());
        value.erase(value.end() - 1);
        return value;
    }

    if (match.find_first_of('.') != std::string::npos)
    {
        return stod(match);
    }

    return stoi(match);
}

JSON::list JSON::arrayParse(const std::string &match)
{
    //                                          int         double      string            comma
    static const std::regex jsonArrayRegex("\\s*([0-9]*\\.?[0-9]+|\"[\\w\\s\\.\\/]+\")\\s*(,)?\\s*");

    std::string worker(match);
    std::smatch matches;
    bool hadComma = true;
    std::list<valueVariant> l;

    while (hadComma && std::regex_search(worker, matches, jsonArrayRegex))
    {
        if (matches.prefix().str().find_first_of(',') != std::string::npos)
        {
            throw ParseException("Wrong format: comma found before value");
        }

        if (matches.size() == 3)
        {
            l.emplace_back(simpleTypeParse(matches[1]));

            hadComma = matches[2] == ",";
        }
        worker = matches.suffix();
    }

    if (worker.length() > 0 || hadComma)
    {
        throw JSON::ParseException("Wrong format: Invalid array format");
    }

    return l;
}