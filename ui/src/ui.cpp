/**
 * \file ui.cpp
 * \brief Definition for user interface of the game.
 * \author Alexandre Bleuler - Bonaventure Dohemeto
 * \version 1.0
 * \date 23/12/2025
 *
 * This file contains functions and variables definitions used to make the 
 * user interface of Tetris. Variables are encapsulated in the namespace UI.
 */

#include "SFML/Graphics.hpp"
#include "core_class.h"
#include "ui.h"


namespace UI
{   
    unsigned int row_number=18; 
    unsigned int column_number=10;

    sf::VideoMode current_video_mode= sf::VideoMode::getDesktopMode(); 
    sf::RenderWindow window(UI::current_video_mode,"Tetris", sf::Style::Default, sf::State::Fullscreen);
    unsigned int pixel_cell_size= current_video_mode.size.y/row_number;
    unsigned int width_in_cell= current_video_mode.size.x/pixel_cell_size;
    unsigned int left_side_width_in_cell= (width_in_cell-column_number)/2;
    unsigned int right_side_width_in_cell= width_in_cell-left_side_width_in_cell-column_number;

    sf::RectangleShape cell(sf::Vector2f(pixel_cell_size - 1.f, pixel_cell_size - 1.f));
}

void draw_grid(Grid& grid, sf::RenderWindow& window)
{   
    for (unsigned int r = 0; r < grid.column_size(); ++r)
        {
            for (unsigned int c = 0; c < grid.row_size(); ++c)
            {
                Color cell_color=grid(r,c).color();
                UI::cell.setPosition(sf::Vector2f(
                    (UI::left_side_width_in_cell + c)*UI::pixel_cell_size,
                    r * UI::pixel_cell_size
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
                    UI::cell.setFillColor(UI::purple);
                    break;

                    case Color::orange : 
                    UI::cell.setFillColor(UI::orange);
                    break;

                    case Color::pink : 
                    UI::cell.setFillColor(UI::pink);
                    break;

                    case Color::red : 
                    UI::cell.setFillColor(sf::Color::Red);
                    break;

                    case Color::green : 
                    UI::cell.setFillColor(sf::Color::Green);
                    break;

                    case Color::none :
                    UI::cell.setFillColor(UI::grey);
                }
                window.draw(UI::cell);
                
            }
        }
}

