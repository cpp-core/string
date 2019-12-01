// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include "core/common.h"

namespace core
{

string remove_prefix(string_view str, string_view prefix);
string_view remove_prefix_view(string_view str, string_view prefix);

}; // end ns core