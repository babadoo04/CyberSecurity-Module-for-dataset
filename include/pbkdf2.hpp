#ifndef PBKDF2_HPP
#define PBKDF2_HPP

#include "IkeyDeriver.hpp"

class pbkdf2 final : public keyDeriverI {
public:
    pbkdf2(std::size_t saltLen, std::size_t keyLen, std::size_t iterations) noexcept;
    ~pbkdf2() noexcept = default;
    
    std::vector<std::uint8_t> deriveKey(const std::string& passwd, const std::vector<std::uint8_t>& salt) const override final; 
    constexpr std::size_t saltSize() const override final;
    constexpr std::size_t keySize() const override final;
private:
    std::size_t saltLen;
    std::size_t keyLen;
    std::size_t iterations;
};

#endif // !PBKDF2_HPP