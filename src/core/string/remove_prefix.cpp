// Copyright (C) 2019, 2022 by Mark Melton
//

#include "core/string/remove_prefix.h"

namespace core
{

std::string_view remove_prefix_view(std::string_view str, std::string_view prefix)
{
    auto prefix_ptr = prefix.data();
    auto prefix_end = prefix_ptr + prefix.size();

    auto str_ptr = str.data();
    auto str_end = str_ptr + str.size();

    while (prefix_ptr < prefix_end and str_ptr < str_end and *prefix_ptr == *str_ptr)
    {
	++prefix_ptr;
	++str_ptr;
    }
    
    if (prefix_ptr == prefix_end)
	return std::string_view{str_ptr, size_t(str_end - str_ptr)};
    return str;
}

std::string remove_prefix(std::string_view str, std::string_view prefix)
{
    return std::string{remove_prefix_view(str, prefix)};
}

}; // end ns core
