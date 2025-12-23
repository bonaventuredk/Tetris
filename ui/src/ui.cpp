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

#include <string>

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

    sf::Font font("../UI/Tetris_font.ttf");
}

void draw_cell(Grid& grid, sf::RenderWindow& window, unsigned int cell_row, unsigned int cell_column, unsigned int row, unsigned int column)
{
    Color cell_color=grid(row, column).color();
    UI::cell.setPosition(sf::Vector2f(
        (cell_column + column)*UI::pixel_cell_size,
        (cell_row + row) * UI::pixel_cell_size
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

void draw_grid(Grid& grid, sf::RenderWindow& window)
{   
    for (unsigned int r = 0; r < grid.column_size(); ++r)
        {
            for (unsigned int c = 0; c < grid.row_size(); ++c)
            {   
                draw_cell(grid, window, 0, UI::left_side_width_in_cell, r, c);
                
            }
        }
}

void draw_score(Grid& grid, sf::RenderWindow& window)
{
    sf::Text text(UI::font);

    // Display legend :

    text.setCharacterSize(76);
    text.setString("Score : ");
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(
                    1*UI::pixel_cell_size,
                    2 * UI::pixel_cell_size
                ));
    window.draw(text);
            
    // Display score :

    text.setString(std::to_string(grid.score()));
    text.setPosition(sf::Vector2f(
                    1*UI::pixel_cell_size,
                    4 * UI::pixel_cell_size
                ));
    window.draw(text);
}

void draw_next_block(sf::RenderWindow& window, PieceType& next_type)
{   
    // Display legend :

    sf::Text text(UI::font);
    text.setCharacterSize(76);
    text.setString("Next piece : ");
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f(
                    (UI::left_side_width_in_cell + UI::column_number + 1)*UI::pixel_cell_size,
                    2 * UI::pixel_cell_size
                ));
    window.draw(text);

    // Creating the grid 

    Grid next_piece_grid(2,4);
    next_piece_grid.put_piece(next_type);

    // Drawing next piece

    unsigned int row= 4;
    unsigned cell_column= UI::left_side_width_in_cell + UI::column_number + 3;
    for (unsigned int r = 0; r < next_piece_grid.column_size(); ++r)
        {
            for (unsigned int c = 0; c <next_piece_grid.row_size(); ++c)
            {   

                if(next_piece_grid(r,c).is_full()) draw_cell(next_piece_grid, window, 4, cell_column,r, c);
                
            }
        }
}