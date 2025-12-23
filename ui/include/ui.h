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

/**
 * \namespace UI
 * \brief A namespace to store variables linked to the UI of the game.
 */

namespace UI
{ 
    extern unsigned int row_number; /**< Number of rows of the Tetris' grid. */
    extern unsigned int column_number; /**< Number of columns of the Tetris' grid. */

    extern sf::VideoMode current_video_mode; /**< The SFML window mode to display (fullscreen). */
    extern unsigned int pixel_cell_size; /**< The size in pixel of a Cell.*/
    extern unsigned int width_in_cell; /**< The width in cells of the window. */
    extern unsigned int left_side_width_in_cell; /**< The width in cells of the part of the window to the left of the grid. */
    extern unsigned int right_side_width_in_cell; /**< The width in cells of the part of the window to the right of the grid. */

    extern sf::RectangleShape cell; /**< An SFML cell for display purposes */
};

/**
 * \brief A function to draw the Tetris' grid on screen.
 * \param grid The grid to draw.
 * \param window The window on which the grid will be drawn.
 * \return 
 */

void draw_grid(Grid& grid, sf::RenderWindow& window);

#endif
