#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <array>

#include "core_class.h"
#include "ui.h"

int main()
{
    Grid grid(UI::row_number, UI::column_number);
    bool is_game_over=false;
    Piece current = grid.put_piece(createRandomPiece());
    PieceType next = createRandomPiece();
    
    double waiting_time= 0.6;
    double time_decrease_rate =0;
    double score_threshold= 200;

    UI::window.setFramerateLimit(60);


    sf::Clock clock;
    // for sound
    sf::Music music;
    if (!music.openFromFile("../UI/sounds/music.ogg"))
        return -1;

    music.setLooping(true);
    music.setVolume(40.f);
    music.play();

    sf::SoundBuffer moveBuffer;
    sf::SoundBuffer rotateBuffer;
    sf::SoundBuffer dropBuffer;

    if (!moveBuffer.loadFromFile("../UI/sounds/move.wav") ||
        !rotateBuffer.loadFromFile("../UI/sounds/rotate.wav") ||
        !dropBuffer.loadFromFile("../UI/sounds/drop.wav"))
    {
        return -1; 
    }

    sf::Sound moveSound(moveBuffer);
    sf::Sound rotateSound(rotateBuffer);
    sf::Sound dropSound(dropBuffer);

    while (UI::window.isOpen())
    {
        
        while(!is_game_over && UI::window.isOpen())
        {
            while(auto event = UI::window.pollEvent())
            {
                if (event->is<sf::Event::Closed>()) //check if the received event corresponds to the window closing
                    UI::window.close(); 
                if (const auto* key = event->getIf<sf::Event::KeyPressed>()) // way to detect key presses in sfml
                {
                    if (key->scancode ==sf::Keyboard::Scan::Left)
                        grid.move_piece(current, Move::left);
                        moveSound.play();
                    if (key->scancode ==sf::Keyboard::Scan::Right)
                        grid.move_piece(current,Move::right);
                        moveSound.play();
                    if (key->scancode== sf::Keyboard::Scan::Down)
                        grid.move_piece(current, Move::down);
                        moveSound.play();
                    if (key->scancode ==sf::Keyboard::Scan::Up)
                        grid.move_piece(current,Move::clock_rotation);
                        rotateSound.play();
                }
            }
            if (clock.getElapsedTime().asSeconds() > (1-time_decrease_rate)*waiting_time) //checks if a certain amount of time has passed (0.6)
            {
                bool has_moved = grid.move_piece(current, Move::down);

                if (!has_moved){
                    dropSound.play();
                    is_game_over=grid.update();
                    if(grid.score() > score_threshold)
                    {
                        score_threshold*=2.25;
                        time_decrease_rate+=0.025;
                    }
                    clock.restart();
                    if(!is_game_over)
                    {
                        current =grid.put_piece(next);
                        next = createRandomPiece();
                    }
                }
                clock.restart();
            }
            UI::window.clear(sf::Color::Black);
            
            draw_grid(grid, UI::window);
            draw_score(grid, UI::window);
            draw_next_block(UI::window, next);
           
            UI:: window.display();
            while(clock.getElapsedTime().asSeconds() < 0.04){}
        }
        
        // Adding a question such as : restart or quit 
    }

    return 0;
}

