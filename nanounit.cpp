#include "nanounit.h"

namespace
{
    std::vector< nanounit::func_pair > funcs;
}

namespace nanounit
{
    void reg_func( funcp func, const std::string& a)
    {
        funcs.push_back( func_pair(a, func) );
    }

    void run_tests()
    {
        for (std::vector<func_pair>::iterator i = funcs.begin(); i != funcs.end(); i++)
        {
            std::cout << "Running test case '" << i->first << "'\n";
            try
            {
                i->second();
            }
            catch(const TestFailed& e)
            {
                std::cout << "Test case '" << i->first << "' FAILED!" << std::endl
                          << "  " << e.what() << std::endl;
            }
            catch(const std::exception& e)
            {
                std::cout << "Unexpected exception caught in test case '" << i->first
                          << "'! Exception: " << e.what() << std::endl;
            }
            catch(...)
            {
                std::cout << "Unexpected exception caught in test case '" << i->first
                          << "'!" << std::endl;
            }
        }
    }
}

int main(int argc, char** argv)
{
    nanounit::run_tests();
    return 0;
}
