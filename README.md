[![Build Status](https://travis-ci.org/nlohmann/fifo_map.svg?branch=master)](https://travis-ci.org/nlohmann/fifo_map)
[![Build status](https://ci.appveyor.com/api/projects/status/ilx8h73gq2gcfbmf?svg=true)](https://ci.appveyor.com/project/nlohmann/fifo-map)
[![Coverage Status](https://img.shields.io/coveralls/nlohmann/fifo_map.svg)](https://coveralls.io/r/nlohmann/fifo_map)
[![Try online](https://img.shields.io/badge/try-online-blue.svg)](http://melpon.org/wandbox/permlink/l2f2Qxhq95qVKRgE)
[![GitHub license](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/nlohmann/fifo_map/master/LICENSE.MIT)
[![Github Releases](https://img.shields.io/github/release/nlohmann/fifo_map.svg)](https://github.com/nlohmann/fifo_map/releases)
[![Github Issues](https://img.shields.io/github/issues/nlohmann/fifo_map.svg)](http://github.com/nlohmann/fifo_map/issues)

# `fifo_map` – a FIFO-ordered associative container for C++

## Overview

C++ allows to defined associative containers such as `std::map`. The values are ordered according to their keys and an ordering relation. The `fifo_map` is an associative container which uses **the order in which keys were inserted to the container** as ordering relation.

As it has the same interface than `std::map`, it can be used as drop-in replacement. The code is header-only (see file [src/fifo_map.hpp](https://github.com/nlohmann/fifo_map/blob/master/src/fifo_map.hpp)) and only relies on the STL.

## Complexity

A `fifo_map` object has the space overhead of:
- one `std::unordered_map<Key, std::size_t>` object to store the key order,
- one pointer to this object in the `Compare` object.

Inserting a value (via `operator[]`, `insert`) and removing a value (`erase`) rely on `std::unordered_map::insert` and `std::unordered_map::erase` which have O(1) average complexity and O(n) worst-case complexity. All other methods have the same performance as the equivalent `std::map` options.

## Example

```cpp
#include "src/fifo_map.hpp"

// for convenience
using nlohmann::fifo_map;

int main() {
    // create fifo_map with template arguments
    fifo_map<int, std::string> m;

    // add elements
    m[2] = "two";
    m[3] = "three";
    m[1] = "one";
    
    // output the map; will print
    // 2: two
    // 3: three
    // 1: one
    for (auto x : m) {
        std::cout << x.first << ": " << x.second << "\n";
    }
    
    // delete an element
    m.erase(2);
    
    // re-add element
    m[2] = "zwei";
    
    // output the map; will print
    // 3: three
    // 1: one
    // 2: zwei
    for (auto x : m) {
        std::cout << x.first << ": " << x.second << "\n";
    }
}
```

[Try this code online.](http://melpon.org/wandbox/permlink/l2f2Qxhq95qVKRgE)

## License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The code is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2015-2017 [Niels Lohmann](http://nlohmann.me)

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

## Execute unit tests

To compile and run the tests, you need to execute

```sh
$ make
$ ./unit

===============================================================================
All tests passed (1286 assertions in 8 test cases)
```

For more information, have a look at the file [.travis.yml](https://github.com/nlohmann/fifo_map/blob/master/.travis.yml).
