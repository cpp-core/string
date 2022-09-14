// Copyright (C) 2019, 2022 by Mark Melton
//

#pragma once
#include <string>

namespace core
{

namespace detail
{
std::string replace_all_base(std::string_view str, std::string_view from, std::string_view to);
};

template<class T, class U, class... Ts>
std::string replace_all(std::string_view str, T from, U to, Ts&&... rest)
{
    if constexpr (sizeof...(Ts) == 0) return detail::replace_all_base(str, from, to);
    else return replace_all(detail::replace_all_base(str, from, to), std::forward<Ts>(rest)...);
}

}; // end ns core
