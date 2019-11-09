// Copyright (C) 2019 by Mark Melton
//

#include "core/string/starts_with.h"

namespace core {

bool ends_with(std::string_view str, std::string_view suffix) noexcept
{
    if (suffix.empty() or suffix.size() > str.size())
	return false;
    for (auto p = suffix.rbegin(), s = str.rbegin(); p != suffix.rend(); ++p, ++s)
	if (*p != *s)
	    return false;
    return true;
}

bool ends_with(std::string_view str, char c) noexcept
{
    return str.size() > 0 and str.back() == c;
}

}; // end ns core
