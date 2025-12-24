/**
 * \file core_class.h
 * \brief Header for core's classes.
 * 
 * This file contains the declarations of the fundamental classes
 * of Tetris' logic: Block, Piece, Cell, and Grid.
 *
 * \author Alexandre Bleuler - Bonaventure Dohemeto
 * \version 1.0
 * \date 19/12/2025
 */

#ifndef CORE_CLASS
#define CORE_CLASS


#include <vector>

/**
 * \enum Move
 * \brief An enum class to manipulate in core basic movements of blocks and pieces
 * as they should appear on screen later.
 */

enum class Move{
    up, /**< Upward movement */
    down, /**< Downward movement */
    left, /**< Leftward movement */
    right, /**< Rightward movement */
    clock_rotation, /**< Clockwise rotation */
    anticlock_rotation, /**< Anticlockwise rotation */
    none /**< No movement */
}; 

/**
 * \brief A simple function to get the inverse move from one of the enum class Move.
 * \param move An element of the enum class Move.
 * \return An element of the enum class Move which is the opposite of \b move .
*/

Move reverse_move(Move move);

enum class PieceType { I=0, O=1, T=2, L=3, J=4, S=5, Z=6 };

/**
 * \enum Move
 * \brief An enum class to set the color of a given PieceType.
 * They are mapped through indexes of the enum. 
 */

enum class Color{
    blue=0, /**< Color associated with element number 0 of PieceType (I currently). */
    yellow=1, /**< Color associated with element number 1 of PieceType (O currently). */
    purple=2, /**< Color associated with element number 2 of PieceType (T currently. */
    orange=3, /**< Color associated with element number 3 of PieceType (L currently). */
    pink=4, /**< Color associated with element number 4 of PieceType (J currently). */
    red=5, /**< Color associated with element number 5 of PieceType (S currently). */
    green=6, /**< Color associated with element number 6 of PieceType (Z currently). */
    none=7, /**< Color associated with empty cells of Tetris' grid. */
}; 


/**
 * \class Block
 * \brief A class which creates the entities representing the Tetris' blocks. It's
 * essentially a couple of non negative integer coordinates.
*/

class Block
{
    public :

        /**
         * \brief Constructing the block from abscissa and ordinate specifications.
         * Constructs it with coordinates (0,0) by default.
         * \param rrolumn An unsigned integer corresponding to the abscissa of the block.
         * \param ccolumn An unsigned integer corresponding to the ordinate of the block.
         * \param color The color of the block. It is Color::none by default.
         * \return
        */

        Block(unsigned int rrow=0, unsigned int ccolumn=0, Color color=Color::none) : _row{rrow}, _column{ccolumn}, _color{color} {}

        /**
         * \brief A getter for the attribute _row
         * \param.
         * \return The attribute _row.
        */

        unsigned int row() const {return _row;} 

        /**
         * \brief A setter for the attribute _row.
         * \param
         * \return A reference to the attribute _row.
        */

        unsigned int& row() {return _row;}

        /**
         * \brief A getter for the attribute _column.
         * \param
         * \return The attribute _column.
        */
       
        unsigned int column() const {return _column;} 

        /**
         * \brief A getter for the attribute _column.
         * \param
         * \return The attribute _column.
        */

        unsigned int& column() {return _column;}

        /**
         * \brief A getter for the attribute _column.
         * \param 
         * \return The attribute _column.
        */

        Color color() const {return _color;} 

        /**
         * \brief A setter for the attribute _color.
         * \param
         * \return The attribute _color.
        */

        Color& color() {return _color;}

        /**
         * \brief A getter for the attribute _color.
         * \param 
         * \return The attribute _color.
        */


        void move(Move direction, unsigned int length=1);

    private :
        unsigned int _row; /**< The abscissa of the block. */
        unsigned int _column; /**< The ordinate of the block. */
        Color _color; /**< The color of the block. */
};

/**
 * @class Piece
 * 
 * @brief Tetris pieces description

*/
/**
 * @class Piece
 * @brief Represents a Tetris piece with blocks, type, pivot, and rotation logic.
 *
 * - Initialize blocks for a given piece type at specific pivot coordinates.
 * - Provide access to block positions, pivot, and color.
 * - Support rotation around the pivot (clockwise and counterclockwise).
 * - Support basic movement operations along the grid.
 */
