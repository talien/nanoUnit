/* Author: Viktor Tusa, 2012 */
/*  This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.*/

#ifndef NANO_UNIT_H_
#define NANO_UNIT_H_

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>

namespace nanounit
{
    enum test_mode
    {
        TEST_EQUAL,
        TEST_NON_EQUAL,
        TEST_ASSERT
    };

    // static bool _nanounit_catched = false;

    template<class A>
    void test_equal_impl(A actual, A expected, int mode, const char* func, const char* filename, const int line)
    {
        std::ostringstream ss;
        switch (mode)
        {
            case nanounit::TEST_EQUAL:
                if (expected != actual)
                {
                    ss << "Equality failed, actual='" << actual << "', expected='" << expected << "' in " << func << " " << filename << ":" << line;
                    throw ss.str();
                }
                std::cout << filename << ":" << line << ": Equality passed." << std::endl;
                break;
            case nanounit::TEST_NON_EQUAL:
                if (expected == actual)
                {
                    ss << "Inequality failed, actual='" << actual << "', not expected='" << expected << "' in " << func << " " << filename << ":" << line;
                    throw ss.str();
                }
                std::cout << filename << ":" << line << ": Inequality passed." << std::endl;
                break;
            case nanounit::TEST_ASSERT:
                if (expected != actual)
                {
                    ss << "Assertion failed, in " << func << " " << filename << ":" << line;
                    throw ss.str();
                }
                std::cout << filename << ":" << line << ": Assertion passed." << std::endl;
                break;
        }
    }

#define test_equal(type, actual, expected) nanounit::test_equal_impl<type>(actual, expected, nanounit::TEST_EQUAL, __PRETTY_FUNCTION__, __FILE__, __LINE__);
#define test_not_equal(type, actual, expected) nanounit::test_equal_impl<type>(actual, expected, nanounit::TEST_NON_EQUAL, __PRETTY_FUNCTION__, __FILE__, __LINE__);
#define test_assert(expr) nanounit::test_equal_impl<bool>(expr, true, nanounit::TEST_ASSERT, __PRETTY_FUNCTION__, __FILE__, __LINE__);

#define test_TRY do { bool _nanounit_catched = false; try {
#define test_CATCH(type) } catch (const type &e) { std::cout << "Exception expected: " << e << std::endl; _nanounit_catched = true; } if (!_nanounit_catched) { throw std::string("Exception expected, but not happened!");} } while(false);

    typedef void (*funcp)(void);
    typedef std::pair<std::string, funcp> func_pair;

    void reg_func( funcp func, std::string a);

    class test
    {
    public:
        test(funcp f, std::string s)
        {
            reg_func(f, s);
        }
    };

#define func_start(name, desc) void name(); nanounit::test test_##name(name, desc);  void name() {
#define func_end }
}

#endif



