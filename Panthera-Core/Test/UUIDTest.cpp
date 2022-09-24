#include <gtest/gtest.h>

#include "Panthera/Core/UUID.hpp"

using namespace Panthera;

TEST(UUIDTest, UUIDTest)
{
    UUID uuid;
    UUID uuid2;
    ASSERT_TRUE(uuid != uuid2);
}

TEST(UUIDTest, UUIDTest2)
{
    UUID uuid;
    UUID uuid2 = uuid;
    ASSERT_TRUE(uuid == uuid2);
}

TEST(UUIDTest, UUIDTest3)
{
    String uuid = "1234567890";
    UUID uuid2 = uuid;
    ASSERT_TRUE(uuid2 == "1234567890");
}

TEST(UUIDTest, UUIDTest4)
{
    uint64_t uuid = 1234567890;
    UUID uuid2 = uuid;
    ASSERT_TRUE(uuid2 == (uint64_t)1234567890);
}

TEST(UUIDTest, UUIDTest5)
{
    uint32_t upper = 1234567890;
    uint32_t lower = 1234567890;
    UUID uuid2 = UUID(upper, lower);
    ASSERT_TRUE(uuid2 == UUID(upper, lower));
}

TEST(UUIDTest, UUIDTest6)
{
    uint16_t a = 1234;
    uint16_t b = 5678;
    uint16_t c = 9012;
    uint16_t d = 3456;
    UUID uuid2 = UUID(a, b, c, d);
    ASSERT_TRUE(uuid2 == UUID(a, b, c, d));
}

TEST(UUIDTest, UUIDTest7)
{
    uint64_t uuid = 1234567890;
    UUID uuid2 = uuid;
    ASSERT_TRUE(uuid2 == "1234567890");
}