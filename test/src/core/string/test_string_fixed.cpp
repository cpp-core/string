// Copyright (C) 2017, 2018, 2019, 2021, 2022 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/string/fixed.h"
#include "coro/stream/stream.h"

using namespace core;
static const size_t NumberLoops = 100'000;

template<size_t N>
bool match(const fixed_string<N>& s, string_view view)
{
    for (size_t i = 0; i < view.size(); ++i)
	if (s[i] != view[i])
	    return false;
    for (size_t i = view.size(); i < s.size(); ++i)
	if (s[i] != 0)
	    return false;
    return true;
}

template<size_t N, typename CharArray>
bool match(const fixed_string<N>& s, CharArray view)
{
    for (size_t i = 0; i < view.size(); ++i)
	if (s[i] != view[i])
	    return false;
    for (size_t i = view.size(); i < s.size(); ++i)
	if (s[i] != 0)
	    return false;
    return true;
}


TEST(StringFixed, ConstructorStringView)
{
    for (auto s : coro::str::alpha(8, 8) | coro::take(10)) {
	auto f = fixed_string<8u>(s);
	EXPECT_TRUE(match(f, s));
    }
}

TEST(StringFixed, Size)
{
    fixed_string<1> x;
    EXPECT_EQ(x.size(), 1u);
}

TEST(StringFixed, Span)
{
    fixed_string<10> x;
    auto span = x.span();
    EXPECT_EQ(span.size(), x.end() - x.begin());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
