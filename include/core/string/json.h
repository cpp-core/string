// Copyright (C) 2018, 2019, 2022 by Mark Melton
//

#pragma once
#include <nlohmann/json.hpp>
#include "core/string/fixed.h"

namespace core {

using json = nlohmann::json;

template<size_t N>
void to_json(json& j, const fixed_string<N>& str)
{
    j = str.begin();
}

template<size_t N>
void from_json(const json& j, fixed_string<N>& str)
{
    str = fixed_string<N>{j.get<std::string>()};
}

}; // core

