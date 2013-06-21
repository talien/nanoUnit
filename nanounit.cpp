#include "nanounit.h"

namespace
{
    std::vector< nanounit::func_pair > funcs;
}

namespace nanounit
{
    void reg_func( funcp func, std::string a)
    {
        funcs.push_back( func_pair(a, func) );
    }

    void run_tests()
    {
        for (std::vector<func_pair>::iterator i = funcs.begin(); i != funcs.end(); i++)
        {
            std::cout << "Running test case " << i->first << std::endl;
            try
            {
                i->second();
            }
            catch(std::string e)
            {
                std::cout << "Test case " << i->first << " FAILED!" << std::endl << "  Error message:" << e << std::endl;
            }
            catch(...)
            {
                std::cout << "Unexpected exception caught during testcase!" << std::endl;
            }
        }
    }
}

int main(int argc, char** argv)
{
    nanounit::run_tests();
    return 0;
}
