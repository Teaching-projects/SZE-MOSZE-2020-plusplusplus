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
public:
    /** Parse the given string input
     * 
     * The function accepts a JSON string as parameter 
     * 
     * @param input JSON input string
     * @return A map with string keys and values in `std::any` type. `int` and `float`
     * is parsed and can be casted
     * @throws invalid_argument is thrown if the number to be parsed format not correct
     * @throws out_of_range is thrown if the number to be parsed too large
     * @relatealso parseFromString
     */
    static std::map<std::string, std::any> parseFromString(const std::string &input);

    /** Parse the given file
     * 
     * The function accepts a filename which will be read from the filesystem. 
     * 
     * @param filename a file on the local filesystem
     * @return A map with string keys and values in `std::any` type. `int` and `float`
     * is parsed and can be casted
     * @throws JsonFileReadError is thrown is the given file does not exists or cannot be read
     * @throws invalid_argument is thrown if the number to be parsed format not correct
     * @throws out_of_range is thrown if the number to be parsed too large
     * @relatealso parseFromString
     */
    static std::map<std::string, std::any> parseFromFile(const std::string &filename);

    /** Parse the given stream to map
     * 
     * The function accepts a stream, which will be read into a string, and will be
     * parsed in that form 
     * 
     * @param stream `istream` which will be read to string
     * @return A map with string keys and values in `std::any` type. `int` and `float`
     * is parsed and can be casted
     * @throws invalid_argument is thrown if the number to be parsed format not correct
     * @throws out_of_range is thrown if the number to be parsed too large
     * @relatealso parseFromString
     */
    static std::map<std::string, std::any> parseFromStream(std::istream &stream);

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
    /** Handle the real parsing
     * 
     * The function uses regex to loop through the file until key: value pairs can
     * be found. If the value is between " " it will be string, else
     * - if it is only numbers with a single dot, then it is parsed as `float`
     * - if it is only numbers, it will be parsed as `int`
     * 
     * @param input json input string
     * @return A map with string keys and values in `std::any` type. `int` and `float`
     * is parsed and can be casted
     * @throws invalid_argument is thrown if the number to be parsed format not correct
     * @throws out_of_range is thrown if the number to be parsed too large
     */
    static std::map<std::string, std::any> parse(const std::string &input);
};