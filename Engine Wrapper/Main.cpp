#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <any>
#include "Subject.hpp"
#include "Wrapper.hpp"
#include "Engine.hpp"

/**
 * @brief Utility function to write text to a file.
 * @param filename Name of the file.
 * @param text Content to write to the file.
 */
void write_to_file(const std::string& filename, const std::string& text) {
    std::ofstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to create file: " + filename);
    }
    file << text;
    file.close();
}

/**
 * @brief Utility function to read text from a file.
 * @param filename Name of the file.
 * @return Content of the file as a string.
 */
std::string read_from_file(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        throw std::runtime_error("Failed to open file: " + filename);
    }
    std::ostringstream ss;
    ss << file.rdbuf();
    file.close();
    return ss.str();
}

/**
 * @brief Run unit tests for all Subject methods.
 */
void run_tests() {
    // Test file
    const std::string filename = "test_text.txt";
    const std::string test_text = "hello world. how are you?";

    try {
        // Prepare file
        write_to_file(filename, test_text);

        // Create Subject and Wrappers
        Subject subj;
        Wrapper replace_wrapper(&subj, [&](const auto& args) { return subj.replace_words(args); });
        Wrapper find_wrapper(&subj, [&](const auto& args) { return subj.find_phrase(args); });
        Wrapper capitalize_words_wrapper(&subj, [&](const auto& args) { return subj.capitalize_words(args); });
        Wrapper capitalize_sentences_wrapper(&subj, [&](const auto& args) { return subj.capitalize_sentences(args); });
        Wrapper number_sentences_wrapper(&subj, [&](const auto& args) { return subj.number_sentences(args); });

        // Register commands in the Engine
        Engine engine;
        engine.register_command(&replace_wrapper, "replace_words");
        engine.register_command(&find_wrapper, "find_phrase");
        engine.register_command(&capitalize_words_wrapper, "capitalize_words");
        engine.register_command(&capitalize_sentences_wrapper, "capitalize_sentences");
        engine.register_command(&number_sentences_wrapper, "number_sentences");

        // Test cases
        std::unordered_map<std::string, std::any> args;

        // Replace words
        args = { {"text", read_from_file(filename)}, {"from", std::string("world")}, {"to", std::string("universe")} };
        std::cout << "Test 1 (replace_words): " << engine.execute("replace_words", args) << "\n";

        // Find phrase
        args = { {"text", read_from_file(filename)}, {"phrase", std::string("world")} };
        std::cout << "Test 2 (find_phrase): " << engine.execute("find_phrase", args) << "\n";

        // Capitalize words
        args = { {"text", read_from_file(filename)} };
        std::cout << "Test 3 (capitalize_words): " << engine.execute("capitalize_words", args) << "\n";

        // Capitalize sentences
        args = { {"text", read_from_file(filename)} };
        std::cout << "Test 4 (capitalize_sentences): " << engine.execute("capitalize_sentences", args) << "\n";

        // Number sentences
        args = { {"text", read_from_file(filename)} };
        std::cout << "Test 5 (number_sentences): " << engine.execute("number_sentences", args) << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error during testing: " << e.what() << "\n";
    }
    // Cleanup
    std::remove(filename.c_str());
}

int main() {
    run_tests();
    return 0;
}
