#ifndef TYPES_HPP
#define TYPES_HPP

#include "pch.hpp"

namespace cryptTools {

    struct encryptedFile {
        std::vector<std::uint8_t> salt;
        std::vector<uint8_t> iv;
        std::vector<uint8_t> tag;
        std::vector<uint8_t> ciphertext;

        encryptedFile();
        ~encryptedFile() = default;

        encryptedFile(encryptedFile&& other) noexcept;
        encryptedFile& operator=(encryptedFile&& other) noexcept;

        encryptedFile(const encryptedFile&) = delete;
        encryptedFile& operator=(const encryptedFile&) = delete; 
    };
}

#endif // !TYPES_HPP