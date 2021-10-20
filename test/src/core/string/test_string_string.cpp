// Copyright (C) 2017, 2018, 2019, 2021 by Mark Melton
//

#include <gtest/gtest.h>
#include <fmt/format.h>
#include "core/string/string.h"
#include "coro/stream/stream.h"

using namespace core;
using namespace costr;

const int NumberSamples = 64;

TEST(String, Strip)
{
    auto gl = str::alpha();
    auto gc = str::alpha();
    auto gr = str::alpha();
    for (auto [l, c, r] : take(zip(std::move(gl), std::move(gc), std::move(gr)), NumberSamples)) {
	auto base = l + c + r;
	{
	    String str{base};
	    str.lstrip(l);
	    EXPECT_EQ(str, c + r);
	}
	{
	    String str{base};
	    str.rstrip(r);
	    EXPECT_EQ(str, l + c);
	}
	{
	    String str{base};
	    str.strip(c);
	    EXPECT_EQ(str, l + r);
	}
    }
}

TEST(String, IntersectPrefix)
{
    auto gl = str::alpha();
    auto gc = str::alpha();
    auto gr = str::alpha();
    for (auto [l, c, r] : take(zip(std::move(gl), std::move(gc), std::move(gr)), NumberSamples)) {
	String a = c + l;
	String b = c + r;
	auto common = common_prefix(a, b);
	a.intersect_prefix(c + r);
	b.intersect_prefix(c + l);

	EXPECT_EQ(common, a);
	EXPECT_EQ(common, b);
    }
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
