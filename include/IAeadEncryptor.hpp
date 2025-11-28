#include "types.hpp"

class aeadEncryptor {
public:
    virtual ~aeadEncryptor() = default;

    virtual encryptedFile enctypt(const std::vector<std::uint8_t>& plaintext, const std::vector<std::uint8_t>& key,
                                  const std::vector<std::uint8_t>& iv) const = 0;
    
    virtual std::vector<std::uint8_t> decrypt(const encryptedFile& file, const std::vector<std::uint8_t>& key) const = 0;

    virtual std::size_t ivSize()  const = 0;
    virtual std::size_t tagSize() const = 0;
};