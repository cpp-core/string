// Copyright (C) 2021, 2022 by Mark Melton
//

#include <regex>
#include "core/string/string.h"
#include "core/mr/mr.h"

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

bool String::contains(char character) const {
    for (auto ch : *this)
	if (ch == character)
	    return true;
    return false;
}

bool String::contains_any(string_view letters) const {
    for (auto l : letters)
	if (contains(l))
	    return true;
    return false;
}

bool String::contains_all(string_view letters) const {
    for (auto l : letters)
	if (not contains(l))
	    return false;
    return true;
}

bool String::contains_any(const std::set<char>& letters) const {
    for (auto ch : *this)
	if (letters.contains(ch))
	    return true;
    return false;
}

bool String::contains_all(const std::set<char>& letters) const {
    for (auto ch : letters)
	if (not contains(ch))
	    return false;
    return true;
}

bool String::is_alpha() const {
    for (auto ch : *this)
	if (not std::isalpha(ch))
	    return false;
    return true;
}

bool String::unique() const {
    std::set<char> letters;
    for (auto ch : *this)
	letters.insert(ch);
    return letters.size() == size();
}

String String::to_lower() const {
    String str{*this};
    return str.to_lower1();
}

String& String::to_lower1() {
    core::mr::source(*this).apply([](char& c) { c = std::tolower(c); }).eval();
    return *this;
}

String String::to_upper() const {
    String str{*this};
    return str.to_upper1();
}

String& String::to_upper1() {
    core::mr::source(*this).apply([](char& c) { c = std::toupper(c); }).eval();
    return *this;
}

String String::strip(const std::string& pattern) const {
    if (pattern.size() > 0) {
	std::regex r{pattern};
	return std::regex_replace(*this, r, "");
    }
    return *this;
}

String& String::strip1(const std::string& pattern) {
    *this = strip(pattern);
    return *this;
}

String String::lstrip(const std::string& pattern) const {
    return strip("^" + pattern);
}

String& String::lstrip1(const std::string& pattern) {
    *this = lstrip(pattern);
    return *this;
}

String String::rstrip(const std::string& pattern) const {
    return strip(pattern + "$");
}

String& String::rstrip1(const std::string& pattern) {
    *this = strip(pattern + "$");
    return *this;
}

String String::common_prefix(const std::string& str) const {
    String r{*this};
    return r.intersect_prefix1(str);
}

String& String::intersect_prefix1(const std::string& str) {
    auto idx = 0;
    for (; idx < std::min(size(), str.size()); ++idx)
	if (at(idx) != str.at(idx))
	    break;
    resize(idx);
    return *this;
}

bool String::match(const string& pattern) const {
    std::regex re{pattern};
    return std::regex_search(*this, re);
}

std::vector<std::string_view> String::split_on_regex(const std::string &regex) const {
    std::regex r{regex};
    std::sregex_token_iterator iter(begin(), end(), r, -1);
    std::sregex_token_iterator end;
    std::vector<std::string_view> result;
    for ( ; iter != end; ++iter)
	result.emplace_back(iter->first.base(), iter->second - iter->first);
    return result;
}

std::string common_prefix(const std::string& a, const std::string& b) {
    String sa{a};
    sa.intersect_prefix1(b);
    return sa.str();
}

}; // core
