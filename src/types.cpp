#include <utility>

#include "types.hpp"

encryptedFile::encryptedFile() noexcept : salt(16), iv(12), tag(16), ciphertext() {
}

encryptedFile::encryptedFile(encryptedFile &&other) noexcept : salt{std::move(other.salt)}, iv{std::move(other.iv)},
    tag{std::move(other.tag)}, ciphertext{std::move(other.ciphertext)} {
}

encryptedFile& encryptedFile::operator=(encryptedFile &&other) noexcept {
    if (this != &other) {
        salt = std::move(other.salt);
        iv  = std::move(other.iv);
        tag  = std::move(other.tag);
        ciphertext = std::move(other.ciphertext);
    }

    return *this;
}
