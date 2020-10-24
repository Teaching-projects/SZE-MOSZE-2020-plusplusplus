#include <stdexcept>

/** JsonParseError exception to be called on invalid input
 */
class JsonParseError : virtual public std::runtime_error
{
public:
    /** Constructor which takes a description as parameter
     */
    explicit JsonParseError(const std::string &description) : std::runtime_error("Parsing error occured: " + description) {}
};
