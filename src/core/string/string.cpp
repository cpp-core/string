// Copyright (C) 2021 by Mark Melton
//

#include <regex>
#include "core/string/string.h"
#include "core/common.h"

core::String operator"" _S(const char *str, unsigned long) {
    return core::String{str};
}

namespace core
{

String::String(const std::string& str)
    : Base(str) {
}

String::String(std::string&& str)
    : Base(str) {
}

String& String::strip(const std::string& pattern) {
    if (pattern.size() > 0) {
	std::regex r{pattern};
	*this = std::regex_replace(*this, r, "");
    }
    return *this;
}

String& String::lstrip(const std::string& pattern) {
    return strip("^" + pattern);
}

String& String::rstrip(const std::string& pattern) {
    return strip(pattern + "$");
}

String& String::intersect_prefix(const std::string& str) {
    auto idx = 0;
    for (; idx < std::min(size(), str.size()); ++idx)
	if (at(idx) != str.at(idx))
	    break;
    resize(idx);
    return *this;
}

std::string common_prefix(const std::string& a, const std::string& b) {
    String sa{a};
    sa.intersect_prefix(b);
    return sa.str();
}

}; // core
