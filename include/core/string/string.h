// Copyright (C) 2021 by Mark Melton
//

#pragma once
#include <string>

namespace core {

class String : public std::string {
public:
    using Base = std::string;
    using Base::Base;

    // Construct a String from std::string.
    String(const std::string& str);

    // Construct a String by moving from std::string.
    String(std::string&& str);

    const std::string& str() const { return *this; }

    // Remove `pattern` from this String.
    String& strip(const std::string& pattern);
    
    // Remove leading `pattern` from this String.
    String& lstrip(const std::string& pattern);

    // Remove trailing `pattern` from this String.
    String& rstrip(const std::string& pattern);

    // Only retain common prefix with given `str`.
    String& intersect_prefix(const std::string& str);
};

std::string common_prefix(const std::string& a, const std::string& b);

}; // end core

core::String operator"" _S(const char*, unsigned long);
