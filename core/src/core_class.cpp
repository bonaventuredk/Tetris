/**
 * \file core_class.cpp
 * \brief Implementation of class.
 * \author Alexandre Bleuler - Bonaventure Dohemeto
 * \version 1.1
 * \date 08/12/2025
 *
 * This file implements the Block, Cell, Piece, Grid classes.
 */
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> //rand()

#include "core_class.h"

//////////////////////////////
////// Move enum class //////
/////////////////////////////

Move reverse_move(Move move)
{
    switch(move)
    {
        case Move::up : 
            return Move::down;
        case Move::down :
            return Move::up;
        case Move::left :
            return Move::right;
        case Move::right :
            return Move::left;
        case Move::clock_rotation :
            return Move::anticlock_rotation;
        case Move::anticlock_rotation :
            return Move::clock_rotation;
        default :
            return Move::none;
    }
}


/////////////////////////
////// Block class //////
/////////////////////////

void Block::move(Move direction, unsigned int length)
{   
    for(unsigned int step=0; step<length; ++step)
    {
        switch(direction)
        {
            case Move::up :
                --_row;
                break;
            case Move::down :
                ++_row;
                break;
            case Move::right :
                ++_column;
                break;
            case Move::left :
                --_column;
                break;
            default :
                break;
        }
    }
    return;
}

/////////////////////////
////// Piece class //////
/////////////////////////


Piece::Piece(PieceType type, unsigned int pivotRow, unsigned int pivotCol)
: _type(type), _pivot_idx(0)
{
    Block pivot{pivotRow, pivotCol};
    for(unsigned int i=0; i<4; ++i)
    {
        _blocks.push_back(pivot);
    }
    // Initialize the blocks relative to the piece type and pivot
    initializeBlocks();
}


void Piece::initializeBlocks()
{
    
    // Set the blocks and pivot index according to the piece type
    switch(_type)
    {   
        case PieceType::I :
            _blocks[1].move(Move::left,1);
            _blocks[2].move(Move::right,1);
            _blocks[3].move(Move::right,2);
            break;

        case PieceType::O :
            _blocks[1].move(Move::left,1);
            _blocks[2].move(Move::down,1);
            _blocks[3].move(Move::down,1);
            _blocks[3].move(Move::left,1);
            break;

        case PieceType::T :
            _blocks[1].move(Move::left,1);
            _blocks[2].move(Move::right,1);
            _blocks[3].move(Move::down,1);
            break;

        case PieceType::J :
            _blocks[1].move(Move::left,1);
            _blocks[2].move(Move::right,1);
            _blocks[3].move(Move::down,1);
            _blocks[3].move(Move::right,1);
            break;

        case PieceType::L :
            _blocks[1].move(Move::left,1);
            _blocks[2].move(Move::right,1);
            _blocks[3].move(Move::down,1);
            _blocks[3].move(Move::left,1);
            break;

        case PieceType::S :
            _blocks[1].move(Move::right,1);
            _blocks[2].move(Move::down,1);
            _blocks[3].move(Move::down,1);
            _blocks[3].move(Move::left,1);
            break;

        case PieceType::Z :
            _blocks[1].move(Move::left,1);
            _blocks[2].move(Move::down,1);
            _blocks[3].move(Move::down,1);
            _blocks[3].move(Move::right,1);
            break;
    }
}

void Piece::move(Move m, unsigned int length)
{
    switch(m)
    {
        case Move::clock_rotation :
            clock_rotate();
            break;
        case Move::anticlock_rotation :
            anticlock_rotate();
            break;
        default:
            for(Block& block : _blocks){block.move(m, length);}
            break;
    }
}


