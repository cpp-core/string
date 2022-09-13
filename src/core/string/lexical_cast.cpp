// Copyright (C) 2017, 2018, 2019, 2021, 2022 by Mark Melton
//

#include <fmt/printf.h>
#include "core/mp/traits/type.h"
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

char lexical_cast_impl<char>::parse(string_view input)
{ return input[0]; }

string lexical_cast_impl<string>::parse(string_view input)
{ return string(input); }

const char* lexical_cast_impl<const char*>::parse(string_view input)
{ return input.begin(); }

template<class T>
T parse_integral(string_view input)
{
    try
    {
	T value{0};
	int base{10};
	const char *start = input.begin();
	
	if ((input.size() > 1) and (input[0] == '0') and
	    ((input[1] == 'x') or input[1] == 'X')) {
	    start += 2;
	    base = 16;
	}
	
	auto r = std::from_chars(start, input.end(), value, base);
	if (r.ptr != input.end())
	    throw lexical_cast_error(input, mp::type_traits<T>::name);
	return value;
    }
    catch (std::invalid_argument const&)
    {
	throw lexical_cast_error(input, mp::type_traits<T>::name);
    }
    catch (std::out_of_range const&)
    {
	throw lexical_cast_error(input, mp::type_traits<T>::name);
    }
}

#define CODE(T)						\
    T lexical_cast_impl<T>::parse(string_view input)	\
    { return parse_integral<T>(input); }
CORE_PP_EVAL_MAP(CODE, int8, int16, int32, int64,
		 uint8, uint16, uint32, uint64);
#undef CODE

template<class T>
T parse_floating_point(string_view input)
{
    try
    {
	T value = 0;
	auto r = std::from_chars(input.begin(), input.end(), value);
	if (r.ptr != input.end())
	    throw lexical_cast_error(input, mp::type_traits<T>::name);
	return value;
    }
    catch (std::invalid_argument const&)
    {
	throw lexical_cast_error(input, mp::type_traits<T>::name);
    }
    catch (std::out_of_range const&)
    {
	throw lexical_cast_error(input, mp::type_traits<T>::name);
    }
}

#define CODE(T)						\
    T lexical_cast_impl<T>::parse(string_view input)	\
    { return parse_floating_point<T>(input); }
CORE_PP_EVAL_MAP(CODE, real32, real64, real128);
#undef CODE

}; // detail

}; // end ns core
