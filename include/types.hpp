#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <cstdint>

struct encryptedFile {
    std::vector<std::uint8_t> salt;
    std::vector<std::uint8_t> iv;
    std::vector<std::uint8_t> tag;
    std::vector<std::uint8_t> ciphertext;
};

#endif // !TYPES_HPP