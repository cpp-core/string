// Copyright (C) 2017, 2018, 2019, 2020 by Mark Melton
//

#include "core/common.h"
#include "core/string/split.h"

namespace core {

// split -- split input by separators given in delims returning result
// as vector of string_views.
//
// split("", ":") -> [""] #
// split("foo", ":") -> ["foo"]
// split(":foo", ":") -> ["", "foo"]
// split("foo:", ":") -> ["foo", ""]
// split("foo:bar", ":") -> ["foo", "bar"]
//
string_views split(string_view input, string_view delims)
{
    string_views fields;
    split(input, delims, fields);
    return fields;
}

// split_copy -- same as split but returns strings copied from the
// string_views to eliminate the depenendence on the input.
//
strings split_copy(string_view input, string_view delims)
{
    strings fields;
    auto views = split(input, delims);
    for (auto& value : views)
	fields.push_back(string(value));
    return fields;
}

// split -- split input by separators given in delims placing results
// in fields which is grown as necessary.
//
// split("", ":", fields) -> 0 #
// split("foo", ":", fields) -> 1 # fields[0] = foo
// split(":foo", ":", fields) -> 2 # fields[0] = "", fields[1] = "foo"
// split("foo:", ":", fields) -> 2 # fields[0] = "foo", fields[1] = ""
// split("foo:bar", ":", fields) -> 2 # fields[0] = "foo", fields[1] = "bar"
//
size_t split(string_view input, string_view delims, string_views& fields)
{
    // counter and lambda for appending to fields.
    size_t n = 0;
    auto append_field = [&](string_view field)
			{
			    if (n >= fields.size())
				fields.resize(n+1);
			    fields[n++] = field;
			};
	
    const char *ptr = input.begin();
    const char *end = input.end();
    bool trailing_delim = false;
    while (ptr < end)
    {
	// Looks for delimiter or end of string
	const char *begin = ptr;
	while (ptr != end and not (trailing_delim = delims.find(*ptr) != string::npos))
	    ++ptr;

	// Append the found field (possibly zero length)
	append_field(string_view(begin, ptr - begin));

	// Advance to start of next field
	++ptr;
    }

    // If the string ends with a trailing delimiter, append an empty field.
    if (trailing_delim)
	append_field("");

    // Resize the vector to match the actual number of fields found.
    fields.resize(n);
    return n;
}

size_t fast_split(string_view input, char delim, string_views& fields)
{
    auto begin = input.begin();
    auto ptr = begin;
    size_t idx = 0;
    while (*++ptr and idx < fields.size())
	if (*ptr == delim or ptr == input.end())
	{
	    fields[idx++] = string_view{ begin, std::size_t(ptr - begin) };
	    begin = ptr + 1;
	}
    return idx;
}

std::string_view split_first(std::string_view str, std::string_view delim) {
    if (str.empty()) return string_view{};
    else return split(str, delim).front();
}

std::string_view split_last(std::string_view str, std::string_view delim) {
    if (str.empty()) return string_view{};
    else return split(str, delim).back();
}

}; // end ns core
