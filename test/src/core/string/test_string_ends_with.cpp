// Copyright (C) 2019 by Mark Melton
//

#include <gtest/gtest.h>
#include "string/ends_with.h"

using namespace core;

TEST(EndsWith, EmptyStringAndSuffix)
{
    auto s = "";
    auto v = "";
    EXPECT_EQ(ends_with(s, v), false); 
}


TEST(EndsWith, EmptyString)
{
    auto s = "";
    auto v = "abc";
    EXPECT_EQ(ends_with(s, v), false); 
    EXPECT_EQ(ends_with(s, v[0]), false); 
}


TEST(EndsWith, EmptySuffix)
{
    auto s = "abcdef";
    auto v = "";
    EXPECT_EQ(ends_with(s, v), false); 
}


TEST(EndsWith, MatchingSuffix)
{
    auto s = "abcdef";
    auto v = "def";
    EXPECT_EQ(ends_with(s, v), true); 
    EXPECT_EQ(ends_with(s, v[2]), true); 
}


TEST(EndsWith, NonMatchingSuffix)
{
    auto s = "abcdef";
    auto v = "bcd";
    EXPECT_EQ(ends_with(s, v), false); 
    EXPECT_EQ(ends_with(s, v[2]), false); 
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
