/**
 * \file main.cpp
 * \brief The file that executes Tetris.
 * \author Alexandre Bleuler - Bonaventure Dohemeto
 * \version 1.0
 * \date 29/12/2025
 */

#include <iostream>
#include <fstream>
#include <string>

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"

#include "core_class.h"
#include "ui.h"

 int bestScore = 0; // Global variable to store the highest score across game sessions
    
int main()
{   
   
    std::string score_file_name= "best_score.txt";

    // Checking if a best score already exist and get it if this is the case.

    std::ifstream reading_score_file{score_file_name, std::ios::in};
    if(reading_score_file.is_open())
    {  
        reading_score_file >> bestScore;
        std::cout << bestScore;
        reading_score_file.close();
    }
   


    // Initialize random seed and game grid
    srand(static_cast<unsigned int>(time(nullptr)));
    Grid grid(UI::row_number, UI::column_number); // Create the main game grid
    bool is_game_over = false; // Flag to check if game is over
    bool is_paused = false; // Flag to check if game is paused
    bool is_quit = false; // Flag to quit the game loop
    Piece current = grid.put_piece(createRandomPiece()); // Current active piece on the grid
    PieceType next = createRandomPiece(); // Next piece to appear

    // Game timing and difficulty settings
    double waiting_time = 0.6; // Base waiting time between piece movements
    double time_decrease_rate = 0; // Variable to increase game speed over time
    double score_threshold = 200; // Score threshold for level-up

    UI::window.setFramerateLimit(60); // Limit the window frame rate

    // Clocks for timing
    sf::Clock clock; // Clock for piece movement timing
    sf::Clock pauseClock; // Clock to handle pause timing

    // Load background music
    sf::Music music;
    if (!music.openFromFile("../ui/sounds/music.ogg"))
        return -1; // Exit if music file not found
    music.setLooping(true); // Loop background music
    music.setVolume(20.f); // Set background music volume
    music.play(); // Start playing music

    // Load sound effects
    sf::SoundBuffer moveLeftBuffer, moveRightBuffer, cloclwiseBuffer, anticloclwiseBuffer;
    sf::SoundBuffer gameoverBuffer, LevelUpBuffer, successBuffer, dropBuffer, pauseBuffer;

    if (!moveLeftBuffer.loadFromFile("../ui/sounds/clickleft.wav") ||
        !moveRightBuffer.loadFromFile("../ui/sounds/clickright.wav") ||
        !cloclwiseBuffer.loadFromFile("../ui/sounds/clockwise.wav") ||
        !anticloclwiseBuffer.loadFromFile("../ui/sounds/anticlockwise.wav") ||
        !dropBuffer.loadFromFile("../ui/sounds/drop.wav") ||
        !successBuffer.loadFromFile("../ui/sounds/success_linedisapear.wav") ||
        !LevelUpBuffer.loadFromFile("../ui/sounds/higherlevelup.wav") ||
        !gameoverBuffer.loadFromFile("../ui/sounds/game_over.wav"))
    {
        return -1; // Exit if any sound file is missing
    }


    // Initialize sound objects
    sf::Sound moveLeftSound(moveLeftBuffer);
    sf::Sound moveRightSound(moveRightBuffer);
    sf::Sound clockwiseSound(cloclwiseBuffer);
    sf::Sound anticlockwiseSound(anticloclwiseBuffer);
    sf::Sound dropSound(dropBuffer);
    sf::Sound successSound(successBuffer);
    sf::Sound levelUpSound(LevelUpBuffer);
    sf::Sound gameOverSound(gameoverBuffer);
    sf::Sound pauseSound(pauseBuffer);

    // Set sound volumes
    moveLeftSound.setVolume(10.f);  // Left movement sound
    moveRightSound.setVolume(10.f); // Right movement sound
    dropSound.setVolume(15.f); // Piece drop sound
    clockwiseSound.setVolume(10.f); // Clockwise rotation sound
    anticlockwiseSound.setVolume(10.f); // Anticlockwise rotation sound
    successSound.setVolume(20.f); // Line clear sound
    levelUpSound.setVolume(70.f); // Level-up sound
    gameOverSound.setVolume(60.f); // Game over sound
    pauseSound.setVolume(60.f); // Pause toggle sound

    // function to restart the game
    auto restartGame = [&](Grid& gridRef, Piece& currentRef, PieceType& nextRef, bool& gameOverRef,
                           bool& pausedRef, sf::Clock& clockRef, double& timeDecreaseRef,
                           double& scoreThresholdRef, sf::Music& musicRef)
    {
        gridRef = Grid(UI::row_number, UI::column_number); // Reset the game grid
        currentRef = gridRef.put_piece(createRandomPiece()); // Place a new current piece
        nextRef = createRandomPiece(); // Generate next piece
        gameOverRef = false; // Reset game over flag
        pausedRef = false; // Reset pause flag
        clockRef.restart(); // Reset clock for movement timing
        timeDecreaseRef = 0; // Reset speed increase
        scoreThresholdRef = 200; // Reset score threshold for level-up
        musicRef.stop(); // Stop and restart music
        musicRef.play();
    };

    // function to handle game-over logic
    auto handleGameOverLogic = [&](Grid& gridRef, Piece& currentRef, PieceType& nextRef, bool& gameOverRef,
                                   bool& pausedRef, sf::Clock& clockRef, double& timeDecreaseRef,
                                   double& scoreThresholdRef, sf::Music& musicRef, sf::RenderWindow& windowRef) -> bool
    {
        while (gameOverRef && windowRef.isOpen())
        {
            while (auto eventOpt = windowRef.pollEvent())
            {
                const sf::Event& event = *eventOpt;

                if (event.is<sf::Event::Closed>())
                {
                    windowRef.close(); // Close the window on exit
                    return false;
                }

                if (const auto* key = event.getIf<sf::Event::KeyPressed>())
                {
                    if (key->scancode == sf::Keyboard::Scan::R) // Restart game
                    {
                        restartGame(gridRef, currentRef, nextRef, gameOverRef, pausedRef,
                                    clockRef, timeDecreaseRef, scoreThresholdRef, musicRef);
                        return true; // Continue game
                    }
                    else if (key->scancode == sf::Keyboard::Scan::Escape) // Quit game
                    {
                        windowRef.close();
                        return false;
                    }
                }
            }
        }
        return false; // Return false if game closed without restart
    };

    // Main game loop
    while (UI::window.isOpen() && !is_quit)
    {
        while(!is_game_over && UI::window.isOpen() && !is_quit)
        {
            // Event handling
            while(auto event = UI::window.pollEvent())
            {
                if (event->is<sf::Event::Closed>())
                    UI::window.close(); // Close window if X is pressed

                if (const auto* key = event->getIf<sf::Event::KeyPressed>())
                {
                    if (key->scancode == sf::Keyboard::Scan::P) // Pause toggle
                    {
                        is_paused = !is_paused;
                        if (is_paused) {
                            music.pause(); // Pause background music
                            pauseSound.play(); // Play pause sound
                        } else {
                            music.play(); // Resume music
                            pauseSound.pause(); // Pause the pause sound
                        }
                    }

                    if (is_paused)
                    {
                        if (key->scancode == sf::Keyboard::Scan::Escape) // Quit from pause menu
                        {
                            UI::window.close();
                            is_quit = true;
                        }

                        if (key->scancode == sf::Keyboard::Scan::R) // Restart from pause menu
                        {
                            pauseSound.stop(); // Stop pause sound
                            music.stop(); // Stop music
                            music.play(); // Restart music

                            // Reset game state
                            grid = Grid(UI::row_number, UI::column_number);
                            current = grid.put_piece(createRandomPiece());
                            next = createRandomPiece();

                            is_game_over = false;
                            is_paused = false;

                            clock.restart();
                            time_decrease_rate = 0;
                            score_threshold = 200;
                        }
                    }

                    // Game controls (when not paused)
                    if (!is_paused) {
                        if (key->scancode == sf::Keyboard::Scan::Left) { grid.move_piece(current, Move::left); moveLeftSound.play(); }
                        if (key->scancode == sf::Keyboard::Scan::Right) { grid.move_piece(current, Move::right); moveRightSound.play(); }
                        if (key->scancode == sf::Keyboard::Scan::Down) { grid.move_piece(current, Move::down); dropSound.play(); }
                        if (key->scancode == sf::Keyboard::Scan::Up) { grid.move_piece(current, Move::clock_rotation); clockwiseSound.play(); }
                        if (key->scancode == sf::Keyboard::Scan::Space) { grid.move_piece(current, Move::anticlock_rotation); anticlockwiseSound.play(); }
                    }
                }
            }

            // Game update logic when not paused
            if (!is_paused && clock.getElapsedTime().asSeconds() > (1-time_decrease_rate)*waiting_time)
            {
                bool has_moved = grid.move_piece(current, Move::down); // Attempt to move piece down
                if (!has_moved){
                    dropSound.play(); // Play drop sound
                    is_game_over = grid.update(); // Update grid and check for game over
                    bestScore = std::max(bestScore, static_cast<int>(grid.score())); // Save best score

                    if (is_game_over) {
                        gameOverSound.play();         // Play game over sound
                        music.stop();                 // Stop background music

                        UI::window.clear(sf::Color::Black); 
                        draw_game_over_screen(UI::window, static_cast<int>(grid.score()), bestScore);
                        UI::window.display();

                        // show game-over screen and handle input (restart/quit)
                        if (!handleGameOverLogic(grid, current, next, is_game_over, is_paused,
                                                clock, time_decrease_rate, score_threshold,
                                                music, UI::window)) {
                            is_quit = true; // Exit if player chooses to quit
                        }

                        
                        if (!is_game_over) {
                            
                            while (auto ev = UI::window.pollEvent()) { (void)ev; }

                            UI::window.clear(sf::Color::Black);
                            UI::window.display();

                            continue; 
                        }
                    }


                    if(grid.score() > score_threshold) { // Level progression
                        score_threshold *= 2.25;
                        time_decrease_rate += 0.05;
                        music.stop();
                        levelUpSound.play();
                    }

                    clock.restart();
                    if(!is_game_over) { current = grid.put_piece(next); next = createRandomPiece(); }
                }
                clock.restart();
            }

            // Rendering
            UI::window.clear(sf::Color::Black);
            draw_grid(grid, UI::window); // Draw the grid
            draw_score(grid, UI::window); // Draw the current score
            draw_next_piece(UI::window, next); // Draw next piece
            draw_controls(UI::window); //  Draw controls on screen

            if (is_paused) { draw_pause_screen(UI::window); } // Draw pause screen if paused

            UI::window.display(); // Display the updated window

            // Simple frame pacing
            while(clock.getElapsedTime().asSeconds() < 0.04){}
        }

    }

    // Saving best score in a fil
    
    std::ofstream writing_score_file{score_file_name, std::ios::out};
    if(writing_score_file.is_open())
    {   
        writing_score_file << bestScore;
        writing_score_file.close();
    }

    return 0;
}
