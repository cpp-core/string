// Copyright (C) 2018, 2019 by Mark Melton
//

#include "core/string/trim.h"

namespace core {

// ltrim -- trim whitespace from start of str.
//
std::string_view ltrim(std::string_view str, std::string_view characters)
{
    auto pos = str.find_first_not_of(characters);
    if (pos == std::string_view::npos) return std::string_view();
    else return str.substr(pos);
}

// rtrim -- trim whitespace from end of str.
//
std::string_view rtrim(std::string_view str, std::string_view characters)
{
    auto pos = str.find_last_not_of(characters);
    if (pos == std::string_view::npos) return std::string_view();
    else return str.substr(0, pos + 1);
}

// trim -- trim whitespace from start and end of str.
//
std::string_view trim(std::string_view str, std::string_view characters)
{
    return rtrim(ltrim(str, characters), characters);
}

}; // end ns core
