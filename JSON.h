#pragma once

#include <map>
#include <string>
#include <variant>
#include <list>
#include <regex>

/**
 * @class JSON
 * 
 * @brief JSON parser class, parse to map with casts
 * 
 * The class includes functions to parse a string / file / stream to a map.
 * The returned map always has `std::string` keys and `std::variant` values.
 * It supports auto parsing to `int` and `double` types (`get` can be used to get the value).
 * 
 * @author +++ Team
 * 
 * @version 1.1
 * 
 * @date 2020-11-12
 * 
 * Created on: 2020-10-25
 */
class JSON
{
public:
    typedef std::variant<int, double, std::string> valueVariant;
    typedef std::list<valueVariant> list;
    typedef std::variant<int, double, std::string, list> listedValueVariant;

private:
    std::map<std::string, listedValueVariant> data;

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
     * @throws JSON::ParseException is thrown if the given file does not exists or cannot be read
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
     * std::string, int and double can be casted, according to the type in the file
     * @return the casted value
     * @throws bad_variant_access is thrown if the given key is not present or is stored in another type
     */
    template <typename T>
    T get(const std::string &key)
    {
        return std::get<T>(data[key]);
    }

    /**
     * If the given element is exists then gets it.
     * If does not exists any element with the given key, then it will give back the given default element.
     * @param key Map element's key.
     * @param elseEl Other default element
     * @return The searched element or a default element.
     */
    template <typename T>
    T getOrElse(const std::string &key, T elseEl)
    {
        return keyExists(key) ? get<T>(key) : elseEl;
    }

    /**
     * Checks the given key existance inside the map.
     * @param key Map element key.
     * @return Existance of the key.
     */
    bool keyExists(const std::string &key)
    {
        return data.find(key) != data.end();
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
    explicit JSON(const std::map<std::string, listedValueVariant> &data) : data(data){};

    /** Handle the real parsing
     * 
     * The function uses regex to loop through the file until key: value pairs can be found.
     * 
     * @param input json input string
     * @return a class initialized with the parsed data structure
     * @throws JSON::ParseException if data found after the closing tag or missing a key / value or the array format is invalid
     * @throws invalid_argument is thrown if the number to be parsed format not correct
     * @throws out_of_range is thrown if the number to be parsed too large
     * @relatealso simpleTypeParse
     * @relatealso arrayParse
     */
    static JSON parse(const std::string &input);

    /** Parse the match into a string, int or double
     * 
     *  Will be parsed as:
     *  - string: quouted string ("apple")
     *  - double: contains a dot
     *  - int: else 
     * 
     * @param match a string to be parsed
     * @throws invalid_argument is thrown if the number to be parsed format not correct
     * @throws out_of_range is thrown if the number to be parsed too large
     */
    static valueVariant simpleTypeParse(const std::string &match);

    /** Creates an std::list of the match based on regex pattern
     * 
     *  Uses simpleTypeParse to parse the values
     * 
     * @param match a string containing values comma separated, without []
     * @throws JSON::ParseException is thrown if the array format is invalid
     * @throws invalid_argument is thrown if the number to be parsed format not correct
     * @throws out_of_range is thrown if the number to be parsed too large
     * @relatealso simpleTypeParse
     */
    static list arrayParse(const std::string &match);

    /** Helper struct for variant casting
     *  used for casting valueVariant to listValueVariant
     */
    template <class... Args>
    struct variant_cast_proxy
    {
        std::variant<Args...> v;

        template <class... ToArgs>
        operator std::variant<ToArgs...>() const
        {
            return std::visit(
                [](auto &&arg) -> std::variant<ToArgs...> { return arg; },
                v);
        }
    };

    /** Helper function for variant casting
     *  used for casting valueVariant to listValueVariant
     */
    template <class... Args>
    static auto variant_cast(const std::variant<Args...> &v) -> variant_cast_proxy<Args...>
    {
        return {v};
    }
};