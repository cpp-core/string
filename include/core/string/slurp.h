// Copyright (C) 2018, 2019 by Mark Melton
//

#pragma once
#include "core/common.h"

namespace core
{

string slurp_into_string(const string& filename);
string slurp_into_string(string_view filename);
string slurp_into_string(std::istream& is);

}; // end ns core
