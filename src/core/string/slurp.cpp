// Copyright (C) 2018, 2019 by Mark Melton
//

#include <fstream>
#include <sstream>
#include "core/string/slurp.h"

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

string slurp_into_string(string_view filename)
{ return slurp_into_string(string{filename}); }

string slurp_into_string(std::istream& is)
{
    std::ostringstream contents;
    contents << is.rdbuf();
    return contents.str();
}

}; // end ns core
