// Copyright (C) 2017, 2018, 2019, 2021 by Mark Melton
//

#include <gtest/gtest.h>
#include "core/string/lexical_cast_stl.h"
#include "core/mp/foreach.h"
#include "coro/stream/stream.h"

using namespace core;
using namespace costr;

const int NumberSamples = 64;

using TestTypes = std::tuple<int,real,string>;
using TestContainers = std::tuple<std::vector<int>,std::vector<string>>;

TEST(StringLexicalStl, Pair)
{
    mp::foreach<TestTypes>([]<class T>() {
	    mp::foreach<TestTypes>([]<class U>() {
		    auto g = take(zip(sampler<T>(), sampler<U>()), NumberSamples);
		    for (const auto& [a, b] : g) {
			auto str = fmt::format("{}:{}", a, b);
			auto [first, second] = lexical_cast<std::pair<T,U>>(str);
			EXPECT_EQ(first, a);
			EXPECT_EQ(second, b);
		    }
		});
	});		
}

TEST(StringLexicalCast, Vector)
{
    mp::foreach<TestContainers>([]<class T>() {
	    auto g = take(sampler<T>(), NumberSamples);
	    for (const auto& container : g) {
		int idx{0};
		string str;
		for (const auto& elem : container) {
		    if (idx++)
			str += ",";
		    str += fmt::format("{}", elem);
		}
		auto vec = lexical_cast<T>(str);
		EXPECT_EQ(vec, container);
	    }
	});
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
