#pragma once

#include <map>
#include <string>
#include <any>

/**
 * @class JSON
 * 
 * @brief JSON parser class, parse to map with casts
 * 
 * The class includes functions to parse a string / file / stream to a map.
 * The returned map always has `std::string` keys and `std::any` values.
 * It supports auto parsing to `int` and `float` types (after it, it is castable).
 * 
 * @author +++ Team
 * 
 * @version 1.0
 * 
 * @date 2020-10-25
 * 
 * Created on: 2020-10-25
 */
class JSON
{
    std::map<std::string, std::any> data;

public:
    /** Parse the given string input
     * 
     * The function accepts a JSON string as parameter 
     * 
     * @param input JSON input string
     * @return a class initialized with the parsed data structure
     * @throws invalid_argument is thrown if the number to be parsed format not correct
     * @throws out_of_range is thrown if the number to be parsed too large
     * @relatealso parseFromString
     */
    static JSON parseFromString(const std::string &input);

    /** Parse the given file
     * 
     * The function accepts a filename which will be read from the filesystem. 
     * 
     * @param filename a file on the local filesystem
     * @return a class initialized with the parsed data structure
     * @throws JsonFileReadError is thrown is the given file does not exists or cannot be read
     * @throws invalid_argument is thrown if the number to be parsed format not correct
     * @throws out_of_range is thrown if the number to be parsed too large
     * @relatealso parseFromString
     */
    static JSON parseFromFile(const std::string &filename);

    /** Parse the given stream to map
     * 
     * The function accepts a stream, which will be read into a string, and will be
     * parsed in that form 
     * 
     * @param stream `istream` which will be read to string
     * @return a class initialized with the parsed data structure
     * @throws invalid_argument is thrown if the number to be parsed format not correct
     * @throws out_of_range is thrown if the number to be parsed too large
     * @relatealso parseFromString
     */
    static JSON parseFromStream(std::istream &stream);

    /**
     * Check if the given key exists the data map
     * @return either 0 (not present) or 1 (present)
     */
    unsigned int count(const std::string &key)
    {
        return data.count(key);
    }

    /**
     * Get a key's value from the map casted to the given format
     * std::string, int and float can be casted, according to the type in the file
     * @return the casted value
     * @throws bad_cast if thrown if the given key is not present or is stored in another type
     */
    template <typename T>
    T get(const std::string &key)
    {
        return std::any_cast<T>(data[key]);
    }

    /** 
     * @class ParseException
     * 
     * @brief Parse Error exception to be called on invalid input
    */
    class ParseException : virtual public std::runtime_error
    {
    public:
        /** 
         * Constructor which takes a description as parameter.
         * @param description Description of parsing error.
        */
        explicit ParseException(const std::string &description) : std::runtime_error("Parsing error occured: " + description) {}
    };

private:
    JSON(std::map<std::string, std::any> data) : data(data){};

    /** Handle the real parsing
     * 
     * The function uses regex to loop through the file until key: value pairs can
     * be found. If the value is between " " it will be string, else
     * - if it is only numbers with a single dot, then it is parsed as `float`
     * - if it is only numbers, it will be parsed as `int`
     * 
     * @param input json input string
     * @return a class initialized with the parsed data structure
     * @throws invalid_argument is thrown if the number to be parsed format not correct
     * @throws out_of_range is thrown if the number to be parsed too large
     */
    static JSON parse(const std::string &input);
};