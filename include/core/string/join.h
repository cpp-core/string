// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include "core/common.h"

namespace core {

template<typename InputIterator>
string join(InputIterator begin, InputIterator end, string_view separator, string_view terminator);

template<typename Container>
string join(const Container& strs, string_view separator = ", ", string_view terminator = "");

}; // end ns core
