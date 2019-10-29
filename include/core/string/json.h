// Copyright (C) 2018, 2019 by Mark Melton
//

#pragma once
#include "core/string/fixed.h"
#include "core/json.h"

namespace core
{


template<size_t N>
void to_json(core::json& j, const fixed_string<N>& str)
{
    j = str.begin();
}

template<size_t N>
void from_json(const core::json& j, fixed_string<N>& str)
{
    str = fixed_string<N>{j.get<string>()};
}

}; // core

