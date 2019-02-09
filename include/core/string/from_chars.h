// Copyright (C) 2018, 2019 by Mark Melton
//

#pragma once
#include <charconv>

namespace std
{

from_chars_result from_chars(const char *begin, const char *end, float& value)
{
    value = stof(string(begin, end - begin));
    return { end };
}

from_chars_result from_chars(const char *begin, const char *end, double& value)
{
    value = stod(string(begin, end - begin));
    return { end };
}

from_chars_result from_chars(const char *begin, const char *end, long double& value)
{
    value = stold(string(begin, end - begin));
    return { end };
}

};
