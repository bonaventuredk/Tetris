#include <SFML/Graphics.hpp>
#include "core_class.h"

int main()
{
    Grid grid(18, 10);
    Piece current = grid.put_piece(PieceType::T);

    const int ROWS = grid.row_size();
    const int COLS = grid.column_size();
    const int CELL = 30;

    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(COLS * CELL, ROWS * CELL)),"Tetris");
    window.setFramerateLimit(60);

    sf::RectangleShape cell(sf::Vector2f(CELL - 1.f, CELL - 1.f));
    sf::Clock clock;
    while (window.isOpen())
    {
        
        while (auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }
        window.clear(sf::Color::Black);
        

        window.display();
        for (unsigned int r = 0; r < ROWS; ++r)
        {
            for (unsigned int c = 0; c < COLS; ++c)
            {
                if (grid(r, c).is_full())
                {
                    cell.setPosition(sf::Vector2f(
                        c * CELL,
                        r * CELL
                    ));
                    cell.setFillColor(sf::Color::Cyan);
                    window.draw(cell);
                }
            }
        }
    }

    return 0;
}

