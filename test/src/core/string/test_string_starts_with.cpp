// Copyright (C) 2019 by Mark Melton
//

#include <gtest/gtest.h>
#include "string/starts_with.h"

using namespace core;

TEST(StartsWith, EmptyStringAndPrefix)
{
    auto s = "";
    auto v = "";
    EXPECT_EQ(starts_with(s, v), false); 
}


TEST(StartsWith, EmptyString)
{
    auto s = "";
    auto v = "abc";
    EXPECT_EQ(starts_with(s, v), false); 
    EXPECT_EQ(starts_with(s, v[0]), false); 
}


TEST(StartsWith, EmptyPrefix)
{
    auto s = "abcdef";
    auto v = "";
    EXPECT_EQ(starts_with(s, v), false); 
}


TEST(StartsWith, MatchingPrefix)
{
    auto s = "abcdef";
    auto v = "abc";
    EXPECT_EQ(starts_with(s, v), true); 
    EXPECT_EQ(starts_with(s, v[0]), true); 
}


TEST(StartsWith, NonMatchingPrefix)
{
    auto s = "abcdef";
    auto v = "bcd";
    EXPECT_EQ(starts_with(s, v), false); 
    EXPECT_EQ(starts_with(s, v[0]), false); 
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
