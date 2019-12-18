// Copyright (C) 2017, 2018, 2019 by Mark Melton
//

#include <fmt/printf.h>
#include "core/traits/type.h"
#include "core/string/lexical_cast.h"
#include "core/string/from_chars.h"
#include "core/pp/map.h"

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

template<class T>
T parse_number(string_view input)
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

#define CODE(T)						\
    T lexical_cast_impl<T>::parse(string_view input)	\
    { return parse_number<T>(input); }
CORE_PP_EVAL_MAP(CODE, int8, int16, int32, int64,
		 uint8, uint16, uint32, uint64,
		 real32, real64, real128);
#undef CODE

}; // detail

}; // end ns core
