#include "pch.hpp"

class keyDeriverI {
public:
    virtual ~keyDeriverI() = default;
    
    virtual std::vector<std::uint8_t> deriveKey(const std::string& passwd, const std::vector<std::uint8_t>& salt) const = 0; 

    virtual std::size_t saltSize() const = 0;
    virtual std::size_t keySize()  const = 0;
};