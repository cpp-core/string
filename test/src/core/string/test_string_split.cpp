// Copyright (C) 2017, 2018, 2019, 2020, 2021 by Mark Melton
//

#include <gtest/gtest.h>
#include <fmt/format.h>
#include "common.h"
#include "core/string/split.h"

using namespace core;

TEST(StringSplit, Empty)
{
    auto s = "";
    EXPECT_EQ(split(s, ":"), string_views{});

    string_views fields;
    EXPECT_EQ(split(s, ":", fields), 0u);
}

TEST(StringSplit, Delim)
{
    auto s = ":";
    EXPECT_EQ(split(s, ":"), (string_views{ "", "" }));

    string_views fields;
    EXPECT_EQ(split(s, ":", fields), 2u);
    EXPECT_EQ(fields[0], "");
    EXPECT_EQ(fields[1], "");
}

TEST(StringSplit, String)
{
    auto s = "foo";
    EXPECT_EQ(split(s, ":"), string_views{ "foo" });

    string_views fields;
    EXPECT_EQ(split(s, ":", fields), 1u);
    EXPECT_EQ(fields[0], "foo");
}

TEST(StringSplit, StringDelim)
{
    auto s = "foo:";
    EXPECT_EQ(split(s, ":"), (string_views{ "foo", "" }));

    string_views fields;
    EXPECT_EQ(split(s, ":", fields), 2u);
    EXPECT_EQ(fields[0], "foo");
    EXPECT_EQ(fields[1], "");
}

TEST(StringSplit, DelimString)
{
    auto s = ":foo";
    EXPECT_EQ(split(s, ":"), (string_views{ "", "foo" }));

    string_views fields;
    EXPECT_EQ(split(s, ":", fields), 2u);
    EXPECT_EQ(fields[0], "");
    EXPECT_EQ(fields[1], "foo");
}

TEST(StringSplit, StringDelimString)
{
    auto s = "foo:bar";
    EXPECT_EQ(split(s, ":"), (string_views{ "foo", "bar" }));

    string_views fields;
    EXPECT_EQ(split(s, ":", fields), 2u);
    EXPECT_EQ(fields[0], "foo");
    EXPECT_EQ(fields[1], "bar");
}

TEST(StringSplit, StringDelimStringDelim)
{
    auto s = "foo:bar:";
    EXPECT_EQ(split(s, ":"), (string_views{ "foo", "bar", "" }));

    string_views fields;
    EXPECT_EQ(split(s, ":", fields), 3u);
    EXPECT_EQ(fields[0], "foo");
    EXPECT_EQ(fields[1], "bar");
    EXPECT_EQ(fields[2], "");
}

TEST(StringSplit, DelimStringDelimStringDelim)
{
    auto s = ":foo:bar:";
    EXPECT_EQ(split(s, ":"), (string_views{ "", "foo", "bar", "" }));

    string_views fields;
    EXPECT_EQ(split(s, ":", fields), 4u);
    EXPECT_EQ(fields[0], "");
    EXPECT_EQ(fields[1], "foo");
    EXPECT_EQ(fields[2], "bar");
    EXPECT_EQ(fields[3], "");
}

TEST(StringSplit, StringDelimStringDelimString)
{
    auto s = "foo:bar:zoo";
    EXPECT_EQ(split(s, ":"), (string_views{ "foo", "bar", "zoo" }));

    string_views fields;
    EXPECT_EQ(split(s, ":", fields), 3u);
    EXPECT_EQ(fields[0], "foo");
    EXPECT_EQ(fields[1], "bar");
    EXPECT_EQ(fields[2], "zoo");
}

TEST(StringSplit, StringSplitFirstLastEmpty)
{
    auto s = "";
    EXPECT_EQ(split_first(s, ":"), string_view{});
    EXPECT_EQ(split_last(s, ":"), string_view{});
}

TEST(StringSplit, StringSplitFirstLastDelim)
{
    auto s = ":";
    EXPECT_EQ(split_first(s, ":"), string_view{});
    EXPECT_EQ(split_last(s, ":"), string_view{});
}

TEST(StringSplit, StringSplitFirstLastString)
{
    auto s = "foo";
    EXPECT_EQ(split_first(s, ":"), string_view{"foo"});
    EXPECT_EQ(split_last(s, ":"), string_view{"foo"});
}

TEST(StringSplit, StringSplitFirstLastDelimString)
{
    auto s = ":foo";
    EXPECT_EQ(split_first(s, ":"), string_view{});
    EXPECT_EQ(split_last(s, ":"), string_view{"foo"});
}

TEST(StringSplit, StringSplitFirstLastStringDelim)
{
    auto s = "foo:";
    EXPECT_EQ(split_first(s, ":"), string_view{"foo"});
    EXPECT_EQ(split_last(s, ":"), string_view{});
}

TEST(StringSplit, StringSplitFirstLastStringDelimString)
{
    auto s = "foo:bar";
    EXPECT_EQ(split_first(s, ":"), string_view{"foo"});
    EXPECT_EQ(split_last(s, ":"), string_view{"bar"});
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
