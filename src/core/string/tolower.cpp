// Copyright (C) 2019, 2022 by Mark Melton
//

#include "core/string/tolower.h"

namespace core
{

void tolower(std::string& str)
{
    for (auto& c : str)
	c = std::tolower(c);
}

std::string tolower(std::string_view str)
{
    std::string r{str};
    tolower(r);
    return r;
}

}; // end ns core
