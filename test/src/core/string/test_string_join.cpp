// Copyright (C) 2019 by Mark Melton
//

#include <list>
#include <set>
#include <vector>
#include <gtest/gtest.h>
#include "string/join.h"

using namespace core;

template<typename Container>
void test_string_join_empty()
{
    Container s;
    EXPECT_EQ(join(s), "");
    EXPECT_EQ(join(s, ":", "="), "=");
}

TEST(StringJoin, Empty)
{
    test_string_join_empty<std::list<std::string>>();
    test_string_join_empty<std::list<std::string_view>>();
    test_string_join_empty<std::set<std::string>>();
    test_string_join_empty<std::set<std::string_view>>();
    test_string_join_empty<std::vector<std::string>>();
    test_string_join_empty<std::vector<std::string_view>>();
}

template<typename Container>
void test_string_join_one()
{
    Container s = { "abc" };
    EXPECT_EQ(join(s), "abc");
    EXPECT_EQ(join(s, ":", "="), "abc=");
}

TEST(StringJoin, One)
{
    test_string_join_one<std::list<std::string>>();
    test_string_join_one<std::list<std::string_view>>();
    test_string_join_one<std::set<std::string>>();
    test_string_join_one<std::set<std::string_view>>();
    test_string_join_one<std::vector<std::string>>();
    test_string_join_one<std::vector<std::string_view>>();
}

template<typename Container>
void test_string_join_two()
{
    Container s = { "abc", "def" };
    EXPECT_EQ(join(s), "abc, def");
    EXPECT_EQ(join(s, ":", "="), "abc:def=");
}

TEST(StringJoin, Two)
{
    test_string_join_two<std::list<std::string>>();
    test_string_join_two<std::list<std::string_view>>();
    test_string_join_two<std::set<std::string>>();
    test_string_join_two<std::set<std::string_view>>();
    test_string_join_two<std::vector<std::string>>();
    test_string_join_two<std::vector<std::string_view>>();
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