class Piece
{
public:
    /**
     * @brief Constructs a Piece of a given type at the specified pivot coordinates.
     * 
     * The constructor initializes the blocks for the specified piece type and sets
     * the pivot index. The piece is positioned on the grid according to the provided
     * pivot coordinates.
     * 
     * @param type The type of the piece (I, O, T, J, L, S, Z).
     * @param pivotRow Row index of the pivot block (default 0).
     * @param pivotCol Column index of the pivot block (default 0).
     */
    Piece(PieceType type = PieceType::I, unsigned int pivotRow = 0, unsigned int pivotCol = 0);

    /**
     * @brief Returns the type of the piece.
     * @return PieceType enum value representing the piece type.
     */
    PieceType type() const { return _type; }

    /**
     * @brief Returns the row index of the pivot block.
     * 
     * The pivot is the reference block around which rotations are performed.
     * 
     * @return Row index of the pivot block.
     */
    unsigned int pivot_row() const { return _blocks[_pivot_idx].row(); }

    /**
     * @brief Returns the column index of the pivot block.
     * 
     * @return Column index of the pivot block.
     */
    unsigned int pivot_col() const { return _blocks[_pivot_idx].column(); }

    /**
     * @brief Access a block at the specified index.
     * 
     * Provides read-only access to a specific block in the piece.
     * 
     * @param i Index of the block (0 to size()-1).
     * @return Copy of the Block at the given index.
     */
    Block operator[](unsigned int i) const { return _blocks[i]; }

    /**
     * @brief Access a block at the specified index.
     * 
     * Provides read/write access to a specific block in the piece.
     * 
     * @param i Index of the block (0 to size()-1).
     * @return Reference to the Block at the given index.
     */
    Block& operator[](unsigned int i) { return _blocks[i]; }

    /**
     * @brief Returns the color of the piece.
     * 
     * The color is taken from the first block of the piece. All blocks of a piece
     * typically share the same color.
     * 
     * @return Color of the piece.
     */
    Color color() const { return (*this)[0].color(); }

    /**
     * @brief Returns the number of blocks composing the piece.
     * @return Number of blocks (usually 4 for standard Tetris pieces).
     */
    unsigned int size() const { return static_cast<unsigned int>(_blocks.size()); }

    /**
     * @brief Moves or rotates the piece.
     * 
     * Depending on the direction parameter, this function either moves the piece
     * horizontally/vertically or rotates it around its pivot.
     * 
     * @param direction Direction of movement or rotation. Can be:
     *                  - Move::left, Move::right, Move::down for movement
     *                  - Move::clock_rotation for clockwise rotation
     *                  - Move::anticlock_rotation for counterclockwise rotation
     * @param length Number of steps to move (ignored for rotation). Default is 1.
     */
    void move(Move direction, unsigned int length = 1);

private:
    PieceType _type;                  /*!< Type of the piece (I, O, T, J, L, S, Z) */
    std::vector<Block> _blocks;       /*!< Blocks composing the piece */
    unsigned int _pivot_idx;          /*!< Index of the pivot block in _blocks */

    /**
     * @brief Initializes the blocks for the piece based on its type.
     * 
     * Sets the default shape of the piece and determines which block is the pivot.
     * Moves the piece to the provided pivot coordinates on the grid.
     * 
     */
    void initializeBlocks();

    /**
     * @brief Rotates the piece 90° clockwise around its pivot.
     * 
     * Uses the pivot block as the center and rotates all other blocks around it
     * according to standard Tetris rotation rules.
     */
    void clock_rotate();

    /**
     * @brief Rotates the piece 90° counterclockwise around its pivot.
     * 
     * Uses the pivot block as the center and rotates all other blocks around it
     * in the opposite direction of clock_rotate().
     */
    void anticlock_rotate();
};

/**
 * \class Cell
 * \brief A class which creates the entities representing the cells of the Tetris' grid. 
 * A cell contain several informations such as if it is empty or full.
*/

class Cell
{
    public :

        /**
         * \brief Constructs the cell. Initiate it as empty by default.
         * \param iis_full A boolean asserting if the cell should be full.
         * \param ccolor The color that correspond to the cell.
         * \return
        */

        Cell(bool iis_full=false, Color ccolor=Color::none) : _is_full{iis_full}, _color{ccolor} {}

        /**
         * \brief Fills the cell by setting the attribute _is_full to true. Also
         * updates the other attributes accordingly to the block that correspond to the cell.
         * \param block The instance of type Block that correspond to the cell.
         * \return
        */

        void fill(Block& block){_is_full=true;_color=block.color();}

        /**
         * \brief Clears the cell by making it empty. 
         * \param
         * \return
        */

