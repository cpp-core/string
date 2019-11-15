// Copyright (C) 2017, 2018, 2019 by Mark Melton
//

#include <gtest/gtest.h>
#include <fmt/format.h>
#include "string/trim.h"

using namespace core;

TEST(StringTrim, Empty)
{
    auto s = "";
    EXPECT_EQ(ltrim(s), s);
    EXPECT_EQ(rtrim(s), s);
    EXPECT_EQ(trim(s), s);
}

TEST(StringTrim, Start)
{
    auto s = " \f\n\r\t\vfoo bar";
    EXPECT_EQ(ltrim(s), "foo bar");
    EXPECT_EQ(rtrim(s), s);
    EXPECT_EQ(trim(s), "foo bar");
}

TEST(StringTrim, End)
{
    auto s = "foo bar \f\n\r\t\v";
    EXPECT_EQ(ltrim(s), s);
    EXPECT_EQ(rtrim(s), "foo bar");
    EXPECT_EQ(trim(s), "foo bar");
}

TEST(StringTrim, Both)
{
    auto s = "  \f\n\r\t\vfoo bar \f\n\r\t\v";
    EXPECT_EQ(ltrim(s), "foo bar \f\n\r\t\v");
    EXPECT_EQ(rtrim(s), "  \f\n\r\t\vfoo bar");
    EXPECT_EQ(trim(s), "foo bar");
}

TEST(StringTrim, Neither)
{
    auto s = "foo bar";
    EXPECT_EQ(ltrim(s), s);
    EXPECT_EQ(rtrim(s), s);
    EXPECT_EQ(trim(s), s);
}


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
