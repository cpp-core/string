// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/string/compare.h"

using namespace core::str;

TEST(StringCompare, Empty)
{
    EXPECT_EQ(core::str::iequals("", ""), true);
    EXPECT_EQ(core::str::iequals("", "abc"), false);
    EXPECT_EQ(core::str::iequals("abc", ""), false);
}

TEST(StringCompare, DifferentSize)
{
    EXPECT_EQ(core::str::iequals("abc", "abcd"), false);
    EXPECT_EQ(core::str::iequals("ABC", "abcd"), false);
    EXPECT_EQ(core::str::iequals("abcd", "abc"), false);
    EXPECT_EQ(core::str::iequals("ABCD", "abc"), false);
}

TEST(StringCompare, SameCase)
{
    EXPECT_EQ(core::str::iequals("abc", "abc"), true);
    EXPECT_EQ(core::str::iequals("ABC", "ABC"), true);
    EXPECT_EQ(core::str::iequals("abc", "def"), false);
    EXPECT_EQ(core::str::iequals("DEF", "ABC"), false);
}

TEST(StringCompare, DifferntCase)
{
    EXPECT_EQ(core::str::iequals("abc", "ABC"), true);
    EXPECT_EQ(core::str::iequals("ABC", "abc"), true);
    EXPECT_EQ(core::str::iequals("abc", "DEF"), false);
    EXPECT_EQ(core::str::iequals("DEF", "abc"), false);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
