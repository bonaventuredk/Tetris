#include "catch2/catch_test_macros.hpp"
#include "core_class.h"
#include <string>


//////////////////////////////// 
//////// Testing Block //////// 
//////////////////////////////

TEST_CASE("Block")
{
    Block block{1,2};

    REQUIRE(block.row()==1);
    REQUIRE(block.column()==2);

    block.move(Move::right);
    REQUIRE(block.column()==3);
    
    block.move(Move::right,2);
    REQUIRE(block.column()==5);

    block.move(Move::left);
    REQUIRE(block.column()==4);

    block.move(Move::up);
    REQUIRE(block.row()==0);

    block.move(Move::down);
    REQUIRE(block.row()==1);
}


///////////////////////////////
////////  Testing grid //////// 
///////////////////////////////

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

/* 
WARNING : empty_grid[1+a*11+b] will correspond to the line a and column b of a tetrix grid.
The beginning 1 correspond to the first '/n' added to ensure convenient display.
11 does refer to the number of elements on a given line (10 cells plus the trailing '\n').
*/


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

TEST_CASE("Grid::put_piece, O type")
{
    Grid grid{10,10};
    std::string expected_grid=set_empty_grid(10,10);

    expected_grid[1+0*11+4]='O';
    expected_grid[1+0*11+5]='O';
    expected_grid[1+1*11+4]='O';
    expected_grid[1+1*11+5]='O';
    Piece piece=grid.put_piece(PieceType::O);
    REQUIRE(get_grid(grid)==expected_grid);
}


TEST_CASE("Grid::put_piece, I type")
{
    Grid grid{10,10};
    std::string expected_grid=set_empty_grid(10,10);

    expected_grid[1+0*11+3]='O';
    expected_grid[1+0*11+4]='O';
    expected_grid[1+0*11+5]='O';
    expected_grid[1+0*11+6]='O';
    Piece piece=grid.put_piece(PieceType::I);
    REQUIRE(get_grid(grid)==expected_grid);
}

TEST_CASE("Grid::put_piece, S type")
{
    Grid grid{10,10};
    std::string expected_grid=set_empty_grid(10,10);

    expected_grid[1+0*11+5]='O';
    expected_grid[1+0*11+6]='O';
    expected_grid[1+1*11+5]='O';
    expected_grid[1+1*11+4]='O';
    Piece piece=grid.put_piece(PieceType::S);
    REQUIRE(get_grid(grid)==expected_grid);
}

TEST_CASE("Grid::put_piece, Z type")
{
    Grid grid{10,10};
    std::string expected_grid=set_empty_grid(10,10);

    expected_grid[1+0*11+4]='O';
    expected_grid[1+0*11+5]='O';
    expected_grid[1+1*11+5]='O';
    expected_grid[1+1*11+6]='O';
    Piece piece=grid.put_piece(PieceType::Z);
    REQUIRE(get_grid(grid)==expected_grid);
}

TEST_CASE("Grid::put_piece, L type")
{
    Grid grid{10,10};
    std::string expected_grid=set_empty_grid(10,10);

    expected_grid[1+0*11+4]='O';
    expected_grid[1+0*11+5]='O';
    expected_grid[1+0*11+6]='O';
    expected_grid[1+1*11+4]='O';
    Piece piece=grid.put_piece(PieceType::L);
    REQUIRE(get_grid(grid)==expected_grid);
}

TEST_CASE("Grid::put_piece, J type")
{
    Grid grid{10,10};
    std::string expected_grid=set_empty_grid(10,10);

    expected_grid[1+0*11+4]='O';
    expected_grid[1+0*11+5]='O';
    expected_grid[1+0*11+6]='O';
    expected_grid[1+1*11+6]='O';
    Piece piece=grid.put_piece(PieceType::J);
    REQUIRE(get_grid(grid)==expected_grid);
}

TEST_CASE("Grid::put_piece, T type")
{
    Grid grid{10,10};
    std::string expected_grid=set_empty_grid(10,10);

    expected_grid[1+0*11+4]='O';
    expected_grid[1+0*11+5]='O';
    expected_grid[1+0*11+6]='O';
    expected_grid[1+1*11+5]='O';
    Piece piece=grid.put_piece(PieceType::T);
    REQUIRE(get_grid(grid)==expected_grid);
}

