// Copyright (C) 2018, 2019 by Mark Melton
//

#pragma once
#include <fstream>
#include <sstream>
#include <string>
#include <cerrno>
#include "core/common.h"

namespace core {

string slurp_into_string(const string& filename)
{
  std::ifstream is(filename, std::ios::in | std::ios::binary);
  if (not is)
      throw(errno);
  
  std::string contents;
  is.seekg(0, std::ios::end);
  contents.resize(is.tellg());
  is.seekg(0, std::ios::beg);
  is.read(&contents[0], contents.size());
  return contents;
}

string slurp_into_string(std::istream& is)
{
    std::ostringstream contents;
    contents << is.rdbuf();
    return contents.str();
}

}; // end ns core
