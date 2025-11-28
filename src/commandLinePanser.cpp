#include "commandLinePanser.hpp"

operation parseOperation(const std::string &s) {
    if (s == "e" || s == "encrypt") return operation::Encrypt;
    if (s == "d" || s == "decrypt") return operation::Decrypt;
    if (s == "v" || s == "verify")  return operation::Verify;
    return operation::Unknown;
}

ClArgs parseArgs(int argc, char **argv) {
    if (argc < 2) {
            throw std::runtime_error("bad args");
        }

    ClArgs args;
    args.op = parseOperation(argv[1]);

    switch (args.op) {
        case operation::Encrypt:

        case operation::Decrypt:
            if (argc != 5) {
                throw std::runtime_error("bad args");
            }
            args.in = argv[2];
            args.out = argv[3];
            args.password = argv[4];
            break;

        case operation::Verify:
            if (argc != 4) {
                throw std::runtime_error("bad args");
            }
            args.in = argv[2];
            args.password = argv[3];
            break;

        case operation::Unknown:
        default:
            throw std::runtime_error("bad args");
    }

    return args;
}
