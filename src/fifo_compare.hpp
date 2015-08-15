/*
The code is licensed under the MIT License <http://opensource.org/licenses/MIT>:

Copyright (c) 2015 Niels Lohmann.

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef NLOHMANN_FIFO_COMPARE_HPP
#define NLOHMANN_FIFO_COMPARE_HPP

#include <vector>

/*!
@brief namespace for Niels Lohmann
@see https://github.com/nlohmann
*/
namespace nlohmann
{

template<class Key>
class fifo_compare
{
  public:
    /// return whether @a lhs was seen before @a rhs
    bool operator()(const Key& lhs, const Key& rhs) const
    {
        // switch order for correct results when 2nd element is inserted
        return find_or_insert(rhs) > find_or_insert(lhs);
    }

  private:
    /// find index of needle in keys list
    std::size_t find_or_insert(const Key& needle) const
    {
        // find index of needle
        for (std::size_t i = 0; i < keys.size(); ++i)
        {
            if (keys[i] == needle)
            {
                return i;
            }
        }

        // needle not found: insert it and return its index
        keys.push_back(needle);
        return keys.size() + 1;
    }

    /// an ordered list of keys
    mutable std::vector<Key> keys;
};

}

#endif
