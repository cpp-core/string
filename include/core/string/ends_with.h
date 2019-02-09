// Copyright (C) 2019 by Mark Melton
//

#pragma once
#include "core/common.h"

namespace core {

bool ends_with(string_view s, string_view prefix) noexcept;
bool ends_with(string_view s, char c) noexcept;

}; // end ns core

