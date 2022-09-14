// Copyright (C) 2019, 2022 by Mark Melton
//

#pragma once
#include <string>

namespace core::str
{

void tolower(std::string& str);
std::string tolower(std::string_view str);

}; // end ns core
