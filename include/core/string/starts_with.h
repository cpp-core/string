// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include "common.h"

namespace core {

bool starts_with(string_view s, string_view prefix) noexcept;
bool starts_with(string_view s, char c) noexcept;

}; // end ns core
