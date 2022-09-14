// Copyright (C) 2018, 2019, 2022 by Mark Melton
//

#pragma once
#include <string>

namespace core::str
{

std::string slurp_into_string(const std::string& filename);
std::string slurp_into_string(std::string_view filename);
std::string slurp_into_string(std::istream& is);

}; // end ns core
