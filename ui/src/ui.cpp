#include "SFML/Graphics.hpp"
#include "core_class.h"
#include "ui.h"



void draw_grid(Grid& grid, sf::RenderWindow& window)
{   
    for (unsigned int r = 0; r < grid.column_size(); ++r)
        {
            for (unsigned int c = 0; c < grid.row_size(); ++c)
            {
                Color cell_color=grid(r,c).color();
                if (grid(r, c).is_full())
                {
                    UI::cell.setPosition(sf::Vector2f(
                        c * UI::pixel_cell,
                        r * UI::pixel_cell
                    ));
                    switch(cell_color)
                    {
                        case Color::blue : 
                        UI::cell.setFillColor(sf::Color::Blue);
                        break;

                        case Color::yellow :  
                        UI::cell.setFillColor(sf::Color::Yellow);
                        break;

                        case Color::purple : 
                        UI::cell.setFillColor(sf::Color::Cyan);
                        break;

                        case Color::orange : 
                        UI::cell.setFillColor(sf::Color::Cyan);
                        break;

                        case Color::pink : 
                        UI::cell.setFillColor(sf::Color::Cyan);
                        break;

                        case Color::red : 
                        UI::cell.setFillColor(sf::Color::Red);
                        break;

                        case Color::green : 
                        UI::cell.setFillColor(sf::Color::Green);
                        break;
                    }
                    window.draw(UI::cell);
                }
            }
        }
}