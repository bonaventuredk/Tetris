#ifndef UI_INCLUDE
#define UI_INCLUDE

#include <SFML/Graphics.hpp>

/**
 * \namespace UI
 * \brief A namespace to store variables linked to the UI of the game.
 */

namespace UI
{
    constexpr unsigned int pixel_cell = 30; 
    sf::RectangleShape cell(sf::Vector2f(UI::pixel_cell - 1.f, UI::pixel_cell - 1.f)); // -1.f : to avoid overlaps at the edges    sf::Clock clock;
};

/**
 * \brief A function to draw the Tetris' grid on screen.
 * \param grid The grid to draw.
 * \param window The window on which the grid will be drawn.
 * \return 
 */

void draw_grid(Grid& grid, sf::RenderWindow& window);

#endif