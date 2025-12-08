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

class Piece
{
    public:
      /*!
       * \brief Constructor
       *
       * Initializes a piece with a type and a pivot position
       *
       * \param type : type of the piece (I, O, T, etc.)
       * \param pivotRow : initial row of the pivot
       * \param pivotCol : initial column of the pivot
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

      /*!
       * \brief Moves the piece
       *
       * Moves the piece in the specified direction
       *
       * \param m : movement direction
       * \param length : number of cells to move (default 1)
       */
      void move(Move m, unsigned int length = 1);

      /*!
       * \brief Clockwise rotation
       *
       * Rotates the piece clockwise around the pivot
       */
      void rotateDirect();

      /*!
       * \brief Counter-clockwise rotation
       *
       * Rotates the piece counter-clockwise around the pivot
       */
      void rotateIndirect();

private:
      PieceType _type; /*!< Type of the piece */
      std::vector<Block> _blocks; /*!< Blocks composing the piece */
      unsigned int _pivot_idx; /*!< Index of the pivot block */

      /*!
       * \brief Initializes the blocks
       *
       * Sets up the positions of the blocks based on the pivot
       *
       * \param pivotRow : row of the pivot
       * \param pivotCol : column of the pivot
       */
      void initializeBlocks(unsigned int pivotRow, unsigned int pivotCol);
};

#endif
