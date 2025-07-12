#include <gtest/gtest.h>

#include "osRandomProvider.hpp"

class OsRandomProviderFixture : public ::testing::Test {
protected:
    static constexpr std::size_t len = 32;
    osRandomProvider rng;
};

TEST_F(OsRandomProviderFixture, ReturnsCorrectLength) {
    const auto bytes = rng.getBytes(len);
    EXPECT_EQ(bytes.size(), len);
}

TEST_F(OsRandomProviderFixture, TwoCallsAreNotEqualMostOfTime) {
    const auto a = rng.getBytes(len);
    const auto b = rng.getBytes(len);

    EXPECT_NE(a, b);
}
