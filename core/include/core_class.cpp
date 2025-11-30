
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
            case Move::down :
                --_column;

            case Move::right :
                ++_row;
                    
            case Move::left:
                --_row;
            default :
            ;
        }
    }
    return;
}

Grid::Grid(unsigned int nrow=1, unsigned int ncol=1)
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
    for(unsigned int f_row=full_rows.size()-1; f_row>=full_rows[0]; --f_row)
    {
        for(unsigned int row=f_row; row<(*this).row_size()-1; ++row)
        {
            matrix[row]=matrix[row+1];
        }
        matrix[(*this).row_size()-1]=std::vector<Cell>((*this).row_size());
    }
    return;
}

std::ostream& operator<<(std::ostream o, Grid board)
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
    _blocks.clear();

    switch(_type)
    {
        case PieceType::I:
            _blocks = { {0,0}, {-1,0}, {1,0}, {2,0} };
            break;
        case PieceType::O:
            _blocks = { {0,0}, {0,1}, {1,0}, {1,1} };
            break;
        case PieceType::T:
            _blocks = { {0,0}, {0,-1}, {0,1}, {1,0} };
            break;
        case PieceType::J:
            _blocks = { {0,0}, {-1,0}, {1,0}, {1,1} };
            break;
        case PieceType::L:
            _blocks = { {0,0}, {-1,0}, {1,0}, {1,-1} };
            break;
        case PieceType::S:
            _blocks = { {0,0}, {0,1}, {1,0}, {1,-1} };
            break;
        case PieceType::Z:
            _blocks = { {0,0}, {0,-1}, {1,0}, {1,1} };
            break;
    }

    int dr = static_cast<int>(pivotRow);
    int dc = static_cast<int>(pivotCol);

    if(dr > 0) move(Move::down, dr);
    else if(dr < 0) move(Move::up, -dr);

    if(dc > 0) move(Move::right, dc);
    else if(dc < 0) move(Move::left, -dc);
}


void Piece::move(Move m, unsigned int length)
{
    int dr = 0, dc = 0;
    switch(m)
    {
        case Move::left:  dc = -static_cast<int>(length); break;
        case Move::right: dc = static_cast<int>(length);  break;
        case Move::down:  dr = static_cast<int>(length);  break;
        case Move::up:    dr = -static_cast<int>(length); break;
        default: break;
    }

    for(auto &b : _blocks) {
        b.row() += dr;
        b.column() += dc;
    }
}
void Piece::rotateDirect()
{
    int pr = _blocks[_pivot_idx].row();
    int pc = _blocks[_pivot_idx].column();
    for(auto &b : _blocks)
    {
        int r = static_cast<int>(b.row()) - pr;
        int c = static_cast<int>(b.column()) - pc;
        b.row() = pr + c;
        b.column() = pc - r;
    }
}


void Piece::rotateIndirect()
{
    //
}

void Piece::setPivotPosition(unsigned int row, unsigned int col)
{
    //
}