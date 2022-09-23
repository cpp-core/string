[![Build and Unit Test](https://github.com/cpp-core/string/actions/workflows/build.yaml/badge.svg)](https://github.com/cpp-core/string/actions/workflows/build.yaml)

# String Operations


## At A Glance


## Installation

### Using cxx-depends (Recommended)

    git clone git@github.com:melton1968/cxx-depends
	mkdir cxx-depends/build && cd cxx-depends/build
    CC=clang-mp-11 CXX=clang++-mp-11 cmake -DCMAKE_INSTALL_PREFIX=$HOME/opt -DCORE_FP_TEST=ON ..
	make cxx_core_string_check # Run tests
	make cxx_core_string       # Build and install
	
