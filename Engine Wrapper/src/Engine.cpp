#include "Engine.hpp"

/**
 * @brief Registers a command in the Engine.
 * @param wrapper Pointer to the Wrapper object.
 * @param command_name Name of the command to register.
 */
void Engine::register_command(Wrapper* wrapper, const std::string& command_name) {
    if (!wrapper) {
        throw std::invalid_argument("Wrapper pointer cannot be null.");
    }
    commands_[command_name] = wrapper;
}

/**
 * @brief Executes a registered command by name with the provided arguments.
 * @param command_name Name of the command to execute.
 * @param args Arguments to pass to the command.
 * @return Result of the command execution.
 */
std::string Engine::execute(const std::string& command_name, const std::unordered_map<std::string, std::any>& args) {
    if (!commands_.count(command_name)) {
        throw std::runtime_error("Command not found: " + command_name);
    }
    return commands_[command_name]->execute(args);
}
