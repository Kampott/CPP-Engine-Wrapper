#include "Subject.hpp"
#include <cctype>
#include <sstream>
#include <algorithm>

/**
 * Replace words in the text.
 */
std::string Subject::replace_words(const std::unordered_map<std::string, std::any>& args) {
    try {
        std::string text = std::any_cast<std::string>(args.at("text"));
        std::string from = std::any_cast<std::string>(args.at("from"));
        std::string to = std::any_cast<std::string>(args.at("to"));

        size_t pos = 0;
        while ((pos = text.find(from, pos)) != std::string::npos) {
            text.replace(pos, from.length(), to);
            pos += to.length();
        }
        return text;
    }
    catch (const std::exception& e) {
        throw std::runtime_error("replace_words: " + std::string(e.what()));
    }
}

/**
 * Find a phrase in the text.
 */
std::string Subject::find_phrase(const std::unordered_map<std::string, std::any>& args) {
    try {
        std::string text = std::any_cast<std::string>(args.at("text"));
        std::string phrase = std::any_cast<std::string>(args.at("phrase"));
        return text.find(phrase) != std::string::npos ? "Found" : "Not Found";
    }
    catch (const std::exception& e) {
        throw std::runtime_error("find_phrase: " + std::string(e.what()));
    }
}

/**
 * Capitalize the first letter of each word in the text.
 */
std::string Subject::capitalize_words(const std::unordered_map<std::string, std::any>& args) {
    try {
        std::string text = std::any_cast<std::string>(args.at("text"));
        bool capitalize = true;
        for (char& c : text) {
            if (std::isspace(c)) {
                capitalize = true;
            }
            else if (capitalize) {
                c = std::toupper(c);
                capitalize = false;
            }
        }
        return text;
    }
    catch (const std::exception& e) {
        throw std::runtime_error("capitalize_words: " + std::string(e.what()));
    }
}

/**
 * Capitalize the first letter of each sentence in the text.
 */
std::string Subject::capitalize_sentences(const std::unordered_map<std::string, std::any>& args) {
    try {
        std::string text = std::any_cast<std::string>(args.at("text"));
        bool capitalize = true;
        for (char& c : text) {
            if (capitalize && std::isalpha(c)) {
                c = std::toupper(c);
                capitalize = false;
            }
            if (c == '.' || c == '!' || c == '?') {
                capitalize = true;
            }
        }
        return text;
    }
    catch (const std::exception& e) {
        throw std::runtime_error("capitalize_sentences: " + std::string(e.what()));
    }
}

/**
 * Number sentences in the text.
 */
std::string Subject::number_sentences(const std::unordered_map<std::string, std::any>& args) {
    try {
        std::string text = std::any_cast<std::string>(args.at("text"));
        std::stringstream result;

        size_t start = 0;
        size_t end = 0;
        int counter = 1;

        while ((end = text.find_first_of(".!?", start)) != std::string::npos) {
            result << counter++ << ". " << text.substr(start, end - start + 1) << "\n";
            start = end + 1;
        }
        if (start < text.size()) {
            result << counter++ << ". " << text.substr(start) << "\n";
        }
        return result.str();
    }
    catch (const std::exception& e) {
        throw std::runtime_error("number_sentences: " + std::string(e.what()));
    }
}
