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
    unsigned int row_number=20; 
    unsigned int column_number=10;

    sf::VideoMode current_video_mode= sf::VideoMode::getDesktopMode(); 
    sf::RenderWindow window(UI::current_video_mode,"Tetris", sf::Style::Default, sf::State::Fullscreen);
    unsigned int pixel_cell_size= current_video_mode.size.y/row_number;
    unsigned int width_in_cell= current_video_mode.size.x/pixel_cell_size;
    unsigned int left_side_width_in_cell= (width_in_cell-column_number)/2;
    unsigned int right_side_width_in_cell= width_in_cell-left_side_width_in_cell-column_number;

    sf::RectangleShape cell(sf::Vector2f(pixel_cell_size - 1.f, pixel_cell_size - 1.f));

    sf::Font font("../ui/Tetris_font.ttf");
    unsigned int font_size= pixel_cell_size*left_side_width_in_cell/10;
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
        if(row > 3)UI::cell.setFillColor(UI::grey);
        else UI::cell.setFillColor(UI::spawn_grey);
        break;
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

void grid_sides_center_text(Move move, sf::Text& text, unsigned int cell_column)
{
    unsigned int text_size= text.getGlobalBounds().size.x;
    unsigned int margin=0;
    switch(move)
    {
        case Move::left :
            margin= (UI::left_side_width_in_cell*UI::pixel_cell_size - text_size)/2;
            break;

        case Move::right :
            margin= (UI::left_side_width_in_cell + UI::column_number)*UI::pixel_cell_size;
            margin= margin + (UI::right_side_width_in_cell*UI::pixel_cell_size - text_size)/2;
            break;
        default :
            break;
    }
    text.setPosition(sf::Vector2f(margin, cell_column* UI::pixel_cell_size));
}

void draw_score(Grid& grid, sf::RenderWindow& window)
{
    sf::Text text(UI::font);

    // Display legend :

    text.setCharacterSize(UI::font_size);
    text.setString("Score :");
    text.setFillColor(sf::Color::White);
    grid_sides_center_text(Move::left, text, 2);
    window.draw(text);
            
    // Display score :

    text.setString(std::to_string(grid.score()));
    grid_sides_center_text(Move::left, text, 4);
    window.draw(text);
}

void draw_next_block(sf::RenderWindow& window, PieceType& next_type)
{   
    // Display legend :

    sf::Text text(UI::font);
    text.setCharacterSize(UI::font_size);
    text.setString("Next piece :");
    text.setFillColor(sf::Color::White);
    grid_sides_center_text(Move::right, text, 2);
    window.draw(text);

    // Creating the grid 

    Grid next_piece_grid(2,4);
    next_piece_grid.put_piece(next_type,0);

    // Drawing next piece

    unsigned int row= 4;
    unsigned cell_column= UI::left_side_width_in_cell + UI::column_number;
    cell_column = cell_column + (UI::right_side_width_in_cell-4)/2;
    for (unsigned int r = 0; r < next_piece_grid.column_size(); ++r)
        {
            for (unsigned int c = 0; c <next_piece_grid.row_size(); ++c)
            {   

                if(next_piece_grid(r,c).is_full()) draw_cell(next_piece_grid, window, 4, cell_column,r, c);
                
            }
        }
}