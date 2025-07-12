#include <gtest/gtest.h>

#include "pbkdf2.hpp"

class Pbkdf2Fixture : public ::testing::Test {
protected:
    static constexpr std::size_t SaltLen = 16;
    static constexpr std::size_t KeyLen  = 32;
    static constexpr std::size_t Iters   = 200'00;

    const std::string pass = "password";
    const std::vector<std::uint8_t> saltA = std::vector<std::uint8_t>(SaltLen, 0xAB);
    const std::vector<std::uint8_t> salt1 = std::vector<std::uint8_t>(SaltLen, 0x01);
    const std::vector<std::uint8_t> salt2 = std::vector<std::uint8_t>(SaltLen, 0x02);
    const std::vector<std::uint8_t> badSalt = std::vector<std::uint8_t>(8, 0x01);

    pbkdf2 kdf{SaltLen, KeyLen, Iters};
};

TEST_F(Pbkdf2Fixture, DeriveKeyHasCorrectSize) {
    const auto key = kdf.deriveKey(pass, salt1);
    EXPECT_EQ(key.size(), KeyLen);
}

TEST_F(Pbkdf2Fixture, SameInputGivesSameKey) {
    const auto key1 = kdf.deriveKey(pass, saltA);
    const auto key2 = kdf.deriveKey(pass, saltA);
    EXPECT_EQ(key1, key2);
}

TEST_F(Pbkdf2Fixture, DifferentSaltGivesDifferentKey) {
    const auto key1 = kdf.deriveKey(pass, salt1);
    const auto key2 = kdf.deriveKey(pass, salt2);
    EXPECT_NE(key1, key2);
}

TEST_F(Pbkdf2Fixture, ThrowsOnWrongSaltSize) {
    EXPECT_THROW((void)kdf.deriveKey(pass, badSalt), std::runtime_error);
}

TEST_F(Pbkdf2Fixture, AccessorsReturnConfiguredSizes) {
    EXPECT_EQ(kdf.saltSize(), SaltLen);
    EXPECT_EQ(kdf.keySize(), KeyLen);
}
