// Copyright (C) 2019 by Mark Melton
//

#include <gtest/gtest.h>
#include "string/compare.h"

using namespace core;

TEST(StringCompare, Empty)
{
    EXPECT_EQ(core::iequals("", ""), true);
    EXPECT_EQ(core::iequals("", "abc"), false);
    EXPECT_EQ(core::iequals("abc", ""), false);
}

TEST(StringCompare, DifferentSize)
{
    EXPECT_EQ(core::iequals("abc", "abcd"), false);
    EXPECT_EQ(core::iequals("ABC", "abcd"), false);
    EXPECT_EQ(core::iequals("abcd", "abc"), false);
    EXPECT_EQ(core::iequals("ABCD", "abc"), false);
}

TEST(StringCompare, SameCase)
{
    EXPECT_EQ(core::iequals("abc", "abc"), true);
    EXPECT_EQ(core::iequals("ABC", "ABC"), true);
    EXPECT_EQ(core::iequals("abc", "def"), false);
    EXPECT_EQ(core::iequals("DEF", "ABC"), false);
}

TEST(StringCompare, DifferntCase)
{
    EXPECT_EQ(core::iequals("abc", "ABC"), true);
    EXPECT_EQ(core::iequals("ABC", "abc"), true);
    EXPECT_EQ(core::iequals("abc", "DEF"), false);
    EXPECT_EQ(core::iequals("DEF", "abc"), false);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
