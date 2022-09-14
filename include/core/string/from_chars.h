// Copyright (C) 2018, 2019, 2022 by Mark Melton
//

#pragma once
#include <charconv>
#include <string>

namespace std
{

from_chars_result from_chars(const char *begin, const char *end, float& value)
{
    value = stof(std::string(begin, end - begin));
    return { end };
}

from_chars_result from_chars(const char *begin, const char *end, double& value)
{
    value = stod(std::string(begin, end - begin));
    return { end };
}

from_chars_result from_chars(const char *begin, const char *end, long double& value)
{
    value = stold(std::string(begin, end - begin));
    return { end };
}

};
