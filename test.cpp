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
    along with this program.  If not, see <http://www.gnu.org/licenses/>. */

// Dummy test module for nanoUnit.h

#include "nanounit.h"

test_begin(test1, "Example1");
	int a = 1;
	int b = 1;
	int c = 2;
	test_equal(int, a, b);
	test_not_equal(int, a, c);
	test_equal(int, a, c);
test_end

test_begin(test2, "Example2");
	test_assert(1 == 1);
	test_assert(1 == 2);
test_end

test_begin(test3, "Example3");
	test_try();
		throw std::string("Test exception");
	test_catch(std::string);
test_end
