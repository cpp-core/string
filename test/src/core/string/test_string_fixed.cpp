// Copyright (C) 2017, 2018, 2019 by Mark Melton
//

#include <gtest/gtest.h>
#include <fmt/format.h>
#include "string/fixed.h"
#include "ranges/view/string.h"
#include "ranges/view/take.h"

using namespace core;
static const size_t NumberLoops = 1'000'000;

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
    // auto gstr = gen_string('a', 'z', 0, 8);
    auto gstr = v::str::alpha(8);
    for (auto s : gstr | v::take(NumberLoops))
    {
	auto f = fixed_string<8u>(s);
	EXPECT_TRUE(match(f, s));
    }
}

// TEST(StringFixed, ConstructorArray)
// {
//     auto garr = gen_array<8>('a', 'z', 0, 8);
//     for (size_t i = 0; i < NumberLoops; ++i)
//     {
// 	auto a = garr();
// 	auto f = fixed_string<8u>(a);
// 	EXPECT_TRUE(match(f, a));
//     }
// }

TEST(StringFixed, Size)
{
    fixed_string<1> x;
    EXPECT_EQ(x.size(), 1u);
}

TEST(StringFixed, Span)
{
    fixed_string<10> x;
    auto span = x.span();
    EXPECT_EQ(span.begin(), x.begin());
    EXPECT_EQ(span.size(), x.end() - x.begin());
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
