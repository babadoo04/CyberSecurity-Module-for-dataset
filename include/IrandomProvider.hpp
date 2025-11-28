#include "pch.hpp"

class randomProviderI {
public:
    virtual ~randomProviderI() = default;

    virtual std::vector<std::uint8_t> getBytes(std::size_t n) const = 0; 
};