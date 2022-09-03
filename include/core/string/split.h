// Copyright (C) 2017, 2018, 2019, 2020, 2022 by Mark Melton
//

#pragma once
#include "core/util/common.h"

namespace core {

string_views split(string_view str, string_view delim);

size_t split(string_view input, string_view delim, string_views& fields);

strings split_copy(string_view str, string_view delim);

size_t fast_split(string_view input, char delim, string_views& fields);

std::string_view split_first(std::string_view str, std::string_view delim);
std::string_view split_last(std::string_view str, std::string_view delim);

}; // end ns core
