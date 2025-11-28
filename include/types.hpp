#ifndef TYPES_HPP
#define TYPES_HPP

#include <vector>
#include <cstdint>

struct encryptedFile {
    std::vector<std::uint8_t> salt;
    std::vector<std::uint8_t> iv;
    std::vector<std::uint8_t> tag;
    std::vector<std::uint8_t> ciphertext;

    encryptedFile() noexcept;
    ~encryptedFile() noexcept = default;

    encryptedFile(encryptedFile&& other) noexcept;
    encryptedFile& operator=(encryptedFile&& other) noexcept;

    encryptedFile(const encryptedFile&) = delete;
    encryptedFile& operator=(const encryptedFile&) = delete; 
};

#endif // !TYPES_HPP