void Piece::anticlock_rotate()
{
    unsigned int pivot_row = _blocks[_pivot_idx].row();    ///< Pivot row
    unsigned int pivot_col = _blocks[_pivot_idx].column(); ///< Pivot column

    for(auto &b : _blocks)
    {
        unsigned int relative_row = b.row() - pivot_row; ///< Relative row to pivot
        unsigned int relative_column = b.column() - pivot_col; ///< Relative column to pivot
        
        b.row() = pivot_row -  relative_column; ///< New row after clockwise rotation
        b.column() = pivot_col +  relative_row; ///< New column after clockwise rotation
    }
}


void Piece::clock_rotate()
{
    unsigned int pivot_row = _blocks[_pivot_idx].row();    ///< Pivot row
    unsigned int pivot_col = _blocks[_pivot_idx].column(); ///< Pivot column

    for(auto &b : _blocks)
    {
        unsigned int relative_row = b.row() - pivot_row; ///< Relative row to pivot
        unsigned int relative_column = b.column() - pivot_col; ///< Relative column to pivot

        b.row() = pivot_row + relative_column; ///< New row after counterclockwise rotation
        b.column() = pivot_col - relative_row; ///< New column after counterclockwise rotation
    }
}

PieceType createRandomPiece(int col)
{
    PieceType types[] = {
        PieceType::I,
        PieceType::O,
        PieceType::T,
        PieceType::L,
        PieceType::J,
        PieceType::S,
        PieceType::Z
    };

    PieceType randomType = types[rand() % 7];
    return randomType;
}

////////////////////////
////// Grid class //////
////////////////////////


Grid::Grid(unsigned int nrow, unsigned int ncol)
{   
    std::vector<Cell>  column (ncol);
    for(unsigned int i=0; i<nrow; ++i)
    {
        matrix.push_back(column);
    }  
    return;
} 

std::vector<unsigned int> Grid::get_full_rows() const 
{
    std::vector<unsigned int> full_rows;
     bool check;
    for(unsigned int row=0; row<(*this).row_size(); ++row)
    {   
        check=true;
        for(unsigned int column=0; column<(*this).column_size(); ++column)
        {
            if(!(*this)(row,column).is_full())
            {
                check=false;
                break;
            }
        }
        if(check)full_rows.push_back(row);
    }
    return full_rows;
}

Piece Grid::put_piece(PieceType ptype)
{
    Piece piece {ptype, 0, (*this).column_size()/2};
    for(unsigned int block=0; block<piece.size(); ++block)
    {   
        (*this)(piece[block].row(), piece[block].column()).fill(piece[block]);
    }
    return piece;
}

bool Grid::move_piece(Piece& piece, Move move, unsigned int length)
{
    for(unsigned int block=0; block<piece.size(); ++block)
    {   
        (*this)(piece[block].row(), piece[block].column()).clear();
    }
    piece.move(move, length);
    bool is_movable=true;
    for(unsigned int block=0; block<piece.size(); ++block)
    { 
        if(piece[block].row()>(*this).row_size() || piece[block].column()>(*this).column_size() 
            || (*this)(piece[block].row(), piece[block].column()).is_full())
        {
            is_movable=false;
        }
    }
    if(!is_movable)
    {
        piece.move(reverse_move(move));
    }
    for(unsigned int block=0; block<piece.size(); ++block)
    {   
        (*this)(piece[block].row(), piece[block].column()).fill(piece[block]);
    }
    return is_movable;
}

void Grid::update()
{
    std::vector<unsigned int> full_rows= (*this).get_full_rows();
    for(unsigned int f_row : full_rows)
    {
        for(unsigned int row=f_row; row>=1; --row)
        {
            matrix[row]=matrix[row-1];
        }
        matrix[0]=std::vector<Cell>((*this).row_size());
    }
    return;
}

std::string get_grid(Grid grid)
{
    std::string grid_as_str="\n";
    for(unsigned int row=0; row<grid.row_size(); ++row)
    {
        for(unsigned int column=0; column<grid.column_size(); ++column)
        {
            if(grid(row, column).is_full()) grid_as_str+='O';
            else grid_as_str+='.';
        }
        grid_as_str+='\n';
    }
    return grid_as_str;
}
