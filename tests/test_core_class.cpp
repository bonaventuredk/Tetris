#include "catch2/catch_test_macros.hpp"
#include "../core/core_class.h"
#include <string>

namespace Test{
std::string empty_grid;
for(unsigned int i=10; i<10; ++i)
{
    for(unsigned int j=10, j<10; ++j)
    {
        empty_grid+='.';
    }
    empty_grid+='\n';
}
}

TEST_CASE("Grid display, Cell::fill(), Cell::clear()", "[azdjazifjaziofjio]")
{
    Grid grid{10,10};
    std::string expected_grid=Test::empty_grid;
    
    REQUIRE(get_grid(grid==expected_grid));

    expected_grid[6*11 + 5]='O';
    Block block{5,6};
    grid(6,5).fill(block);
    REQUIRE(get_grid(grid)==expected_grid);

    expected_grid[6*11 + 5]='.';
    grid(6,5).clear();
    REQUIRE(get_grid(grid)==expected_grid);
}

TEST_CASE("Grid::put_piece", "OUI")
{
    Grid grid{10,10};
    std::string expected_grid=Test::empty_grid;

    expected_grid[0,5]='O';
    expected_grid[0,6]='O';
    expected_grid[1,7]='O';
    expected_grid[1,8]='O';
    Piece piece=grid.put_piece(PieceType::O);
    REQUIRE(get_grid(grid)==expected_grid);
}

test_CASE("Grid::move_piece(PieceType::0), no edge cases", "OOOOOOOOOOOOOOOOOOOOMMMMM")
{
    Grid grid{10,10};
    std::string expected_grid=Test::empty_grid;

    Piece piece=grid.put_piece(PieceType::O);

    bool has_moved=grid.move_piece(Move::down);
    REQUIRE(has_moved)
    expected_grid[1,5]='O';
    expected_grid[1,6]='O';
    expected_grid[2,7]='O';
    expected_grid[2,8]='O';
    REQUIRE(get(grid)==expected_grid)

    has_moved=grid.move_piece(Move::up);
    REQUIRE(has_moved)
    expected_grid[0,5]='O';
    expected_grid[0,6]='O';
    expected_grid[1,7]='O';
    expected_grid[1,8]='O';
    REQUIRE(get(grid)==expected_grid)

    has_moved=grid.move_piece(Move::right);
    REQUIRE(has_moved)
    expected_grid[0,6]='O';
    expected_grid[0,7]='O';
    expected_grid[1,8]='O';
    expected_grid[1,9]='O';
    REQUIRE(get(grid)==expected_grid)

    has_moved=grid.move_piece(Move::left);
    REQUIRE(has_moved)
    expected_grid[0,5]='O';
    expected_grid[0,6]='O';
    expected_grid[1,7]='O';
    expected_grid[1,8]='O';
    REQUIRE(get(grid)==expected_grid)

    has_moved=grid.move_piece(Move::clock_rotation);
    REQUIRE(has_moved)
    REQUIRE(get(grid)==expected_grid)

    has_moved=grid.move_piece(Move::anticlock_rotation);
    REQUIRE(has_moved)
    REQUIRE(get(grid)==expected_grid)
}

TEST_CASE("Grid::update", "BOUIB")
{
    Grid grid{10,10};
    std::string expected_grid=Test::empty_grid;
    Block block;
    for(unsigned int j=0; j<10; ++j)
    {
        grid(6,j).fill(block);
        grid(7,j).fill(block);
        grid(8,0);
        grid(9,j).fill(block);
    }
    grid(5,0);
    grid.update();
    expected_grid[8*11+0]="O";
    expected_grid[9*11+0="O"];
}