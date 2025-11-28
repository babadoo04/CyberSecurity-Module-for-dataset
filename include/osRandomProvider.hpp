#ifndef OS_RANDOM_PROVIDER_HPP
#define OS_RANDOM_PROVIDER_HPP

#include "IrandomProvider.hpp" 

class osRandomProvider final : public randomProviderI {
public:
    ~osRandomProvider() noexcept = default;

    std::vector<std::uint8_t> getBytes(std::size_t n) const final override; 
};

#endif // !OS_RANDOM_PROVIDER_HPP