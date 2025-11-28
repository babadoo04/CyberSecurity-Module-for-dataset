#ifndef COMMAND_LINE_PARSER_HPP
#define COMMAND_LINE_PARSER_HPP

#include <filesystem>
#include <string>

enum class operation {
    Encrypt,
    Decrypt,
    Verify,
    Unknown
};

struct ClArgs {
    operation op = operation::Unknown;
    std::filesystem::path in;
    std::filesystem::path out;
    std::string password;
};

operation parseOperation(const std::string& s);

ClArgs parseArgs(int argc, char** argv);


#endif // !COMMAND_LINE_PARSER_HPP