#include "catch2/catch_test_macros.hpp"
#include "../core/core_class.h"
#include <string>

TEST_CASE("Grid display", "[azdjazifjaziofjio]")
{
    Grid grid{10,10};
    std::string expected_board;
    for(unsigned int i=10; i<10; ++i)
    {
        for(unsigned int j=10, j<10; ++j)
        {
            expected_board+='.';
        }
        expected_board+='\n';
    }
    REQUIRE(get_grid(grid)==expected_board)
}
