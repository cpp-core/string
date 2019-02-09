// Copyright (C) 2017, 2018, 2019 by Mark Melton
//

#pragma once
#include "core/common.h"

namespace core {

string_views split(string_view str, string_view delim);

size_t split(string_view input, string_view delim, string_views& fields);

strings split_copy(string_view str, string_view delim);

size_t fast_split(string_view input, char delim, string_views& fields);

}; // end ns core
