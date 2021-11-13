// Copyright (C) 2017, 2018, 2019, 2021 by Mark Melton
//

#include <gtest/gtest.h>
#include <fmt/format.h>
#include "core/string/string.h"
#include "core/fp/fold.h"
#include "coro/stream/stream.h"

using namespace core;
using namespace coro;
using core::fp::all;

const int NumberSamples = 64;

bool is_lower_case(const string& str) {
    return all(str, [](char c) { return std::islower(c); });
}

bool is_upper_case(const string& str) {
    return all(str, [](char c) { return std::isupper(c); });
}

TEST(String, ToLower)
{
    auto g = str::alpha();
    for (String str : take(std::move(g), NumberSamples)) {
	auto lc = str.to_lower();
	EXPECT_TRUE(is_lower_case(lc));
	str.to_lower1();
	EXPECT_TRUE(is_lower_case(str));
    }
}

TEST(String, ToUpper)
{
    auto g = str::alpha();
    for (String str : take(std::move(g), NumberSamples)) {
	auto lc = str.to_upper();
	EXPECT_TRUE(is_upper_case(lc));
	str.to_upper1();
	EXPECT_TRUE(is_upper_case(str));
    }
}

TEST(String, Strip)
{
    auto g = str::alpha() * str::alpha() * str::alpha() | zip() | take(NumberSamples);
    for (auto [l, c, r] : g) {
	bool lgood = l.empty() or c.empty() or (l.back() != c.front());
	bool rgood = r.empty() or c.empty() or (r.front() != c.back());
	
	auto base = l + c + r;
	if (lgood) {
	    String str{base};
	    EXPECT_EQ(str.lstrip(l), c + r);
	    str.lstrip1(l);
	    EXPECT_EQ(str, c + r);
	}
	
	if (rgood) {
	    String str{base};
	    EXPECT_EQ(str.rstrip(r), l + c);
	    str.rstrip1(r);
	    EXPECT_EQ(str, l + c);
	}
	
	// if (lgood and rgood) {
	//     cout << "?: " << l << " " << c << " " << r << endl;
	//     String str{base};
	//     EXPECT_EQ(str.strip(c), l + r);
	//     str.strip1(c);
	//     EXPECT_EQ(str, l + r);
	// }
    }
}

TEST(String, IntersectPrefix)
{
    auto g = str::alpha() * str::alpha() * str::alpha() | zip() | take(NumberSamples);
    for (auto [l, c, r] : g) {
	String a = c + l;
	String b = c + r;
	auto common = common_prefix(a, b);
	
	EXPECT_EQ(a.common_prefix(c + r), common);
	EXPECT_EQ(b.common_prefix(c + l), common);
	
	a.intersect_prefix1(c + r);
	b.intersect_prefix1(c + l);

	EXPECT_EQ(common, a);
	EXPECT_EQ(common, b);
    }
}

TEST(String, Matches)
{
    auto str = "abcdefhijklmnopqrstuvwxyz"_S;
    EXPECT_TRUE(str.match(""));
    EXPECT_TRUE(str.match("^[a-z]*$"));
    EXPECT_TRUE(str.match("^abc"));
    EXPECT_TRUE(str.match("xyz$"));
    EXPECT_TRUE(str.match("mno"));

    EXPECT_FALSE(str.match("M"));
    EXPECT_FALSE(str.match("[A-Z]"));
    EXPECT_FALSE(str.match("abc$"));
    EXPECT_FALSE(str.match("^xyz"));
    EXPECT_FALSE(str.match("nm"));
}

TEST(String, Parse)
{
    auto str = "1.23"_S;
    auto x = str.parse<real>();
    EXPECT_EQ(x, 1.23);
    EXPECT_THROW(str.parse<int>(), std::runtime_error);
}

TEST(String, ParseTuple)
{
    auto str = "1.23,hello"_S;
    auto [x, s] = str.parse<real,std::string>(",");
    EXPECT_EQ(x, 1.23);
    EXPECT_EQ(s, "hello"s);
    EXPECT_THROW((str.parse<real,real>(",")), std::runtime_error);
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
