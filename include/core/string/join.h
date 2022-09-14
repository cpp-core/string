// Copyright (C) 2019, 2022 by Mark Melton
//

#pragma once
#include <string>

namespace core::str {

template<typename InputIterator>
std::string join(InputIterator begin,
		 InputIterator end,
		 std::string_view separator,
		 std::string_view terminator);

template<typename Container>
std::string join(const Container& strs,
		 std::string_view separator = ", ",
		 std::string_view terminator = "");

}; // end ns core
