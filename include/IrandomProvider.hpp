#ifndef IRANDOM_PROVIDER_HPP
#define IRANDOM_PROVIDER_HPP

#include <vector>

#include <cstdint>
#include <cstddef>

class randomProviderI {
public:
    virtual ~randomProviderI() noexcept = default;

    virtual std::vector<std::uint8_t> getBytes(std::size_t n) const = 0; 
};

#endif // !IRANDOM_PROVIDER_HPP