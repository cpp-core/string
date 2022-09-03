// Copyright (C) 2018, 2019, 2022 by Mark Melton
//

#pragma once
#include "core/string/fixed.h"
#include "core/extra/json/nljson.h"

namespace core
{


template<size_t N>
void to_json(nlj::json& j, const fixed_string<N>& str)
{
    j = str.begin();
}

template<size_t N>
void from_json(const nlj::json& j, fixed_string<N>& str)
{
    str = fixed_string<N>{j.get<string>()};
}

}; // core

