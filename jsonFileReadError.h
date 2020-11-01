#pragma once

#include <stdexcept>

/** 
 * @class JsonFileReadError
 * 
 * @brief Exception to be called on file read error
 * 
 * @author +++ Team
 */
class JsonFileReadError : virtual public std::runtime_error
{
public:
    /** 
     * Constructor which takes the filename as parameter and will have an error message containing it.
     * @param filename The file's name what is not found or cannot be opened.
     */
    explicit JsonFileReadError(const std::string &filename) : std::runtime_error("File not found or cannot be opened: " + filename) {}
};
