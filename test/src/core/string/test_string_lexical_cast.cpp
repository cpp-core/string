// Copyright (C) 2017, 2018, 2019 by Mark Melton
//

#include <gtest/gtest.h>
#include <range/v3/view/take.hpp>
#include "core/string/lexical_cast.h"
#include "core/traits/extrema.h"
#include "core/range/sample.h"

using namespace core;

TEST(StringLexicalCastTest, String)
{
    std::string s = lexical_cast<std::string>(string("abc"));
    EXPECT_EQ(s, "abc");
}

template<typename T>
struct number_test
{
    static void apply()
    {
	auto actual_min_value = extrema<T>::min();
	auto min_repr = fmt::format(extrema<T>::fmt_spec(), actual_min_value);
	auto min_value = lexical_cast<T>(min_repr);
	EXPECT_EQ(min_value, actual_min_value);

	auto actual_max_value = extrema<T>::max();
	auto max_repr = fmt::format(extrema<T>::fmt_spec(), actual_max_value);
	auto max_value = lexical_cast<T>(max_repr);
	EXPECT_EQ(max_value, actual_max_value);
	
	EXPECT_THROW(lexical_cast<T>("abc"), lexical_cast_error);
	
	auto generator = cr::uniform(actual_min_value, actual_max_value);
	for (auto value : generator | v::take(5))
	{
	    string s = fmt::format(extrema<T>::fmt_spec(), value);
	    auto n = lexical_cast<T>(s);
	    EXPECT_EQ(value, n);
	    string s2 = fmt::format(extrema<T>::fmt_spec(), n);
	    EXPECT_EQ(s, s2);
	}
    }
};

TEST(StringLexicalCastTest, Int8)
{ number_test<int8>::apply(); }

TEST(StringLexicalCastTest, Int16)
{ number_test<int16>::apply(); }

TEST(StringLexicalCastTest, Int32)
{ number_test<int32>::apply(); }

TEST(StringLexicalCastTest, Int64)
{ number_test<int64>::apply(); }

TEST(StringLexicalCastTest, Uint8)
{ number_test<uint8>::apply(); }

TEST(StringLexicalCastTest, Uint16)
{ number_test<uint16>::apply(); }

TEST(StringLexicalCastTest, Uint32)
{ number_test<uint32>::apply(); }

TEST(StringLexicalCastTest, Uint64)
{ number_test<uint64>::apply(); }

// TEST(StringLexicalCastTest, Real32)
// { number_test<real32>::apply(); }

TEST(StringLexicalCastTest, Real64)
{ number_test<real64>::apply(); }

TEST(StringLexicalCastTest, Real128)
{ number_test<real128>::apply(); }


int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
