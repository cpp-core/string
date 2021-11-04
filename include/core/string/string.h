// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include <string>
#include "core/common.h"

namespace core {

// String - Transparently extends std::string with convenient manipulation methods.
//
// Methods with both const and modifying versions are differentiated
// by denoting the const versions with [[nodiscard]] and appending a 1
// to the name of the modifying version (analagous to scheme's
// convention of set!).
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
    bool match(const string& pattern) const;
};

std::string common_prefix(const std::string& a, const std::string& b);

}; // end core

// Create a String from characters.
core::String operator"" _S(const char*, unsigned long);
