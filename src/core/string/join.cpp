// Copyright (C) 2019, 2021, 2022 by Mark Melton
//

#include <list>
#include <set>
#include <vector>
#include "core/fp/fold.h"
#include "core/string/join.h"

using std::string;
using strings = std::vector<string>;
using std::string_view;
using string_views = std::vector<string_view>;
using std::list;
using std::set;

namespace core::str {

template<class Container>
string join(const Container& strs, string_view separator, string_view terminator)
{
    if (strs.size() == 0)
	return string{terminator};

    string infix{separator};
    auto r = fp::fold_l(++strs.begin(), strs.end(), string{*strs.begin()},
			[=](const auto& a, const auto& b) { return a + infix + std::string(b); });
    r += string{terminator};
    return r;
}

template string join<list<string>>(const list<string>&, string_view, string_view);
template string join<set<string>>(const set<string>&, string_view, string_view);
template string join<strings>(const strings&, string_view, string_view);

template string join<list<string_view>>(const list<string_view>&, string_view, string_view);
template string join<set<string_view>>(const set<string_view>&, string_view, string_view);
template string join<string_views>(const string_views&, string_view, string_view);

}; // end ns core
