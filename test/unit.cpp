/*!
@file
@copyright The code is licensed under the MIT License
           <http://opensource.org/licenses/MIT>,
           Copyright (c) 2015 Niels Lohmann.
@author Niels Lohmann <http://nlohmann.me>
@see https://github.com/nlohmann/fifo_map
*/

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#define private public
#include "fifo_map.hpp"

using nlohmann::fifo_map;

#include <string>

    TEST_CASE("element access")
    {
        fifo_map<std::string, int> m = {{"C", 1}, {"A", 2}, {"B", 3}};
        const fifo_map<std::string, int> mc = m;
        
        SECTION("at")
        {
            CHECK(m.at("C") == 1);
            CHECK(m.at("A") == 2);
            CHECK(m.at("B") == 3);
            
            CHECK_THROWS_AS(m.at("Z"), std::out_of_range);

            CHECK(mc.at("C") == 1);
            CHECK(mc.at("A") == 2);
            CHECK(mc.at("B") == 3);
            
            CHECK_THROWS_AS(mc.at("Z"), std::out_of_range);
        }
        
        SECTION("operator[]")
        {
            CHECK(m["C"] == 1);
            CHECK(m["A"] == 2);
            CHECK(m["B"] == 3);
            
            CHECK_NOTHROW(m["Z"]);
            CHECK(m["Z"] == 0);
        }
    }
    
    TEST_CASE("iterators")
    {
        fifo_map<std::string, int> m = {{"C", 1}, {"A", 2}, {"B", 3}};
        const fifo_map<std::string, int> mc = m;
        
        SECTION("begin/end with nonconst object")
        {
            fifo_map<std::string, int>::iterator it = m.begin();
            CHECK(it->first == "C");
            CHECK(it->second == 1);
            ++it;
            CHECK(it->first == "A");
            CHECK(it->second == 2);
            ++it;
            CHECK(it->first == "B");
            CHECK(it->second == 3);
            ++it;
            CHECK(it == m.end());
        }

        SECTION("begin/end with const object")
        {
            fifo_map<std::string, int>::const_iterator it = mc.begin();
            CHECK(it->first == "C");
            CHECK(it->second == 1);
            ++it;
            CHECK(it->first == "A");
            CHECK(it->second == 2);
            ++it;
            CHECK(it->first == "B");
            CHECK(it->second == 3);
            ++it;
            CHECK(it == mc.end());
        }

        SECTION("cbegin/cend with nonconst object")
        {
            fifo_map<std::string, int>::const_iterator it = m.cbegin();
            CHECK(it->first == "C");
            CHECK(it->second == 1);
            ++it;
            CHECK(it->first == "A");
            CHECK(it->second == 2);
            ++it;
            CHECK(it->first == "B");
            CHECK(it->second == 3);
            ++it;
            CHECK(it == m.cend());
        }

        SECTION("cbegin/cend with const object")
        {
            fifo_map<std::string, int>::const_iterator it = mc.cbegin();
            CHECK(it->first == "C");
            CHECK(it->second == 1);
            ++it;
            CHECK(it->first == "A");
            CHECK(it->second == 2);
            ++it;
            CHECK(it->first == "B");
            CHECK(it->second == 3);
            ++it;
            CHECK(it == mc.cend());
        }
}