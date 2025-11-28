#include "pch.hpp"
#include "pbkdf2.hpp"

pbkdf2::pbkdf2(std::size_t saltLen, std::size_t keyLen, std::size_t iterations) noexcept : saltLen{saltLen}, keyLen{keyLen}, iterations{iterations} {
}

std::vector<std::uint8_t> pbkdf2::deriveKey(const std::string &passwd, const std::vector<std::uint8_t> &salt) const {
    if (salt.size() != saltLen) {
        throw std::runtime_error("PBKDF2: invalid salt length");
    }
    std::vector<CryptoPP::byte> passBytes(passwd.begin(), passwd.end());
    std::vector<std::uint8_t> key(keyLen);

    CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA256> pbkdf;
    pbkdf.DeriveKey(
        key.data(), key.size(), 0,
        passBytes.data(), passBytes.size(),
        salt.data(), salt.size(),
        iterations);

    return key;
}

constexpr std::size_t pbkdf2::saltSize() const {
    return saltLen;
}

constexpr std::size_t pbkdf2::keySize() const {
    return keyLen;
}
