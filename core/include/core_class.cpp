
#include <iostream>
#include <vector>
#include <string>

#include "core_class.h"

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

void Grid::update()
{
    std::vector<unsigned int> full_rows= (*this).get_full_rows();
    for(unsigned int f_row : full_rows)
    {
        for(unsigned int row = f_row; row>=1; --row)
        {
            matrix[row]=matrix[row-1];
        }
        matrix[0]=std::vector<Cell>((*this).row_size());
    }
    return;
}

std::ostream& operator<<(std::ostream& o, Grid board)
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
    o << print_board;
    return o;
}


//For Piece class 

Piece::Piece(PieceType type, unsigned int pivotRow, unsigned int pivotCol)
: _type(type), _pivot_idx(0)
{
    initializeBlocks(pivotRow, pivotCol);
}


void Piece::initializeBlocks(unsigned int pivotRow, unsigned int pivotCol)
{
    switch(_type)
    {
        case PieceType::I:
       
        _blocks = { {1,1}, {0,1}, {2,1}, {3,1} };
        break;

        case PieceType::O:
        _blocks = { {1,1}, {1,2}, {2,1}, {2,2} };
        break;

        case PieceType::T:
        
        _blocks = { {1,1}, {1,0}, {1,2}, {2,1} };
        break;

        case PieceType::J:
        
        _blocks = { {1,1}, {0,1}, {2,1}, {2,2} };
        break;

        case PieceType::L:
        
        _blocks = { {1,1}, {0,1}, {2,1}, {2,0} };
        break;

        case PieceType::S:
        
        _blocks = { {1,1}, {1,2}, {2,1}, {2,0} };
        break;

        case PieceType::Z:
        
        _blocks = { {1,1}, {1,0}, {2,1}, {2,2} };
        break;
    }

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
            b.column() -= length;
            break;

            case Move::right:
            b.column() += length;
            break;

            case Move::up:
            b.row() -= length;
            break;

            case Move::down:
            b.row() += length;
            break;

            default:
            break;
        }
    }
}

void Piece::rotateDirect()
{
    unsigned int pr = _blocks[_pivot_idx].row();
    unsigned int pc = _blocks[_pivot_idx].column();

    for(auto &b : _blocks)
    {
        int r = (int)b.row() - (int)pr;
        int c = (int)b.column() - (int)pc;
        
        int newR = pr + c;
        int newC = pc - r;

        b.row() = (unsigned int)newR;
        b.column() = (unsigned int)newC;
    }
}


void Piece::rotateIndirect()
{
    // 3 rotations 
    rotateDirect();
    rotateDirect();
    rotateDirect();
}

