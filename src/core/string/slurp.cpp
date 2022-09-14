// Copyright (C) 2018, 2019, 2022 by Mark Melton
//

#include <fstream>
#include <sstream>
#include "core/string/slurp.h"

namespace core {

std::string slurp_into_string(const std::string& filename)
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

std::string slurp_into_string(std::string_view filename)
{ return slurp_into_string(std::string{filename}); }

std::string slurp_into_string(std::istream& is)
{
    std::ostringstream contents;
    contents << is.rdbuf();
    return contents.str();
}

}; // end ns core
