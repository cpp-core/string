// Copyright (C) 2017, 2018, 2019, 2020, 2022 by Mark Melton
//

#pragma once
#include <string>
#include <vector>

namespace core::str {

std::vector<std::string_view> split(std::string_view str, std::string_view delim);

size_t split(std::string_view input, std::string_view delim, std::vector<std::string_view>&fields);

std::vector<std::string> split_copy(std::string_view str, std::string_view delim);

size_t fast_split(std::string_view input, char delim, std::vector<std::string_view>& fields);

std::string_view split_first(std::string_view str, std::string_view delim);
std::string_view split_last(std::string_view str, std::string_view delim);

}; // end ns core
