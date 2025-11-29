// Classes for core part of the game  

#ifndef CORE_CLASS
#define CORE_CLASS

#include <vector>

enum class Move{up, down, left, right};

class Block
{
    public :
        Block(unsigned int rrow=0, unsigned int ccolumn=0) : _row{rrow}, _column{ccolumn} {}
        unsigned int row() const {return _row;} 
        unsigned int& row() {return _row;}
        unsigned int column() const {return _column;} 
        unsigned int& column() {return _column;}

        void move(Move direction);

    private :
        unsigned int _row;
        unsigned int _column;
};

class Cell
{
    public :
        Cell(bool iis_full=false) : is_full{_iis_full} {}
        bool is_full() const {return _is_full;}
        bool& is_full(){return _is_full;}

    private :
        bool _is_full;
};

class Grid
{   
    public :

        // index (0,0) : case en bas à gauche

        Grid(unsigned int nrow=1, unsigned int ncol=1) 
        {   
            std::vector<Block*>  column (ncol, nullptr);
            for(unsigned int i=0; i<nrow; ++i)
            {
                matrix.push_back(column);
                is_full_rows.push_back(false);
            }  
        } 

        Block* operator()(unsigned int row, unsigned int column) const {return matrix[row][column];} 
        Block*& operator()(unsigned int row, unsigned int column){return matrix[row][column];} 

        unsigned int get_row_size() const {return matrix.size();}
        unsigned int get_column_size() const {return matrix[0].size();}

        std::vector<unsigned int> get_full_rows() const
        {
            std::vector<unsigned int> full_rows;
            {
                for(unsigned int i=0; i<is_full_rows.size(); ++i)
                    if(is_full_rows[i]) full_rows.push_back(i);
            }
            return full_rows;
        }

        void move_piece(Piece piece, Input input);

    private :
        std::vector< std::vector<Block*> > matrix;
        std::vector<bool> is_full_rows;

        void move_block(Block block, Input input);
};

//matrix{std::vector< std::vector<Block*>(ncol, nullptr)> (nrow)}, is_full_row{std::vector<bool> }

#endif