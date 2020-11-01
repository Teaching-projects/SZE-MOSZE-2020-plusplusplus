#pragma once

#include <stdexcept>

/** 
 * @class JsonParseError 
 * 
 * @brief Exception to be called on invalid input
 * 
 * @author +++ Team
 */
class JsonParseError : virtual public std::runtime_error
{
public:
    /** 
     * Constructor which takes a description as parameter
     * @param description Description of the error behaviour.
     */
    explicit JsonParseError(const std::string &description) : std::runtime_error("Parsing error occured: " + description) {}
};
