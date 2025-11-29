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
        Cell(bool iis_full=false) : _is_full{iis_full} {}
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
            std::vector<Cell>  column (ncol);
            for(unsigned int i=0; i<nrow; ++i)
            {
                matrix.push_back(column);
            }  
        } 

        Cell operator()(unsigned int row, unsigned int column) const {return matrix[row][column];} 
        Cell& operator()(unsigned int row, unsigned int column){return matrix[row][column];} 

        unsigned int row_size() const {return matrix.size();}
        unsigned int column_size() const {return matrix[0].size();}

        void clear_full_rows();
        

    private :
        std::vector< std::vector<Cell> > matrix;
        std::vector<unsigned int> get_full_rows() const;
};

#endif