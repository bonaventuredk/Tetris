// Classes for core part of the game  

#ifndef CORE_CLASS
#define CORE_CLASS

#include <vector>

enum class Move{up, down, left, right, direct_rotation, indirect_rotation};

class Block
{
    public :
        Block(unsigned int rrow=0, unsigned int ccolumn=0) : _row{rrow}, _column{ccolumn} {}
        unsigned int row() const {return _row;} 
        unsigned int& row() {return _row;}
        unsigned int column() const {return _column;} 
        unsigned int& column() {return _column;}
        void move(Move direction, unsigned int length=1);

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
        Grid(unsigned int nrow=1, unsigned int ncol=1);
        Cell operator()(unsigned int row, unsigned int column) const {return matrix[row][column];} 
        Cell& operator()(unsigned int row, unsigned int column){return matrix[row][column];} 
        unsigned int row_size() const {return matrix.size();}
        unsigned int column_size() const {return matrix[0].size();}
        void update();

    private :
        std::vector< std::vector<Cell> > matrix;
        std::vector<unsigned int> get_full_rows() const;
};

enum class PieceType { I, O, T, L, J, S, Z };

class Piece {
public:
    Piece(PieceType type = PieceType::I, unsigned int pivotRow = 0, unsigned int pivotCol = 0);

    PieceType type() const { return _type; }
    unsigned int pivot_row() const { return _blocks[_pivot_idx].row(); }
    unsigned int pivot_col() const { return _blocks[_pivot_idx].column(); }

    std::vector<Block> getBlocks() const { return _blocks; }
    unsigned int size() const { return static_cast<unsigned int>(_blocks.size()); }

    void move(Move m);
    void rotateDirect();   
    void rotateIndirect();
    void setPivotPosition(unsigned int row, unsigned int col);

private:
    PieceType _type;
    std::vector<Block> _blocks;   
    unsigned int _pivot_idx;     

    void initializeBlocks(unsigned int pivotRow, unsigned int pivotCol);
};
#endif