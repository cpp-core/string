// Copyright (C) 2019 by Mark Melton
//

#include "core/string/replace.h"

namespace core
{

namespace detail
{

string replace_all_base(string_view source, string_view from, string_view to)
{
    size_t start_pos{0};
    string str = string{source};
    while((start_pos = str.find(from, start_pos)) != string::npos)
    {
	str.replace(start_pos, from.size(), to);
	start_pos += to.size();
    }
    return str;
}

}; // end ns detail
}; // end ns core
