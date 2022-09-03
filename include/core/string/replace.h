// Copyright (C) 2019, 2022 by Mark Melton
//

#pragma once
#include "core/utility/common.h"

namespace core
{

namespace detail
{
string replace_all_base(string_view str, string_view from, string_view to);
};

template<class T, class U, class... Ts>
string replace_all(string_view str, T from, U to, Ts&&... rest)
{
    if constexpr (sizeof...(Ts) == 0) return detail::replace_all_base(str, from, to);
    else return replace_all(detail::replace_all_base(str, from, to), std::forward<Ts>(rest)...);
}

}; // end ns core
