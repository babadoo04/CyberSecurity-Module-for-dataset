#include "pch.hpp"
#include "osRandomProvider.hpp"

std::vector<std::uint8_t> osRandomProvider::getBytes(std::size_t n) const {
    CryptoPP::AutoSeededRandomPool rng;
    std::vector<std::uint8_t> out(n);
    rng.GenerateBlock(out.data(), out.size());
    
    return out;
}