// Copyright (C) 2021, 2022 by Mark Melton
//

#pragma once
#include <fmt/format.h>
#include <set>
#include <string>
#include <vector>
#include "core/string/lexical_cast.h"
#include "core/tuple/parse.h"

namespace core::str {

// The String class transparently extends std::string with convenient manipulation methods.
//
// Methods with both const and modifying versions are differentiated by denoting the const
// versions with [[nodiscard]] and appending a 1 to the name of the modifying version
// (analagous to scheme's convention of set!).
class String : public std::string {
public:
    using Base = std::string;
    using Base::Base;

    // Construct a String from std::string.
    String(const std::string& str);

    // Construct a String by moving from std::string.
    String(std::string&& str);

    // Return reference to the underlying string
    const std::string& str() const { return *this; }

    // Return true if String contains the given character.
    bool contains(char ch) const;
    
    // Return true is String contains any characters in letters.
    bool contains_any(std::string_view letters) const;
	
    // Return true is String contains all characters in letters.
    bool contains_all(std::string_view letters) const;
	
    // Return true is String contains any characters in letters.
    bool contains_any(const std::set<char>& letters) const;
	
    // Return true is String contains all characters in letters.
    bool contains_all(const std::set<char>& letters) const;
	
    // Return true if String contains only alpha characters.
    bool is_alpha() const;

    // Return true if all letters in String are unique.
    bool unique() const;
    
    // Return new String with characters converted to lower case.
    [[nodiscard]] String to_lower() const;

    // Convert characters to lower case in this String and return
    // reference.
    String& to_lower1();

    // Return new String with characters converted to upper case.
    [[nodiscard]] String to_upper() const;

    // Convert characters to upper case in this String and return
    // reference.
    String& to_upper1();

    // Return new String with `pattern` removed.
    [[nodiscard]] String strip(const std::string& pattern) const;
    
    // Delete `pattern` from this string and return reference.
    String& strip1(const std::string& pattern);

    // Return new String with leading `pattern` removed.
    [[nodiscard]] String lstrip(const std::string& pattern) const;

    // Delete leading `pattern` from this string and return reference.
    String& lstrip1(const std::string& pattern);

    // Return new string with trailing `pattern` removed.
    [[nodiscard]] String rstrip(const std::string& pattern) const;

    // Delete trailing `pattern` from this string and return reference.
    String& rstrip1(const std::string& pattern);

    // Return new String containing common prefix with given `str`.
    [[nodiscard]] String common_prefix(const std::string& str) const;

    // Delete all but common prefix with `str` from this string and
    // return reference.
    String& intersect_prefix1(const std::string& str);

    // Return true if `pattern` matches any part of this string.
    // auto str = "abcdefhijklmnopqrstuvwxyz"_S;
    // str.match("^[a-z]*$") == true;
    // str.match("mno")      == true;
    // str.match("abc$")     == false;
    // str.match("^xyz")     == false;
    bool match(const std::string& pattern) const;

    // Split on the given `regex` and return the vector of results.
    std::vector<std::string_view> split_on_regex(const std::string& regex) const;

    // Return the lexical_cast of this string to type `T`.
    //
    // *auto str = "1.23_S";
    // str.parse<real>() --> 1.23
    // str.parse<int>()  --> throws*
    template<class T>
    T parse() const {
	return core::str::lexical_cast<T>(*this);
    }
    
    // Split on the given `regex` and return a tuple of parsed results.
    //
    // *auto str = "1.23 foo"_S
    // str.parse<real,std::string>() --> std::tuple<1.23,"foo">
    // str.parse<real,real>()        --> throws*
    // str.parse<real>()             --> throws*
    template<class... Ts>
    requires (sizeof...(Ts) > 1)
    std::tuple<Ts...> parse(const std::string& regex) const {
	constexpr auto N = sizeof...(Ts);
	auto fields = split_on_regex(regex);
	if (fields.size() != N)
	    throw std::runtime_error
		(fmt::format("expected {} fields, but got {}", N, fields.size()));
	return core::tp::parse<std::tuple<Ts...>>(fields);
    }
};

std::string common_prefix(const std::string& a, const std::string& b);

// A vector of String
using Strings = std::vector<String>;

}; // end core::str

// Create a String from characters.
core::str::String operator"" _S(const char*, unsigned long);

