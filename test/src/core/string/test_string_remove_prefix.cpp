// Copyright (C) 2019 by Mark Melton
//

#include <gtest/gtest.h>
#include "string/remove_prefix.h"

using namespace core;

TEST(RemovePrefix, Match)
{
    EXPECT_EQ(remove_prefix("abcdef", "abc"), "def");
    EXPECT_EQ(remove_prefix("abcdef", "abcdef"), "");
}

TEST(RemovePrefix, NoMatch)
{
    EXPECT_EQ(remove_prefix("abcdef", "bcd"), "abcdef");
    EXPECT_EQ(remove_prefix("abcdef", "def"), "abcdef");
    EXPECT_EQ(remove_prefix("abcdef", "abcdefg"), "abcdef");
}

TEST(RemovePrefix, EmptyPrefix)
{
    EXPECT_EQ(remove_prefix("abcdef", ""), "abcdef");
}

TEST(RemovePrefix, EmptyStr)
{
    EXPECT_EQ(remove_prefix("", "abc"), "");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
