// Copyright (C) 2019, 2022 by Mark Melton
//

#pragma once
#include <string>

namespace core::str
{

std::string remove_prefix(std::string_view str, std::string_view prefix);
std::string_view remove_prefix_view(std::string_view str, std::string_view prefix);

}; // end ns core
