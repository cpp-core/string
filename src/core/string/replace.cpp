// Copyright (C) 2019, 2022 by Mark Melton
//

#include "core/string/replace.h"

namespace core
{

namespace detail
{

std::string replace_all_base(std::string_view source, std::string_view from, std::string_view to)
{
    size_t start_pos{0};
    auto str = std::string{source};
    while((start_pos = str.find(from, start_pos)) != std::string::npos)
    {
	str.replace(start_pos, from.size(), to);
	start_pos += to.size();
    }
    return str;
}

}; // end ns detail
}; // end ns core
