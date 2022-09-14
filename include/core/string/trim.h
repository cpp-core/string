// Copyright (C) 2018, 2019, 2022 by Mark Melton
//

#pragma once
#include <string>
#include <string_view>

namespace core::str {

// ltrim, rtrim, trim -- Return a new string_view with leading,
// trailing or both leading and trailing characters removed. The
// default characters are whitespace.
//
// ltrim -- Remove leading characters from the given string_view.
// rtrim -- Remove trailing characters from the given string_view.
// trim -- Remove both leading and trailing characters from the given string_view.
std::string_view ltrim(std::string_view str, std::string_view characters = " \f\n\r\t\v");
std::string_view rtrim(std::string_view str, std::string_view characters = " \f\n\r\t\v");
std::string_view trim(std::string_view str, std::string_view characters = " \f\n\r\t\v");

}; // end ns core
