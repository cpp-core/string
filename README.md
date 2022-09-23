[![Build and Unit Test](https://github.com/cpp-core/string/actions/workflows/build.yaml/badge.svg)](https://github.com/cpp-core/string/actions/workflows/build.yaml)

# C++ String Library


## At A Glance


## Installation

### Using depends (Recommended)

    git clone https://github.com/cpp-core/depends
	mkdir depends/build && cd depends/build
    CC=clang-mp-11 CXX=clang++-mp-11 cmake -DCMAKE_INSTALL_PREFIX=$HOME/opt -DSTRING_TEST=ON ..
	make string-check # Run tests
	make string       # Build and install
	
