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

#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <utility>

enum test_mode
{
    TEST_EQUAL,
    TEST_NON_EQUAL,
    TEST_ASSERT,
};

template<class A> void test_equal_impl(A actual, A expected, int mode, const char* func, const char* filename, const int line)
{
    std::stringstream ss;
    switch (mode)
    {
        case TEST_EQUAL:
            if (expected != actual)
            {
                ss << "Equality failed, actual='" << actual << "', expected='" << expected << "' in " << func << " " << filename << ":" << line;
                throw ss.str();
            }
            std::cout << "Equality passed, actual='" << actual << "', expected='" << expected << "' in " << func << " " << filename << ":" << line << std::endl;
            break;
        case TEST_NON_EQUAL:
            if (expected == actual)
            {
                ss << "Inequality failed, actual='" << actual << "', not expected='" << expected << "' in " << func << " " << filename << ":" << line;
                throw ss.str();
            }
            std::cout << "Inequality passed, actual='" << actual << "', not expected='" << expected << "' in " << func << " " << filename << ":" << line << std::endl;
            break;
        case TEST_ASSERT:
            if (expected != actual)
            {
                ss << "Assertion failed, in " << func << " " << filename << ":" << line;
                throw ss.str();
            }
            std::cout << "Assertion passed, in " << func << " " << filename << ":" << line;
            break;
    }

}


#define test_equal(type, actual, expected) test_equal_impl<type>(actual, expected, TEST_EQUAL, __PRETTY_FUNCTION__, __FILE__, __LINE__);
#define test_not_equal(type, actual, expected) test_equal_impl<type>(actual, expected, TEST_NON_EQUAL, __PRETTY_FUNCTION__, __FILE__, __LINE__);
#define test_assert(expr) test_equal_impl<bool>(expr, true, TEST_ASSERT, __PRETTY_FUNCTION__, __FILE__, __LINE__);

#define test_TRY try {
#define test_CATCH(type) } catch (type e) { std::cout << "Exception expected: " << e << std::endl; }

typedef void (*funcp)(void);
typedef std::pair<std::string, funcp> func_pair;
std::vector< func_pair > funcs;

void reg_func( funcp func, std::string a)
{
    funcs.push_back(func_pair(a,func));
}


class test
{
    public:
        test(funcp f, std::string s)
        {
            reg_func(f, s);
        }
};

#define func_start(name, desc) void name(); test test_##name(name, desc);  void name() {
#define func_end }

void run_tests()
{
    for (std::vector<func_pair>::iterator i = funcs.begin(); i != funcs.end(); i++)
    {
        std::cout << "Running testcase " << i->first << std::endl;
        try
        {
            i->second();
        }
        catch(std::string e)
        {
            std::cout << "Testcase " << i->first << " FAILED!" << std::endl << "  Error message:" << e << std::endl;
        }
    }
}


int main()
{
    run_tests();
}
