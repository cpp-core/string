// Copyright (C) 2017, 2018, 2019 by Mark Melton
//

#pragma once
#include "core/common.h"
#include "core/traits/concepts.h"

namespace core {

struct lexical_cast_error : public std::runtime_error
{ lexical_cast_error(string_view input, string_view type); };

namespace detail
{

template<class T>
struct lexical_cast_impl;

template<>
struct lexical_cast_impl<bool>
{ static bool parse(string_view); };

template<>
struct lexical_cast_impl<string>
{ static string parse(string_view); };

template<>
struct lexical_cast_impl<const char*>
{ static const char* parse(string_view); };

template<Arithmetic T>
struct lexical_cast_impl<T>
{ static T parse(string_view s); };

}; // detail

template<class T, class... Us>
T lexical_cast(string_view s, Us... extra)
{ return detail::lexical_cast_impl<T>::parse(s, extra...); }

}; // end ns core
