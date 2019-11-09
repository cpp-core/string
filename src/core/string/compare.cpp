// Copyright (C) 2019 by Mark Melton
//

#include "core/string/compare.h"

namespace core
{

bool iequals(string_view a, string_view b)
{
    return std::equal(a.begin(), a.end(), b.begin(), b.end(),
		      [](char a, char b) { return std::tolower(a) == std::tolower(b); });
}

}; // end ns core
