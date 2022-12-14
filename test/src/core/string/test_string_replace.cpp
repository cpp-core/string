// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/string/replace.h"

using namespace core::str;

TEST(StringReplaceMultiple, Empty)
{
    {
	auto r = core::str::replace_all("", "abc", "def");
	EXPECT_EQ(r, "");
    }
    {
	auto r = core::str::replace_all("", "abc", "def", "ghi", "jkl");
	EXPECT_EQ(r, "");
    }
}

TEST(StringReplaceMultiple, NoMatch)
{
    {
	auto r = core::str::replace_all("abcxydef", "xyz", "abc");
	EXPECT_EQ(r, "abcxydef");
    }
    {
	auto r = core::str::replace_all("abcxydef", "xyz", "abc", "ghi", "jkl");
	EXPECT_EQ(r, "abcxydef");
    }
}

TEST(StringReplaceMultiple, Match)
{
    {
	auto r = core::str::replace_all("abcdefabcdef", "bcd", "xyz");
	EXPECT_EQ(r, "axyzefaxyzef");
    }
    {
	auto r = core::str::replace_all("abcdefabcdef", "bcd", "xyz", "efa", "????");
	EXPECT_EQ(r, "axyz????xyzef");
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