        void clear(){_is_full=false; _color=Color::none;}

        /**
         * \brief Checks if the cell if full.
         * \param
         * \return A boolean asserting if the cell is full. 
        */

        bool is_full() const {return _is_full;};

        /**
         * \brief A getter for the attribute _color.
         * \param
         * \return The attribute _color.
        */

        Color color() const{return _color;}

    private :
        bool _is_full; /**< A boolean indicating if the Cell is full. False by default. */
        Color _color; /**< The color of the block. This is none by default.*/
};

/**
 * \class Grid
 * \brief A class which creates a 2D grid of Cell entities. It is actualised
 * through methods using the creation and the movements of Piece entities. It is 
 * designed to be used as interface between the core of the game and it's UI made
 * with SFML. The index (0,0) represents grid's top-left corner.
*/

class Grid
{   
    public :

        /**
         * \brief Constructs the grid from the number of rows and colums it 
         * should have. The size if of 18 rows and 10 columns by default.The default score is 0.
         * \param nrow The number of rows of the grid.
         * \param ncol The number of columns of the grid.
        */

        Grid(unsigned int nrow=18, unsigned int ncol=10);

        /**
         * \brief A getter for the score of the player. 
         * \param 
         * \return The player's current score.
        */

        unsigned int score() const {return _score;}
        
        /**
         * \brief Gets the Cell entity corresponding to a given position of the 
         * attribute \b matrix . 
         * \param row The row's index of the cell.
         * \param col The column's index of the cell
         * \return The cell corresponding to the position ( \b row , \b col ).
        */

        Cell operator()(unsigned int row, unsigned int column) const {return matrix[row][column];} 

        /**
         * \brief Sets the Cell entity corresponding to a given position of the 
         * attribute \b matrix . 
         * \param row The row's index of the cell.
         * \param col The column's index of the cell
         * \return The cell's reference corresponding to the position ( \b row , \b col ).
        */

        Cell& operator()(unsigned int row, unsigned int column){return matrix[row][column];} 

        /**
         * \brief Gets the size of rows of the grid. 
         * \param
         * \return The size of rows of the grid.
        */

        unsigned int row_size() const {return matrix[0].size();}

        /**
         * \brief Gets the size of columns of the grid . 
         * \param
         * \return The size of columns of the grid.
        */

        unsigned int column_size() const {return matrix.size();}

        /**
         * \brief Creates a piece of a given type and sets
         * the grid accordingly. 
         * \param ptype The type of the piece that has to be created.
         * \param row The row of the piece's pivot. It's 0 by default.
         * \return The piece that has been created.
        */

        Piece put_piece(PieceType ptype, unsigned int row=0);

        /**
         * \brief Moves an existing piece, checks if the move is possible in the grid and
         * moves the piece back the piece if it isn't. Also sets the grid accordingly
         * to the result of the different movement. The length of the movement is 1
         * by default.
         * \param piece A reference to the piece that will be moved.
         * \param move The move from Move that has to be performed.
         * \param length The length of the movement.
         * \return A boolean asserting if the movement was possible.
        */

        bool move_piece(Piece& piece, Move move, unsigned int length=1); 

        /**
         * \brief Checks if the grid has full rows and supresses them. Makes the other
         * rows fall accordingly.
         * \param score The current score of the player
         * \return A boolean asserting if the game is over or not.
        */

        bool update();

    private :

        std::vector< std::vector<Cell> > matrix; /**< A matrix of Cell entities. */
        unsigned int _score; /**< The player's score currently associated with the grid. */

        /**
         * \brief A method that get the index of the grid's lines
         * that are full.
         * \param 
         * \return A vector containing the indexes of full lines, from
         * top to bottom (from 0 to the maximum index). 
        */

        std::vector<unsigned int> get_full_rows() const;
};

/**
 * \brief Encodes the grid in a string starting with '\\n'. 
 * Every line of the grid is terminated by '\\n'. Empty cells 
 * are reprented by '.', the full ones by 'O'. This function
 * is designed to be used for debugging and testing of the Grid class. 
 * \param grid The grid which is going to be encoded.
 * \return The string encoding the grid.
*/

std::string get_grid(Grid grid);

/**
 * @brief Creates a random Tetris piece.
 *
 * Randomly selects one of the seven standard Tetrix pieces
 * (I, O, T, L, J, S, Z) and initializes it at row 0 and
 * the given column.
 *
 * @param col Initial column of the piece.
 * @return Piece A newly created random Tetris piece.
 */
PieceType createRandomPiece();



#endif
