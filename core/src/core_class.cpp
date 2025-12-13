/**
 * \file core_class.cpp
 * \brief Implementation of class.
 * \author Alexandre Bleuler - Bonaventure Dohemeto
 * \version 1.1
 * \date 08/12/2025
 *
 * This file implements the Block, Cell, Piece, Grid class.
 */
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib> //rand()

#include "core_class.h"

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

void Block::move(Move direction, unsigned int length)
{   
    for(unsigned int step=0; step<length; ++step)
    {
        switch(direction)
        {
            case Move::up :
                ++_column;
                break;
            case Move::down :
                --_column;
                break;
            case Move::right :
                ++_row;
                break;
            case Move::left:
                --_row;
                break;
            default :
                break;
        }
    }
    return;
}

Piece::Piece(PieceType type, unsigned int pivotRow, unsigned int pivotCol)
: _type(type), _pivot_idx(0)
{
    // Initialize the blocks relative to the piece type and pivot
    initializeBlocks(pivotRow, pivotCol);
}


void Piece::initializeBlocks(unsigned int pivotRow, unsigned int pivotCol)
{
    // Set the blocks and pivot index according to the piece type
    switch(_type)
    {
        case PieceType::I:
            _blocks = { {1,1}, {0,1}, {2,1}, {3,1} };
            _pivot_idx = 1; 
            break;

        case PieceType::O:
            _blocks = { {1,1}, {1,2}, {2,1}, {2,2} };
            _pivot_idx = 2; 
            break;

        case PieceType::T:
            _blocks = { {1,1}, {1,0}, {1,2}, {2,1} };
            _pivot_idx = 0; 
            break;

        case PieceType::J:
            _blocks = { {1,1}, {0,1}, {2,1}, {2,2} };
            _pivot_idx = 3; 
            break;

        case PieceType::L:
            _blocks = { {1,1}, {0,1}, {2,1}, {2,0} };
            _pivot_idx = 3; 
            break;

        case PieceType::S:
            _blocks = { {1,1}, {1,2}, {2,1}, {2,0} };
            _pivot_idx = 0; 
            break;

        case PieceType::Z:
            _blocks = { {1,1}, {1,0}, {2,1}, {2,2} };
            _pivot_idx = 0;
            break;
    }

    // Move piece to the desired initial position
    move(Move::down, pivotRow);
    move(Move::right, pivotCol);
}

void Piece::move(Move m, unsigned int length)
{
    for(auto &b : _blocks)
    {
        switch(m)
        {
            case Move::left:
                b.column() -= length; ///< Move left by reducing column
                break;

            case Move::right:
                b.column() += length; ///< Move right by increasing column
                break;

            case Move::up:
                b.row() -= length;    ///< Move up by reducing row
                break;

            case Move::down:
                b.row() += length;    ///< Move down by increasing row
                break;

            default:
                break;
        }
    }
}


void Piece::rotateDirect()
{
    unsigned int pr = _blocks[_pivot_idx].row();    ///< Pivot row
    unsigned int pc = _blocks[_pivot_idx].column(); ///< Pivot column

    for(auto &b : _blocks)
    {
        int r = (int)b.row() - (int)pr; ///< Relative row to pivot
        int c = (int)b.column() - (int)pc; ///< Relative column to pivot
        
        int newR = pr + c; ///< New row after clockwise rotation
        int newC = pc - r; ///< New column after clockwise rotation

        b.row() = (unsigned int)newR;
        b.column() = (unsigned int)newC;
    }
}




void Piece::rotateIndirect()
{
    unsigned int pr = _blocks[_pivot_idx].row();    ///< Pivot row
    unsigned int pc = _blocks[_pivot_idx].column(); ///< Pivot column

    for(auto &b : _blocks)
    {
        int r = (int)b.row() - (int)pr; ///< Relative row to pivot
        int c = (int)b.column() - (int)pc; ///< Relative column to pivot

        int newR = pr - c; ///< New row after counterclockwise rotation
        int newC = pc + r; ///< New column after counterclockwise rotation

        b.row() = (unsigned int)newR;
        b.column() = (unsigned int)newC;
    }
}

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

std::string get_grid(Grid board)
{
    std::string print_board;
    for(unsigned int row=0; row<board.row_size(); ++row)
    {
        for(unsigned int column=0; column<board.column_size(); ++column)
        {
            if(board(row, column).is_full()) print_board+='O';
            else print_board+='.';
        }
        print_board+='\n';
    }
    return print_board;
}


Piece createRandomPiece(int col)
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
    return Piece(randomType, 0, col);
}
