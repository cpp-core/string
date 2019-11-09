// Copyright (C) 2019 by Mark Melton
//

#include "core/string/starts_with.h"

namespace core {

bool starts_with(std::string_view str, std::string_view prefix) noexcept
{
    if (prefix.empty() or prefix.size() > str.size())
	return false;
    for (auto p = prefix.begin(), s = str.begin(); p != prefix.end(); ++p, ++s)
	if (*p != *s)
	    return false;
    return true;
}

bool starts_with(std::string_view str, char c) noexcept
{
    return str.size() > 0 and str.front() == c;
}

}; // end ns core
