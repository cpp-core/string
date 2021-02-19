// Copyright (C) 2017, 2018, 2019, 2021 by Mark Melton
//

#pragma once
#include <sstream>
#include "core/common.h"

namespace core {

template<class T>
string to_string(const T& value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

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
struct lexical_cast_impl<char>
{ static char parse(string_view); };

template<>
struct lexical_cast_impl<string>
{ static string parse(string_view); };

template<>
struct lexical_cast_impl<const char*>
{ static const char* parse(string_view); };

template<>
struct lexical_cast_impl<uint8>
{ static uint8 parse(string_view s); };

template<>
struct lexical_cast_impl<uint16>
{ static uint16 parse(string_view s); };

template<>
struct lexical_cast_impl<uint32>
{ static uint32 parse(string_view s); };

template<>
struct lexical_cast_impl<uint64>
{ static uint64 parse(string_view s); };

template<>
struct lexical_cast_impl<int8>
{ static int8 parse(string_view s); };

template<>
struct lexical_cast_impl<int16>
{ static int16 parse(string_view s); };

template<>
struct lexical_cast_impl<int32>
{ static int32 parse(string_view s); };

template<>
struct lexical_cast_impl<int64>
{ static int64 parse(string_view s); };

template<>
struct lexical_cast_impl<real32>
{ static real32 parse(string_view s); };

template<>
struct lexical_cast_impl<real64>
{ static real64 parse(string_view s); };

template<>
struct lexical_cast_impl<real128>
{ static real128 parse(string_view s); };

}; // detail

template<class T, class... Us>
T lexical_cast(string_view s, Us... extra)
{ return detail::lexical_cast_impl<T>::parse(s, extra...); }

}; // end ns core
