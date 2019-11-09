// Copyright (C) 2019 by Mark Melton
//

#include "core/string/tolower.h"

namespace core
{

void tolower(string& str)
{
    for (auto& c : str)
	c = std::tolower(c);
}

string tolower(string_view str)
{
    string r{str};
    tolower(r);
    return r;
}

}; // end ns core
