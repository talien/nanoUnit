#include "nanounit.h"
#include <stdexcept>

test_begin(numbers, "Numbers");
    test_assert(1 == 1);
    test_assert(1 == 2);
test_end

test_begin(throwTest1, "Throw wrong exception")
    throw std::runtime_error("fail");
test_end
