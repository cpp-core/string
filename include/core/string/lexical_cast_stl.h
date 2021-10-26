// Copyright (C) 2017, 2018, 2019, 2021 by Mark Melton
//

#pragma once
#include "core/string/lexical_cast.h"

namespace core::detail {

template<class T, class U>
struct lexical_cast_impl<std::pair<T,U>> {
    static std::pair<T,U> parse(string_view s, string_view sep = ":") {
	auto pos = s.find_first_of(sep);
	if ((pos == s.size()) or (pos != s.find_last_of(sep)))
	    throw core::lexical_cast_error{s, "first:second"};
	auto first = lexical_cast<T>(s.substr(0, pos));
	auto second = lexical_cast<U>(s.substr(pos + 1));
	return {first, second};
    }
};

template<class T>
struct lexical_cast_impl<std::vector<T>> {
    static std::vector<T> parse(string_view s, char sep = ',') {
	std::vector<T> container;
	if (s.size() > 0) {
	    const char *ptr = s.data();
	    const char *end = ptr + s.size();
	    const char *begin = ptr;
	    while (ptr < end + 1) {
		if ((ptr == end) or (*ptr == sep)) {
		    container.emplace_back(lexical_cast<T>({begin, size_t(ptr - begin)}));
		    ++ptr;
		    begin = ptr;
		}
		else
		    ++ptr;
	    }
	}
	return container;
    }
};

}; // core::detail
