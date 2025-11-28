#ifndef AES256G_CM_CIPHER_HPP
#define AES256G_CM_CIPHER_HPP

#include "IAeadEncryptor.hpp"

class aes256GcmCipher final : public aeadEncryptor {
public:
    ~aes256GcmCipher() noexcept = default;
    encryptedFile encrypt(const std::vector<std::uint8_t>& plaintext, const std::vector<std::uint8_t>& key,
                                  const std::vector<std::uint8_t>& iv) const final override;
    
    std::vector<std::uint8_t> decrypt(const encryptedFile& file, const std::vector<std::uint8_t>& key) const final override;

    std::size_t ivSize()  const final override;
    std::size_t tagSize() const final override;
};

#endif // !AES256G_CM_CIPHER_HPP