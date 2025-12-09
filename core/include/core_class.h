/**
 * \file core_class.h
 * \brief Declaration of core classes for the Tetris.
 * 
 * This file contains the declarations of the fundamental classes
 * of the Tetris logic: Block, Cell, Piece, and Grid.
 *
 * \author Alexandre Bleuler - Bonaventure Dohemeto
 * \version 1.1
 * \date 08/12/2025
 */
#ifndef CORE_CLASS
#define CORE_CLASS

#include <vector>

enum class Move{up, down, left, right, clock_rotation, anticlock_rotation};
enum class PieceType { I, O, T, L, J, S, Z };

Move reverse_move(Move move);

/**
 * @class Block
 * 
 * @brief Class for the block ...

*/
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

        // index (0,0) : case en haut à gauche
        Grid(unsigned int nrow=1, unsigned int ncol=1);
        Cell operator()(unsigned int row, unsigned int column) const {return matrix[row][column];} 
        Cell& operator()(unsigned int row, unsigned int column){return matrix[row][column];} 
        unsigned int row_size() const {return matrix.size();}
        unsigned int column_size() const {return matrix[0].size();}
        void put_piece(PieceType ptype) const;
        void move_piece(Piece& piece, Move move);
        void update();

    private :
        std::vector< std::vector<Cell> > matrix;
        std::vector<unsigned int> get_full_rows() const;
};

/**
 * @class Piece
 * 
 * @brief Tetris pieces description

*/
class Piece
{
    public:
      /**
       * \brief Constructor for a Piece object.
       *
       * Creates a piece of the given type and places it at the initial pivot coordinates.
       *
       * \param type The type of the piece (I, O, T, J, L, S, Z)
       * \param pivotRow The row index of the pivot point
       * \param pivotCol The column index of the pivot point
       */
      Piece(PieceType type = PieceType::I, unsigned int pivotRow = 0, unsigned int pivotCol = 0);

      /*!
       * \brief Returns the type of the piece
       * \return piece type
       */
      PieceType type() const { return _type; }

      /*!
       * \brief Returns the pivot row
       * \return pivot row index
       */
      unsigned int pivot_row() const { return _blocks[_pivot_idx].row(); }

      /*!
       * \brief Returns the pivot column
       * \return pivot column index
       */
      unsigned int pivot_col() const { return _blocks[_pivot_idx].column(); }

      /*!
       * \brief Returns the blocks of the piece
       * \return vector of blocks
       */
      std::vector<Block> getBlocks() const { return _blocks; }

      /*!
       * \brief Returns the number of blocks
       * \return size of the piece
       */
      unsigned int size() const { return static_cast<unsigned int>(_blocks.size()); }

      /**
       * \brief Moves the piece in a given direction.
       *
       * Adjusts the coordinates of all blocks according to the move direction.
       *
       * \param m Direction to move (left, right, up, down)
       * \param length Number of steps to move
       */
      void move(Move m, unsigned int length = 1);

      /**
       * \brief Rotates the piece 90° clockwise around its pivot.
       *
       * Uses the pivot block as the center and rotates all blocks around it.
       * The rotation formula swaps and negates coordinates relative to the pivot.
       */
      void rotateDirect();

      /**
       * \brief Rotates the piece 90° counterclockwise around its pivot.
       *
       * Uses the pivot block as the center and rotates all blocks around it
       * in the opposite direction.
       */
      void rotateIndirect();

private:
      PieceType _type; /*!< Type of the piece */
      std::vector<Block> _blocks; /*!< Blocks composing the piece */
      unsigned int _pivot_idx; /*!< Index of the pivot block */

      /**
       * \brief Initializes the blocks for the piece based on its type.
       *
       * Sets the default shape of the piece and assigns the pivot block index.
       * Moves the piece to the provided pivot coordinates on the grid.
       *
       * \param pivotRow Row index where the pivot block should be placed
       * \param pivotCol Column index where the pivot block should be placed
       */
      void initializeBlocks(unsigned int pivotRow, unsigned int pivotCol);
};

#endif
