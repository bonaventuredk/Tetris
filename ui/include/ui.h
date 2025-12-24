/**
 * \file ui.h
 * \brief Declaration for user interface of the game.
 * \author Alexandre Bleuler - Bonaventure Dohemeto
 * \version 1.0
 * \date 23/12/2025
 *
 * This file contains functions and variables déclarations used to make the 
 * user interface of Tetris. Variables are encapsulated in the namespace UI.
 */

#ifndef UI_INCLUDE
#define UI_INCLUDE

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
/**
 * \namespace UI
 * \brief A namespace to store variables linked to the UI of the game.
 */

namespace UI
{ 
    extern unsigned int row_number; /**< Number of rows of the Tetris' grid. */
    extern unsigned int column_number; /**< Number of columns of the Tetris' grid. */

    extern sf::VideoMode current_video_mode; /**< The SFML window mode to display (fullscreen). */
    extern sf::RenderWindow window;
    extern unsigned int pixel_cell_size; /**< The size in pixel of a Cell.*/
    extern unsigned int width_in_cell; /**< The width in cells of the window. */
    extern unsigned int left_side_width_in_cell; /**< The width in cells of the part of the window to the left of the grid. */
    extern unsigned int right_side_width_in_cell; /**< The width in cells of the part of the window to the right of the grid. */

    extern sf::RectangleShape cell; /**< An SFML rectangle to display Tetris' blocks. */

    constexpr sf::Color grey{110, 110, 110}; /**< Color grey for SFML. */
    constexpr sf::Color spawn_grey{70, 70, 70}; /**< Other color grey for SFML. */
    constexpr sf::Color orange{255, 128, 0}; /**< Color orange for SFML. */
    constexpr sf::Color pink{243 , 130, 185}; /**< Color pink for SFML. */
    constexpr sf::Color purple{224, 32, 255}; /**< Color purple for SFML. */

    extern sf::Font font; /**< A font for displaying texts with SFML (https://www.dafont.com/fr/tetris.font). */
    extern unsigned int font_size; /**< The size of the font in pixels. */
};

/**
 * \brief A function to draw the cells of a Tetris' grid on screen.
 * \param grid The grid from which the cell come.
 * \param window The window on which the cell will be drawn.
 * \param cell_row The row of the top left cell of the grid.
 * \param cell_column The column of the top left cell of the grid.
 * \param row The row index of the cell in the grid.
 * \param column The column index of the cell in the grid.
 * \return 
 */


void draw_cell(Grid& grid, sf::RenderWindow& window, unsigned int cell_row, unsigned int cell_column, unsigned int row, unsigned int column);

/**
 * \brief A function to draw the Tetris' grid on screen.
 * \param grid The grid to draw.
 * \param window The window on which the grid will be drawn.
 * \return 
 */

void draw_grid(Grid& grid, sf::RenderWindow& window);

/**
 * \brief A function to center a text on a line of cells on sides of the Tetris' grid.
 * \param move Indicate if it has to be centered to the left or to the right of the grid.
 * \param text The text that has to be centered.
 * \param cell_column The column of the cell on which the text starts.
 * \return 
 */


void grid_sides_center_text(Move move, sf::Text& text, unsigned int cell_column);

/**
 * \brief A function to show the player's score on screen.
 * \param grid The current game's grid which contains the player's score.
 * \param window The window on which the score will be displayed.
 * \return 
 */

void draw_score(Grid& next_piece_grid, sf::RenderWindow& window);

/**
 * \brief A function to show the piece that the player will get the next turn.
 * \param window The window on which the next piece will be displayed.
 *  \param newt_type The type of the next piece.
 * \return 
 */


void draw_next_block(sf::RenderWindow& window, PieceType& next_type);

/**
 * @brief Handles the Game Over screen and allows the player to restart or quit.
 * 
 * @param grid Reference to the game grid.
 * @param current Reference to the current Tetris piece.
 * @param next Reference to the next Tetris piece.
 * @param is_game_over Reference to the boolean flag indicating whether the game is over.
 */

void handleGameOver(Grid& grid, Piece& current, PieceType& next, bool& is_game_over);

#endif
