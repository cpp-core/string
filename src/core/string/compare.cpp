// Copyright (C) 2019, 2022 by Mark Melton
//

#include "core/string/compare.h"

namespace core::str
{

bool iequals(std::string_view a, std::string_view b)
{
    return std::equal(a.begin(), a.end(), b.begin(), b.end(),
		      [](char a, char b) { return std::tolower(a) == std::tolower(b); });
}

}; // end ns core
