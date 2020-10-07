#include <stdexcept>

/** JsonFileReadError exception to be called on file read error
 */
class JsonFileReadError : virtual public std::runtime_error
{
public:
    /** Constructor which takes the filename as parameter
     *  and will have an error message containing it
     */
    explicit JsonFileReadError(const std::string &filename) : std::runtime_error("File not found or cannot be opened: " + filename) {}
};
