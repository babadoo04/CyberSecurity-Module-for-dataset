#ifndef IKEY_DERIVER_HPP
#define IKEY_DERIVER_HPP

#include <vector>
#include <string>

#include <cstdint>
#include <cstddef>

class keyDeriverI {
public:
    virtual ~keyDeriverI() noexcept = default;
    
    virtual std::vector<std::uint8_t> deriveKey(const std::string& passwd, const std::vector<std::uint8_t>& salt) const = 0; 

    virtual std::size_t saltSize() const = 0;
    virtual std::size_t keySize() const = 0;
};

#endif // !IKEY_DERIVER_HPP