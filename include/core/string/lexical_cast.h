// Copyright (C) 2017, 2018, 2019 by Mark Melton
//

#pragma once
#include "common.h"
#include "traits/concepts.h"

namespace core {

struct lexical_cast_error : public std::runtime_error
{ lexical_cast_error(string_view input, string_view type); };

namespace detail
{

template<typename T>
struct lexical_cast_impl;

template<>
struct lexical_cast_impl<bool>
{ static bool parse(string_view); };

template<>
struct lexical_cast_impl<string>
{ static string parse(string_view); };

template<ArithmeticType T>
struct lexical_cast_impl<T>
{ static T parse(string_view s); };

}; // detail

template<typename T>
T lexical_cast(string_view s)
{ return detail::lexical_cast_impl<T>::parse(s); }

}; // end ns core
