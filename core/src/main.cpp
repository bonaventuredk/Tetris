#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include <array>

#include "core_class.h"
#include "ui.h"

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
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
    if (!music.openFromFile("../ui/sounds/music.ogg"))
        return -1;

    music.setLooping(true);
    music.setVolume(10.f);
    music.play();

    sf::SoundBuffer moveLeftBuffer;
    sf::SoundBuffer moveRightBuffer;
    sf::SoundBuffer cloclwiseBuffer;
    sf::SoundBuffer anticloclwiseBuffer;
    sf::SoundBuffer gameoverBuffer;
    sf::SoundBuffer LevelUpBuffer;
    sf::SoundBuffer successBuffer;
    sf::SoundBuffer dropBuffer;

    if (!moveLeftBuffer.loadFromFile("../ui/sounds/clickleft.wav") ||
    !moveRightBuffer.loadFromFile("../ui/sounds/clickright.wav") ||
    !cloclwiseBuffer.loadFromFile("../ui/sounds/clockwise.wav") ||
    !anticloclwiseBuffer.loadFromFile("../ui/sounds/anticlockwise.wav") ||
    !dropBuffer.loadFromFile("../ui/sounds/drop.wav") ||
    !successBuffer.loadFromFile("../ui/sounds/success_linedisapear.wav") ||
    !LevelUpBuffer.loadFromFile("../ui/sounds/higherlevelup.wav") ||
    !gameoverBuffer.loadFromFile("../ui/sounds/game_over.wav"))
    {
        return -1;
    }


    sf::Sound moveLeftSound(moveLeftBuffer);
    sf::Sound moveRightSound(moveRightBuffer);

    sf::Sound clockwiseSound(cloclwiseBuffer);
    sf::Sound anticlockwiseSound(anticloclwiseBuffer);

    sf::Sound dropSound(dropBuffer);
    sf::Sound successSound(successBuffer); //for line disapear
    sf::Sound levelUpSound(LevelUpBuffer);
    sf::Sound gameOverSound(gameoverBuffer);

    moveLeftSound.setVolume(50.f);  
    moveRightSound.setVolume(50.f);
    dropSound.setVolume(70.f);
    clockwiseSound.setVolume(40.f);
    anticlockwiseSound.setVolume(40.f);
    successSound.setVolume(60.f);
    levelUpSound.setVolume(80.f);
    gameOverSound.setVolume(100.f);

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
                    if (key->scancode == sf::Keyboard::Scan::Left) {
                        grid.move_piece(current, Move::left);
                        moveLeftSound.play();
                    }

                    if (key->scancode == sf::Keyboard::Scan::Right) {
                        grid.move_piece(current, Move::right);
                        moveRightSound.play();
                    }

                    if (key->scancode == sf::Keyboard::Scan::Down) {
                        grid.move_piece(current, Move::down);
                        dropSound.play();
                    }

                    if (key->scancode == sf::Keyboard::Scan::Up) {
                        grid.move_piece(current, Move::clock_rotation);
                        clockwiseSound.play();
                    }

                    if (key->scancode == sf::Keyboard::Scan::Space) {
                        grid.move_piece(current, Move::anticlock_rotation);
                        anticlockwiseSound.play();
                    }
                }
            }
            if (clock.getElapsedTime().asSeconds() > (1-time_decrease_rate)*waiting_time) //checks if a certain amount of time has passed (0.6)
            {
                bool has_moved = grid.move_piece(current, Move::down);

                if (!has_moved){
                    dropSound.play();
                    is_game_over=grid.update();
                    if (is_game_over) 
                    {
                        gameOverSound.play();
                    }
                    if(grid.score() > score_threshold)
                    {
                        score_threshold*=2.25;
                        time_decrease_rate+=0.025;
                        music.stop();
                        levelUpSound.play();
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

