// Copyright (C) 2019, 2021 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/string/tolower.h"

using namespace core;

TEST(StringToLower, CStr)
{
    EXPECT_EQ(tolower(""), "");
    EXPECT_EQ(tolower("abc"), "abc");
    EXPECT_EQ(tolower("ABC"), "abc");
}

TEST(StringToLower, String)
{
    EXPECT_EQ(tolower(""s), "");
    EXPECT_EQ(tolower("abc"s), "abc");
    EXPECT_EQ(tolower("ABC"s), "abc");
}

TEST(StringToLower, StringInPlace)
{
    {
	string str;
	tolower(str);
	EXPECT_EQ(str, "");
    }
    {
	string str{"abc"};
	tolower(str);
	EXPECT_EQ(str, "abc");
    }
    {
	string str{"ABC"};
	tolower(str);
	EXPECT_EQ(str, "abc");
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
