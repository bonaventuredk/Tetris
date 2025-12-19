#include "catch2/catch_test_macros.hpp"
#include "../core/include/core_class.h"
#include <string>

std::string set_empty_grid(unsigned int nrow, unsigned int ncol)
{
    std::string empty_grid= "\n";
    for(unsigned int i=0; i<nrow; ++i)
    {
        for(unsigned int j=0; j<ncol; ++j)
        {
            empty_grid+='.';
        }
        empty_grid+='\n';
    }
    return empty_grid;
}


TEST_CASE("Grid display, Cell::fill(), Cell::clear()")
{
    Grid grid{10,10};
    std::string expected_grid=set_empty_grid(10,10);
    
    REQUIRE(get_grid(grid)==expected_grid);

    expected_grid[1+6*11+5]='O';
    Block block{6,5};
    grid(6,5).fill(block);
    REQUIRE(get_grid(grid)==expected_grid);

    expected_grid[1+6*11+5]='.';
    grid(6,5).clear();
    REQUIRE(get_grid(grid)==expected_grid);
}

TEST_CASE("Grid::put_piece")
{
    Grid grid{10,10};
    std::string expected_grid=set_empty_grid(10,10);

    expected_grid[1+4]='O';
    expected_grid[1+5]='O';
    expected_grid[1+1*11+4]='O';
    expected_grid[1+1*11+5]='O';
    Piece piece=grid.put_piece(PieceType::O);
    REQUIRE(get_grid(grid)==expected_grid);
}

TEST_CASE("Grid::move_piece(PieceType::0), no edge cases")
{
    Grid grid{10,10};
    std::string expected_grid=set_empty_grid(10,10);

    Piece piece=grid.put_piece(PieceType::O);

    bool has_moved=grid.move_piece(piece, Move::down);
    REQUIRE(has_moved);
    expected_grid[1,5]='O';
    expected_grid[1,6]='O';
    expected_grid[2,7]='O';
    expected_grid[2,8]='O';
    REQUIRE(get_grid(grid)==expected_grid);

    has_moved=grid.move_piece(piece, Move::up);
    REQUIRE(has_moved);
    expected_grid[0,5]='O';
    expected_grid[0,6]='O';
    expected_grid[1,7]='O';
    expected_grid[1,8]='O';
    REQUIRE(get_grid(grid)==expected_grid);

    has_moved=grid.move_piece(piece, Move::right);
    REQUIRE(has_moved);
    expected_grid[0,6]='O';
    expected_grid[0,7]='O';
    expected_grid[1,8]='O';
    expected_grid[1,9]='O';
    REQUIRE(get_grid(grid)==expected_grid);

    has_moved=grid.move_piece(piece, Move::left);
    REQUIRE(has_moved);
    expected_grid[0,5]='O';
    expected_grid[0,6]='O';
    expected_grid[1,7]='O';
    expected_grid[1,8]='O';
    REQUIRE(get_grid(grid)==expected_grid);

    has_moved=grid.move_piece(piece, Move::clock_rotation);
    REQUIRE(has_moved);
    REQUIRE(get_grid(grid)==expected_grid);

    has_moved=grid.move_piece(piece, Move::anticlock_rotation);
    REQUIRE(has_moved);
    REQUIRE(get_grid(grid)==expected_grid);
}

TEST_CASE("Grid::update")
{
    Grid grid{10,10};
    std::string expected_grid=set_empty_grid(10,10);
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
    expected_grid[8*11+0]='O';
    expected_grid[9*11+0]='O';
}