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

#ifndef NLOHMANN_FIFO_MAP_HPP
#define NLOHMANN_FIFO_MAP_HPP

#include <limits>
#include <map>
#include <vector>
#include <functional>
#include <memory>
#include <utility>
#include <cstdlib>
#include <iostream>
#include <algorithm>

/*!
@brief namespace for Niels Lohmann
@see https://github.com/nlohmann
*/
namespace nlohmann
{

template<class Key>
class fifo_map_compare
{
  public:
    fifo_map_compare(std::vector<Key>& k) : keys(k) {}

    bool operator()(const Key& lhs, const Key& rhs) const
    {
        return find_key(lhs) < find_key(rhs);
    }

    void add_key(const Key& key)
    {
        if (find_key(key) == std::numeric_limits<size_t>::max())
        {
            keys.push_back(key);
        }
    }

    void remove_key(const Key& key)
    {
        keys.erase(std::find(keys.begin(), keys.end(), key));
    }

  private:
    std::vector<Key>& keys;

    std::size_t find_key(const Key& key) const
    {
        const auto it = std::find(keys.begin(), keys.end(), key);

        return (it == keys.end()) ?
               std::numeric_limits<size_t>::max() :
               static_cast<std::size_t>(it - keys.begin());
    }
};


template <
    class Key,
    class T,
    class Compare = fifo_map_compare<Key>,
    class Allocator = std::allocator<std::pair<const Key, T>>
    > class fifo_map
{
  public:
    using key_type = Key;
    using mapped_type = T;
    using value_type = std::pair<const Key, T>;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using key_compare = Compare;
    using allocator_type = Allocator;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;

    using internal_map_type = std::map<Key, T, Compare, Allocator>;

    using iterator = typename internal_map_type::iterator;
    using const_iterator = typename internal_map_type::const_iterator;
    using reverse_iterator = typename internal_map_type::reverse_iterator;
    using const_reverse_iterator = typename internal_map_type::const_reverse_iterator;

  public:
    /// default constructor
    fifo_map() : m_keys(), m_compare(m_keys), m_map(m_compare) {}

    template<class InputIterator>
    fifo_map(InputIterator first, InputIterator last)
        : m_keys(), m_compare(m_keys), m_map(m_compare)
    {
        for (auto it = first; it != last; ++it)
        {
            insert(*it);
        }
    }

    fifo_map(std::initializer_list<value_type> init) : fifo_map()
    {
        for (auto x : init)
        {
            insert(x);
        }
    }


    /*
     * Element access
     */

    /// access specified element with bounds checking
    T& at(const Key& key)
    {
        return m_map.at(key);
    }

    /// access specified element with bounds checking
    const T& at(const Key& key) const
    {
        return m_map.at(key);
    }

    /// access specified element
    T& operator[](const Key& key)
    {
        m_compare.add_key(key);
        return m_map[key];
    }

    /// access specified element
    T& operator[](Key&& key)
    {
        m_compare.add_key(key);
        return m_map[key];
    }


    /*
     * Iterators
     */

    /// returns an iterator to the beginning
    iterator begin()
    {
        return m_map.begin();
    }

    /// returns an iterator to the end
    iterator end()
    {
        return m_map.end();
    }

    /// returns an iterator to the beginning
    const_iterator begin() const
    {
        return m_map.begin();
    }

    /// returns an iterator to the end
    const_iterator end() const
    {
        return m_map.end();
    }

    /// returns an iterator to the beginning
    const_iterator cbegin() const
    {
        return m_map.cbegin();
    }

    /// returns an iterator to the end
    const_iterator cend() const
    {
        return m_map.cend();
    }

    /// returns a reverse iterator to the beginning
    reverse_iterator rbegin()
    {
        return m_map.rbegin();
    }

    /// returns a reverse iterator to the end
    reverse_iterator rend()
    {
        return m_map.rend();
    }

    /// returns a reverse iterator to the beginning
    const_reverse_iterator rbegin() const
    {
        return m_map.rbegin();
    }

    /// returns a reverse iterator to the end
    const_reverse_iterator rend() const
    {
        return m_map.rend();
    }

    /// returns a reverse iterator to the beginning
    const_reverse_iterator crbegin() const
    {
        return m_map.crbegin();
    }

    /// returns a reverse iterator to the end
    const_reverse_iterator crend() const
    {
        return m_map.crend();
    }


    /*
     * Capacity
     */

    /// checks whether the container is empty
    bool empty() const noexcept
    {
        return m_map.empty();
    }

    /// returns the number of elements
    size_type size() const noexcept
    {
        return m_map.size();
    }

    /// returns the maximum possible number of elements
    size_type max_size() const noexcept
    {
        return m_map.max_size();
    }


    /*
     * Modifiers
     */

    /// clears the contents
    void clear() noexcept
    {
        m_map.clear();
        m_keys.clear();
    }

    std::pair<iterator, bool> insert(const value_type& value)
    {
        m_compare.add_key(value.first);
        return m_map.insert(value);
    }

    template<class P>
    std::pair<iterator, bool> insert( P&& value )
    {
        m_compare.add_key(value.first);
        return m_map.insert(value);
    }

    iterator insert(const_iterator hint, const value_type& value)
    {
        m_compare.add_key(value.first);
        return m_map.insert(hint, value);
    }

    iterator insert(const_iterator hint, value_type&& value)
    {
        m_compare.add_key(value.first);
        return m_map.insert(hint, value);
    }

    template<class InputIt>
    void insert(InputIt first, InputIt last)
    {
        for (const_iterator it = first; it != last; ++it)
        {
            m_compare.add_key(it->first);
        }

        m_map.insert(first, last);
    }

    void insert(std::initializer_list<value_type> ilist)
    {
        for (auto value : ilist)
        {
            m_compare.add_key(value.first);
        }

        m_map.insert(ilist);
    }

    /// remove element at position
    iterator erase(const_iterator pos)
    {
        m_compare.remove_key(pos->first);
        return m_map.erase(pos);
    }

    /// remove elements in range
    iterator erase(const_iterator first, const_iterator last)
    {
        for (const_iterator it = first; it != last; ++it)
        {
            m_compare.remove_key(it->first);
        }

        return m_map.erase(first, last);
    }

    /// remove elements with key
    size_type erase(const key_type& key)
    {
        size_type res = m_map.erase(key);

        if (res > 0)
        {
            m_compare.remove_key(key);
        }

        return res;
    }

    /// swaps the contents
    void swap(fifo_map& other)
    {
        std::swap(m_map, other.m_map);
        std::swap(m_compare, other.m_compare);
        std::swap(m_keys, other.m_keys);
    }


    /*
     * Lookup
     */

    /// returns the number of elements matching specific key
    size_type count(const Key& key) const
    {
        return m_map.count(key);
    }

    /// finds element with specific key
    iterator find(const Key& key)
    {
        return m_map.find(key);
    }

    /// finds element with specific key
    const_iterator find(const Key& key) const
    {
        return m_map.find(key);
    }

    /// returns range of elements matching a specific key
    std::pair<iterator, iterator> equal_range(const Key& key)
    {
        return m_map.equal_range(key);
    }

    /// returns range of elements matching a specific key
    std::pair<const_iterator, const_iterator> equal_range(const Key& key) const
    {
        return m_map.equal_range(key);
    }

    /// returns an iterator to the first element not less than the given key
    iterator lower_bound(const Key& key)
    {
        return m_map.lower_bound(key);
    }

    /// returns an iterator to the first element not less than the given key
    const_iterator lower_bound(const Key& key) const
    {
        return m_map.lower_bound(key);
    }

    /// returns an iterator to the first element greater than the given key
    iterator upper_bound(const Key& key)
    {
        return m_map.upper_bound(key);
    }

    /// returns an iterator to the first element greater than the given key
    const_iterator upper_bound(const Key& key) const
    {
        return m_map.upper_bound(key);
    }


    /*
     * Observers
     */

    /// returns the function that compares keys
    key_compare key_comp() const
    {
        return m_compare;
    }


    /*
     * Non-member functions
     */

    friend bool operator==(const fifo_map& lhs, const fifo_map& rhs)
    {
        return lhs.m_map == rhs.m_map;
    }

    friend bool operator!=(const fifo_map& lhs, const fifo_map& rhs)
    {
        return lhs.m_map != rhs.m_map;
    }

    friend bool operator<(const fifo_map& lhs, const fifo_map& rhs)
    {
        return lhs.m_map < rhs.m_map;
    }

    friend bool operator<=(const fifo_map& lhs, const fifo_map& rhs)
    {
        return lhs.m_map <= rhs.m_map;
    }

    friend bool operator>(const fifo_map& lhs, const fifo_map& rhs)
    {
        return lhs.m_map > rhs.m_map;
    }

    friend bool operator>=(const fifo_map& lhs, const fifo_map& rhs)
    {
        return lhs.m_map >= rhs.m_map;
    }

  private:
    /// the keys
    std::vector<Key> m_keys;
    /// the comparison object
    Compare m_compare;
    /// the internal data structure
    internal_map_type m_map;
};

}

#endif
