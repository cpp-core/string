// Copyright (C) 2017, 2018, 2019 by Mark Melton
//

#include <fmt/printf.h>
#include "core/traits/type.h"
#include "core/string/lexical_cast.h"
#include "core/string/from_chars.h"

namespace core {

lexical_cast_error::lexical_cast_error(string_view input, string_view type)
    : std::runtime_error(fmt::sprintf("cannot parse '%s' as '%s'", input, type))
{ }

namespace detail
{

bool lexical_cast_impl<bool>::parse(string_view input)
{
    if (input == "0" or input == "f" or input == "false")
	return false;
    if (input == "1" or input == "t" or input == "true")
	return true;
    throw lexical_cast_error(input, "bool");
}

string lexical_cast_impl<string>::parse(string_view input)
{ return string(input); }

const char* lexical_cast_impl<const char*>::parse(string_view input)
{ return input.begin(); }

template<Arithmetic T>
T lexical_cast_impl<T>::parse(string_view input)
{
    try
    {
	T value = 0;
	auto r = std::from_chars(input.begin(), input.end(), value);
	if (r.ptr != input.end())
	    throw lexical_cast_error(input, type_traits<T>::name);
	return value;
    }
    catch (std::invalid_argument const&)
    {
	throw lexical_cast_error(input, type_traits<T>::name);
    }
    catch (std::out_of_range const&)
    {
	throw lexical_cast_error(input, type_traits<T>::name);
    }
}

}; // detail

template struct detail::lexical_cast_impl<int8>;
template struct detail::lexical_cast_impl<int16>;
template struct detail::lexical_cast_impl<int32>;
template struct detail::lexical_cast_impl<int64>;
template struct detail::lexical_cast_impl<uint8>;
template struct detail::lexical_cast_impl<uint16>;
template struct detail::lexical_cast_impl<uint32>;
template struct detail::lexical_cast_impl<uint64>;
template struct detail::lexical_cast_impl<real32>;
template struct detail::lexical_cast_impl<real64>;
template struct detail::lexical_cast_impl<real128>;

}; // end ns core