TEST_CASE("Grid::move_piece, O type, no edge cases")
{
    Grid grid{10,10};
    std::string expected_grid=set_empty_grid(10,10);

    Piece piece=grid.put_piece(PieceType::O);

    bool has_moved=grid.move_piece(piece, Move::down);
    REQUIRE(has_moved==true);
    expected_grid[1+1*11+4]='O';
    expected_grid[1+1*11+5]='O';
    expected_grid[1+2*11+4]='O';
    expected_grid[1+2*11+5]='O';
    REQUIRE(get_grid(grid)==expected_grid);

    expected_grid=set_empty_grid(10,10);
    has_moved=grid.move_piece(piece, Move::up);
    REQUIRE(has_moved==true);
    expected_grid[1+0*11+4]='O';
    expected_grid[1+0*11+5]='O';
    expected_grid[1+1*11+4]='O';
    expected_grid[1+1*11+5]='O';
    REQUIRE(get_grid(grid)==expected_grid);

    expected_grid=set_empty_grid(10,10);
    has_moved=grid.move_piece(piece, Move::right);
    REQUIRE(has_moved==true);
    expected_grid[1+0*11+5]='O';
    expected_grid[1+0*11+6]='O';
    expected_grid[1+1*11+5]='O';
    expected_grid[1+1*11+6]='O';
    REQUIRE(get_grid(grid)==expected_grid);

    expected_grid=set_empty_grid(10,10);
    has_moved=grid.move_piece(piece, Move::left);
    REQUIRE(has_moved==true);
    expected_grid[1+0*11+4]='O';
    expected_grid[1+0*11+5]='O';
    expected_grid[1+1*11+4]='O';
    expected_grid[1+1*11+5]='O';
    REQUIRE(get_grid(grid)==expected_grid);


    expected_grid=set_empty_grid(10,10);
    has_moved=grid.move_piece(piece, Move::down);
    has_moved=grid.move_piece(piece, Move::clock_rotation);
    REQUIRE(has_moved==true);
    expected_grid[1+0*11+4]='O';
    expected_grid[1+0*11+5]='O';
    expected_grid[1+1*11+4]='O';
    expected_grid[1+1*11+5]='O';
    REQUIRE(get_grid(grid)==expected_grid);

    expected_grid=set_empty_grid(10,10);
    has_moved=grid.move_piece(piece, Move::anticlock_rotation);
    REQUIRE(has_moved==true);
    expected_grid[1+1*11+4]='O';
    expected_grid[1+1*11+5]='O';
    expected_grid[1+2*11+4]='O';
    expected_grid[1+2*11+5]='O';
    REQUIRE(get_grid(grid)==expected_grid);
}

TEST_CASE("Grid::move_piece, I type, edge cases")
{
    Grid grid{10,10};
    std::string expected_grid=set_empty_grid(10,10);
    expected_grid[1+0*11+3]='O';
    expected_grid[1+0*11+4]='O';
    expected_grid[1+0*11+5]='O';
    expected_grid[1+0*11+6]='O';
    Piece piece=grid.put_piece(PieceType::I);
    bool has_moved;

    has_moved=grid.move_piece(piece, Move::right, 4);
    REQUIRE(has_moved==false);
    REQUIRE(get_grid(grid)==expected_grid);

    has_moved=grid.move_piece(piece, Move::left, 20);
    REQUIRE(has_moved==false);
    REQUIRE(get_grid(grid)==expected_grid);

    has_moved=grid.move_piece(piece, Move::up, 20);
    REQUIRE(has_moved==false);
    REQUIRE(get_grid(grid)==expected_grid);

    has_moved=grid.move_piece(piece, Move::down, 20);
    REQUIRE(has_moved==false);
    REQUIRE(get_grid(grid)==expected_grid);

    expected_grid=set_empty_grid(10,10);
    has_moved=grid.move_piece(piece, Move::right, 3);
    expected_grid[1+0*11+6]='O';
    expected_grid[1+0*11+7]='O';
    expected_grid[1+0*11+8]='O';
    expected_grid[1+0*11+9]='O';
    has_moved=grid.move_piece(piece, Move::clock_rotation);
    REQUIRE(has_moved==false);
    REQUIRE(get_grid(grid)==expected_grid);

    has_moved=grid.move_piece(piece, Move::anticlock_rotation);
    REQUIRE(has_moved==false);
    REQUIRE(get_grid(grid)==expected_grid);
    has_moved=grid.move_piece(piece, Move::left, 3);

    expected_grid=set_empty_grid(10,10);
    has_moved=grid.move_piece(piece, Move::down, 1);
    has_moved=grid.move_piece(piece, Move::anticlock_rotation);
    has_moved=grid.move_piece(piece, Move::right, 4);
    expected_grid[1+0*11+9]='O';
    expected_grid[1+1*11+9]='O';
    expected_grid[1+2*11+9]='O';
    expected_grid[1+3*11+9]='O';
    
    has_moved=grid.move_piece(piece, Move::clock_rotation);
    REQUIRE(has_moved==false);
    REQUIRE(get_grid(grid)==expected_grid);

    has_moved=grid.move_piece(piece, Move::anticlock_rotation);
    REQUIRE(has_moved==false);
    REQUIRE(get_grid(grid)==expected_grid);
    has_moved=grid.move_piece(piece, Move::left, 4);
    has_moved=grid.move_piece(piece, Move::clock_rotation);
    has_moved=grid.move_piece(piece, Move::up, 1);

    expected_grid=set_empty_grid(10,10);
    has_moved=grid.move_piece(piece, Move::down, 2);
    expected_grid[1+2*11+3]='O';
    expected_grid[1+2*11+4]='O';
    expected_grid[1+2*11+5]='O';
    expected_grid[1+2*11+6]='O';
    Piece piece_wall=grid.put_piece(PieceType::S);
    expected_grid[1+0*11+5]='O';
    expected_grid[1+0*11+6]='O';
    expected_grid[1+1*11+5]='O';
    expected_grid[1+1*11+4]='O';
    has_moved=grid.move_piece(piece, Move::up, 1);
    REQUIRE(has_moved==false);
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
        grid(9,j).fill(block);
    }
    grid(8,0).fill(block);
    grid(5,0).fill(block);
    grid.update();
    expected_grid[1+8*11+0]='O';
    expected_grid[1+9*11+0]='O';
    REQUIRE(get_grid(grid)==expected_grid);
}