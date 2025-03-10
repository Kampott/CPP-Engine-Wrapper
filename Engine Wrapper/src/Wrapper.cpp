#include "Wrapper.hpp"

/**
 * Constructor for the Wrapper class.
 */
Wrapper::Wrapper(Subject* subject, const std::function<std::string(const std::unordered_map<std::string, std::any>&)>& func)
    : subject_(subject), function_(func) {
    if (!subject_) {
        throw std::invalid_argument("Subject pointer cannot be null.");
    }
}

/**
 * Executes the wrapped function.
 */
std::string Wrapper::execute(const std::unordered_map<std::string, std::any>& args) {
    return function_(args);
}
