#include <SFML/Graphics.hpp>
#include "core_class.h"

int main()
{
    Grid grid(18, 10);
    Piece current = grid.put_piece(PieceType::T);

    const int ROWS = grid.row_size();
    const int COLS = grid.column_size();
    const int CELL = 30; //pixel's cell

    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(COLS * CELL, ROWS * CELL)),"Tetris");
    window.setFramerateLimit(60);

    sf::RectangleShape cell(sf::Vector2f(CELL - 1.f, CELL - 1.f)); // -1.f : to avoid overlaps at the edges    sf::Clock clock;
    sf::Clock clock;
    while (window.isOpen())
    {
        
        while(auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) //check if the received event corresponds to the window closing
                window.close(); 
            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) // way to detect key presses in sfml
            {
                if (key->scancode ==sf::Keyboard::Scan::Left)
                    grid.move_piece(current, Move::left);
                if (key->scancode ==sf::Keyboard::Scan::Right)
                    grid.move_piece(current,Move::right);
                if (key->scancode== sf::Keyboard::Scan::Down)
                    grid.move_piece(current, Move::down);
                if (key->scancode ==sf::Keyboard::Scan::Up)
                    grid.move_piece(current,Move::clock_rotation);
            }
        }
        if (clock.getElapsedTime().asSeconds() > 0.6f) //checks if a certain amount of time has passed (0.6)
        {
            bool moved = grid.move_piece(current, Move::down);
            if (!moved){
                grid.update();
                current  =grid.put_piece(createRandomPiece(COLS/2));
            }
            clock.restart();
        }
        window.clear(sf::Color::Black);
        

        
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
        window.display();
    }

    return 0;
}

