
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