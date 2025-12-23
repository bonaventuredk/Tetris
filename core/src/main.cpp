#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "core_class.h"
#include "ui.h"

int main()
{
    Grid grid(UI::row_number, UI::column_number);
    bool is_game_over=false;
    unsigned int score= grid.score();
    Piece current = grid.put_piece(createRandomPiece());

    sf::RenderWindow window(
        UI::current_video_mode,"Tetris", sf::Style::Default, sf::State::Fullscreen);
    window.setFramerateLimit(60);


    sf::Clock clock;
    // for sound
    sf::Music music;
    if (!music.openFromFile("../sounds/music.ogg"))
        return -1;

    music.setLooping(true);
    music.setVolume(40.f);
    music.play();

    sf::SoundBuffer moveBuffer;
    sf::SoundBuffer rotateBuffer;
    sf::SoundBuffer dropBuffer;

    if (!moveBuffer.loadFromFile("../sounds/move.wav") ||
        !rotateBuffer.loadFromFile("../sounds/rotate.wav") ||
        !dropBuffer.loadFromFile("../sounds/drop.wav"))
    {
        return -1; 
    }

    sf::Sound moveSound(moveBuffer);
    sf::Sound rotateSound(rotateBuffer);
    sf::Sound dropSound(dropBuffer);

    while (window.isOpen())
    {
        
        while(!is_game_over && window.isOpen())
        {
            while(auto event = window.pollEvent())
            {
                if (event->is<sf::Event::Closed>()) //check if the received event corresponds to the window closing
                    window.close(); 
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
            if (clock.getElapsedTime().asSeconds() > 0.6f) //checks if a certain amount of time has passed (0.6)
            {
                bool moved = grid.move_piece(current, Move::down);
                if (!moved){
                    dropSound.play();
                    is_game_over=grid.update();
                    score=grid.score();
                    current =grid.put_piece(createRandomPiece());
                }
                clock.restart();
            }
            window.clear(sf::Color::Black);
            
            draw_grid(grid, window);

           
            window.display();
        }
        
        // Adding a question such as : restart or quit 
    }

    return 0;
}

