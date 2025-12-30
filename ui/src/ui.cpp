/**
 * \file ui.cpp
 * \brief User interface implementation for Tetris game
 * \author Alexandre Bleuler - Bonaventure Dohemeto
 * \version 1.0
 * \date 23/12/2025
 */

#include <string>
#include <iostream>
#include <optional>
#include "SFML/Graphics.hpp"
#include <SFML/Audio/Music.hpp>
#include <SFML/Window.hpp>
#include "core_class.h"
#include "ui.h"
#include <fstream> 

namespace UI
{   
    // Grid dimensions
    unsigned int row_number = 20; 
    unsigned int column_number = 10;

    // Window setup
    sf::VideoMode current_video_mode = sf::VideoMode::getDesktopMode(); 
    sf::RenderWindow window(UI::current_video_mode, "Tetris", sf::Style::Default, sf::State::Fullscreen);
    
    // Cell size calculations
    unsigned int height_in_cell = row_number + 2;
    unsigned int pixel_cell_size = current_video_mode.size.y / height_in_cell;
    unsigned int width_in_cell = current_video_mode.size.x / pixel_cell_size;
    unsigned int left_side_width_in_cell = (width_in_cell - column_number) / 2;
    unsigned int right_side_width_in_cell = width_in_cell - left_side_width_in_cell - column_number;

    // Visual elements
    sf::RectangleShape cell(sf::Vector2f(pixel_cell_size - 1.f, pixel_cell_size - 1.f));
    sf::Font font("../ui/Tetris_font.ttf");
    unsigned int font_size = pixel_cell_size * left_side_width_in_cell / 10;
}

// Draw single cell with appropriate color
void draw_cell(Grid& grid, sf::RenderWindow& window, unsigned int cell_row, unsigned int cell_column, unsigned int row, unsigned int column)
{
    Color cell_color = grid(row, column).color();
    UI::cell.setPosition(sf::Vector2f(
        (cell_column + column) * UI::pixel_cell_size,
        (cell_row + row) * UI::pixel_cell_size
    ));
    
    switch(cell_color)
    {
        case Color::blue: 
            UI::cell.setFillColor(sf::Color::Blue);
            break;
        case Color::yellow:  
            UI::cell.setFillColor(sf::Color::Yellow);
            break;
        case Color::purple: 
            UI::cell.setFillColor(UI::purple);
            break;
        case Color::orange: 
            UI::cell.setFillColor(UI::orange);
            break;
        case Color::pink: 
            UI::cell.setFillColor(UI::pink);
            break;
        case Color::red: 
            UI::cell.setFillColor(sf::Color::Red);
            break;
        case Color::green: 
            UI::cell.setFillColor(sf::Color::Green);
            break;
        case Color::none:
            if(row > 3) UI::cell.setFillColor(UI::grey);
            else UI::cell.setFillColor(UI::spawn_grey);
            break;
    }
    window.draw(UI::cell);
}

// Draw entire game grid
void draw_grid(Grid& grid, sf::RenderWindow& window)
{   
    for (unsigned int r = 0; r < grid.column_size(); ++r)
    {
        for (unsigned int c = 0; c < grid.row_size(); ++c)
        {   
            draw_cell(grid, window, 1, UI::left_side_width_in_cell, r, c);
        }
    }
}

// Position text on left or right side of grid
void grid_sides_center_text(Move move, sf::Text& text, unsigned int cell_row)
{
    unsigned int text_size = text.getGlobalBounds().size.x;
    unsigned int margin = 0;
    
    switch(move)
    {
        case Move::left:
            margin = (UI::left_side_width_in_cell * UI::pixel_cell_size - text_size) / 2;
            break;
        case Move::right:
            margin = (UI::left_side_width_in_cell + UI::column_number) * UI::pixel_cell_size;
            margin += (UI::right_side_width_in_cell * UI::pixel_cell_size - text_size) / 2;
            break;
        default:
            break;
    }
    text.setPosition(sf::Vector2f(margin, cell_row * UI::pixel_cell_size));
}

// Display score information
void draw_score(Grid& grid, sf::RenderWindow& window)
{
    sf::Text text(UI::font);
    text.setCharacterSize(UI::font_size);
    
    // Score label
    text.setString("Score :");
    text.setFillColor(sf::Color::White);
    grid_sides_center_text(Move::left, text, 2);
    window.draw(text);
    
    // Current score
    text.setString(std::to_string(grid.score()));
    grid_sides_center_text(Move::left, text, 4);
    window.draw(text);
    
    // Best score
    extern int bestScore;
    text.setString("Best : " + std::to_string(bestScore));
    grid_sides_center_text(Move::left, text, 6);
    window.draw(text);
}

// Display next piece preview
void draw_next_piece(sf::RenderWindow& window, PieceType& next_type)
{   
    sf::Text text(UI::font);
    text.setCharacterSize(UI::font_size);
    text.setString("Next piece :");
    text.setFillColor(sf::Color::White);
    grid_sides_center_text(Move::right, text, 2);
    window.draw(text);
    
    // Create preview grid
    Grid next_piece_grid(2, 4);
    next_piece_grid.put_piece(next_type, 0);
    
    // Draw next piece
    unsigned cell_column = UI::left_side_width_in_cell + UI::column_number;
    cell_column += (UI::right_side_width_in_cell - 4) / 2;
    
    for (unsigned int r = 0; r < next_piece_grid.column_size(); ++r)
    {
        for (unsigned int c = 0; c < next_piece_grid.row_size(); ++c)
        {   
            if(next_piece_grid(r, c).is_full()) 
                draw_cell(next_piece_grid, window, 5, cell_column, r, c);
        }
    }
}

// Game over screen display
void draw_game_over_screen(sf::RenderWindow& window, int score, int bestScore)
{
    // Text elements for game over screen
    sf::Text gameOverText(UI::font);
    gameOverText.setCharacterSize(UI::font_size * 1);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setString("GAME OVER!");
    
    sf::Text scoreText(UI::font);
    scoreText.setCharacterSize(UI::font_size * 0.75f);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setString("Score: " + std::to_string(score));
    
    sf::Text bestScoreText(UI::font);
    bestScoreText.setCharacterSize(UI::font_size * 0.75f);
    bestScoreText.setFillColor(sf::Color::Yellow);
    bestScoreText.setString("Best: " + std::to_string(bestScore));
    
    sf::Text instructionText(UI::font);
    instructionText.setCharacterSize(UI::font_size * 0.5);
    instructionText.setFillColor(sf::Color::Yellow);
    instructionText.setString("Press R to restart, M (qwerty) to menu or Esc to quit !");
    
    // Background panel
    float maxWidth = 0.75f * UI::width_in_cell * UI::pixel_cell_size;
    float totalHeight = 0.40f * UI::height_in_cell * UI::pixel_cell_size;
    
    sf::RectangleShape background(sf::Vector2f(maxWidth, totalHeight));
    background.setFillColor(sf::Color(30, 30, 30, 230));
    background.setOutlineThickness(3.f);
    background.setOutlineColor(sf::Color::White);
    
    // Position calculation
    sf::Vector2f windowSize(window.getSize().x, window.getSize().y);
    sf::Vector2f backgroundPos(
        windowSize.x / 2.f - maxWidth / 2.f,
        windowSize.y / 2.f - totalHeight / 2.f
    );
    background.setPosition(backgroundPos);
    
    double box_upper_row = backgroundPos.y;
    double box_height = background.getGlobalBounds().size.y;
    
    // Position and draw all elements
    unsigned int text_width = gameOverText.getGlobalBounds().size.x;
    gameOverText.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
        box_upper_row + 1 * box_height / 10
    ));
    
    text_width = scoreText.getGlobalBounds().size.x;
    scoreText.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
        box_upper_row + 3 * box_height / 10
    ));
    
    text_width = bestScoreText.getGlobalBounds().size.x;
    bestScoreText.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
        box_upper_row + 5 * box_height / 10
    ));
    
    text_width = instructionText.getGlobalBounds().size.x;
    instructionText.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
        box_upper_row + 7 * box_height / 10
    ));
    
    window.draw(background);
    window.draw(gameOverText);
    window.draw(scoreText);
    window.draw(bestScoreText);
    window.draw(instructionText);
}

// Display control instructions
void draw_controls(sf::RenderWindow& window)
{
    sf::Text text(UI::font);
    text.setCharacterSize(UI::font_size);
    text.setFillColor(sf::Color::White);
    
    std::vector<std::string> controls = {
        " left arrow : Moving left",
        " right arrow : Moving right",
        " down arrow : Moving down ",
        " up arrow : Anti-clockwise rotation",
        " Space : Clockwise rotation",
        "P : Resume"
    };
    
    // Controls title
    text.setString("Controls :");
    grid_sides_center_text(Move::right, text, 10);
    window.draw(text);
    
    // List controls
    text.setCharacterSize(UI::font_size * 0.7f);
    for(size_t i = 0; i < controls.size(); ++i)
    {
        text.setString(controls[i]);
        grid_sides_center_text(Move::right, text, 13 + i);
        window.draw(text);
    }
}

// Pause screen overlay
void draw_pause_screen(sf::RenderWindow& window)
{
    // Semi-transparent overlay
    sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 150));
    
    // Pause text
    sf::Text pause_text(UI::font);
    pause_text.setCharacterSize(UI::font_size * 1.5);
    pause_text.setFillColor(sf::Color::Yellow);
    pause_text.setString("PAUSE");
    
    unsigned int text_width = pause_text.getGlobalBounds().size.x;
    unsigned int text_height = pause_text.getGlobalBounds().size.y;
    pause_text.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,  
        ((UI::height_in_cell - 6) * UI::pixel_cell_size - text_height) / 2    
    ));
    
    // Instructions
    sf::Text instruction_text(UI::font);
    instruction_text.setCharacterSize(UI::font_size);
    instruction_text.setFillColor(sf::Color::White);
    instruction_text.setString("Press |P: resume | R: start a new game | M: menu | Esc: quit ");
   
    text_width = instruction_text.getGlobalBounds().size.x;
    text_height = instruction_text.getGlobalBounds().size.y;
    instruction_text.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,  
        ((UI::height_in_cell + 2) * UI::pixel_cell_size - text_height) / 2    
    ));
    
    window.draw(overlay);
    window.draw(pause_text);
    window.draw(instruction_text);
}

// Main menu display
void draw_menu_screen(sf::RenderWindow& window, MenuChoice selectedChoice, int bestScore)
{
    // Menu text elements
    sf::Text titleText(UI::font);
    titleText.setCharacterSize(UI::font_size * 2.0f);
    titleText.setFillColor(sf::Color::Red);
    titleText.setString("TETRIS");
    
    sf::Text startText(UI::font);
    startText.setCharacterSize(UI::font_size * 0.8f);
    startText.setString("Start Game");
    startText.setFillColor(selectedChoice == MenuChoice::StartGame ? sf::Color::Yellow : sf::Color::White);
    
    sf::Text controlsText(UI::font);
    controlsText.setCharacterSize(UI::font_size * 0.8f);
    controlsText.setString("Controls");
    controlsText.setFillColor(selectedChoice == MenuChoice::Controls ? sf::Color::Yellow : sf::Color::White);
    
    sf::Text bestScoreText(UI::font);
    bestScoreText.setCharacterSize(UI::font_size * 0.8f);
    bestScoreText.setString("Best Score: " + std::to_string(bestScore));
    bestScoreText.setFillColor(selectedChoice == MenuChoice::BestScore ? sf::Color::Yellow : sf::Color::White);
    
    sf::Text quitText(UI::font);
    quitText.setCharacterSize(UI::font_size * 0.8f);
    quitText.setString("Quit");
    quitText.setFillColor(selectedChoice == MenuChoice::Quit ? sf::Color::Yellow : sf::Color::White);
    
    sf::Text instructionText(UI::font);
    instructionText.setCharacterSize(UI::font_size * 0.5f);
    instructionText.setFillColor(sf::Color::Cyan);
    instructionText.setString("Use UP/DOWN arrows to navigate, ENTER to select");
    
    // Menu background
    float maxWidth = 0.6f * UI::width_in_cell * UI::pixel_cell_size;
    float totalHeight = 0.7f * UI::height_in_cell * UI::pixel_cell_size;
    
    sf::RectangleShape background(sf::Vector2f(maxWidth, totalHeight));
    background.setFillColor(sf::Color(20, 20, 20, 230));
    background.setOutlineThickness(3.f);
    background.setOutlineColor(sf::Color::White);
    
    // Position background
    sf::Vector2f windowSize(window.getSize().x, window.getSize().y);
    sf::Vector2f backgroundPos(
        windowSize.x / 2.f - maxWidth / 2.f,
        windowSize.y / 2.f - totalHeight / 2.f
    );
    background.setPosition(backgroundPos);
    
    // Position all text elements
    double box_upper_row = backgroundPos.y;
    double box_height = background.getGlobalBounds().size.y;
    
    unsigned int text_width = titleText.getGlobalBounds().size.x;
    titleText.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
        box_upper_row + 0.1f * box_height
    ));
    
    text_width = startText.getGlobalBounds().size.x;
    startText.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
        box_upper_row + 0.3f * box_height
    ));
    
    text_width = controlsText.getGlobalBounds().size.x;
    controlsText.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
        box_upper_row + 0.4f * box_height
    ));
    
    text_width = bestScoreText.getGlobalBounds().size.x;
    bestScoreText.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
        box_upper_row + 0.5f * box_height
    ));
    
    text_width = quitText.getGlobalBounds().size.x;
    quitText.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
        box_upper_row + 0.6f * box_height
    ));
    
    text_width = instructionText.getGlobalBounds().size.x;
    instructionText.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
        box_upper_row + 0.85f * box_height
    ));
    
    // Draw everything
    window.draw(background);
    window.draw(titleText);
    window.draw(startText);
    window.draw(controlsText);
    window.draw(bestScoreText);
    window.draw(quitText);
    window.draw(instructionText);
}

// Global best score
extern int bestScore; 

// Main menu logic
MenuChoice showMenu(int bestScore)
{
    bool in_menu = true;
    MenuChoice menu_selection = MenuChoice::StartGame;

    while (in_menu && UI::window.isOpen())
    {
        while (auto event = UI::window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                UI::window.close();

            if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                // Menu navigation
                if (key->scancode == sf::Keyboard::Scan::Up)
                {
                    if (menu_selection == MenuChoice::StartGame)
                        menu_selection = MenuChoice::Quit;
                    else if (menu_selection == MenuChoice::Controls)
                        menu_selection = MenuChoice::StartGame;
                    else if (menu_selection == MenuChoice::BestScore)
                        menu_selection = MenuChoice::Controls;
                    else if (menu_selection == MenuChoice::Quit)
                        menu_selection = MenuChoice::BestScore;
                }
                else if (key->scancode == sf::Keyboard::Scan::Down)
                {
                    if (menu_selection == MenuChoice::StartGame)
                        menu_selection = MenuChoice::Controls;
                    else if (menu_selection == MenuChoice::Controls)
                        menu_selection = MenuChoice::BestScore;
                    else if (menu_selection == MenuChoice::BestScore)
                        menu_selection = MenuChoice::Quit;
                    else if (menu_selection == MenuChoice::Quit)
                        menu_selection = MenuChoice::StartGame;
                }
                // Selection
                else if (key->scancode == sf::Keyboard::Scan::Enter ||
                        key->scancode == sf::Keyboard::Scan::Space)
                {
                    return menu_selection;
                }
                else if (key->scancode == sf::Keyboard::Scan::Escape)
                {
                    return MenuChoice::Quit;
                }
            }
        }

        // Draw menu
        UI::window.clear(sf::Color::Black);
        draw_menu_screen(UI::window, menu_selection, bestScore);
        UI::window.display();
    }

    return MenuChoice::Quit;
}

// Game initialization
void initializeGame(Grid& grid, Piece& current, PieceType& next, bool& gameOver,
                   double& timeDecreaseRate, double& scoreThreshold)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    grid = Grid(UI::row_number, UI::column_number);
    current = grid.put_piece(createRandomPiece());
    next = createRandomPiece();
    gameOver = false;
    timeDecreaseRate = 0;
    scoreThreshold = 200;
}

// Restart game
void restartGame(Grid& grid, Piece& current, PieceType& next, bool& gameOver,
                bool& isPaused, sf::Clock& clock, double& timeDecreaseRate,
                double& scoreThreshold, sf::Music& music)
{
    grid = Grid(UI::row_number, UI::column_number);
    current = grid.put_piece(createRandomPiece());
    next = createRandomPiece();
    gameOver = false;
    isPaused = false;
    timeDecreaseRate = 0;
    scoreThreshold = 200;
    clock.restart();
    music.stop();
    music.play();
}

// Handle in-game input
void handleGameInput(Grid& grid, Piece& current, bool& isPaused, bool& isQuit,
                    bool& goToMenu, sf::Sound& moveLeftSound, sf::Sound& moveRightSound,
                    sf::Sound& clockwiseSound, sf::Sound& anticlockwiseSound,
                    sf::Sound& dropSound)
{
    while (auto event = UI::window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            UI::window.close();
        }
        else if (const auto* key = event->getIf<sf::Event::KeyPressed>())
        {
            if (key->scancode == sf::Keyboard::Scan::P)
            {
                isPaused = !isPaused;
            }
            else if (!isPaused)
            {
                if (key->scancode == sf::Keyboard::Scan::Left)
                {
                    grid.move_piece(current, Move::left);
                    moveLeftSound.play();
                }
                else if (key->scancode == sf::Keyboard::Scan::Right)
                {
                    grid.move_piece(current, Move::right);
                    moveRightSound.play();
                }
                else if (key->scancode == sf::Keyboard::Scan::Down)
                {
                    grid.move_piece(current, Move::down);
                    dropSound.play();
                }
                else if (key->scancode == sf::Keyboard::Scan::Up)
                {
                    grid.move_piece(current, Move::clock_rotation);
                    clockwiseSound.play();
                }
                else if (key->scancode == sf::Keyboard::Scan::Space)
                {
                    grid.move_piece(current, Move::anticlock_rotation);
                    anticlockwiseSound.play();
                }
            }
        }
    }
}

// Handle pause menu input
void handlePauseInput(bool& isPaused, bool& isQuit, bool& goToMenu, Grid& grid,
                     Piece& current, PieceType& next, double& timeDecreaseRate,
                     double& scoreThreshold, sf::Clock& clock, sf::Music& music,
                     sf::Sound& pauseSound)
{
    if (auto event = UI::window.pollEvent())
    {
        if (const auto* key = event->getIf<sf::Event::KeyPressed>())
        {
            if (key->scancode == sf::Keyboard::Scan::P)
            {
                isPaused = false;
            }
            else if (key->scancode == sf::Keyboard::Scan::Escape)
            {
                isQuit = true;
            }
            else if (key->scancode == sf::Keyboard::Scan::M)
            {
                goToMenu = true;
                isPaused = false;
            }
            else if (key->scancode == sf::Keyboard::Scan::R)
            {
                restartGame(grid, current, next, isPaused, isPaused, clock,
                           timeDecreaseRate, scoreThreshold, music);
            }
        }
    }
}

// Handle game over input
void handleGameOverInput(Grid& grid, Piece& current, PieceType& next,
                        bool& gameOver, bool& isPaused, sf::Clock& clock,
                        double& timeDecreaseRate, double& scoreThreshold,
                        sf::Music& music, bool& isQuit, bool& goToMenu)
{
    if (auto event = UI::window.pollEvent())
    {
        if (const auto* key = event->getIf<sf::Event::KeyPressed>())
        {
            if (key->scancode == sf::Keyboard::Scan::R)
            {
                restartGame(grid, current, next, gameOver, isPaused, clock,
                           timeDecreaseRate, scoreThreshold, music);
                goToMenu = false;
            }
            else if (key->scancode == sf::Keyboard::Scan::M)
            {
                goToMenu = true;
                gameOver = false;
            }
            else if (key->scancode == sf::Keyboard::Scan::Escape)
            {
                isQuit = true;
            }
        }
    }
}

// Game update logic
void updateGame(Grid& grid, Piece& current, PieceType& next, bool& gameOver,
               sf::Clock& clock, double& timeDecreaseRate, double& scoreThreshold,
               sf::Sound& dropSound, sf::Sound& successSound, sf::Sound& levelUpSound,
               sf::Sound& gameOverSound, sf::Music& music, int& bestScore)
{
    if (clock.getElapsedTime().asSeconds() > (1 - timeDecreaseRate) * 0.6)
    {
        bool hasMoved = grid.move_piece(current, Move::down);
        if (!hasMoved)
        {
            dropSound.play();
            gameOver = grid.update();
            bestScore = std::max(bestScore, static_cast<int>(grid.score()));

            if (gameOver)
            {
                gameOverSound.play();
                music.stop();
            }
            else if (grid.score() > scoreThreshold)
            {
                scoreThreshold *= 2.25;
                timeDecreaseRate += 0.05;
                music.stop();
                levelUpSound.play();
                music.play();
            }

            if (!gameOver)
            {
                current = grid.put_piece(next);
                next = createRandomPiece();
            }
        }
        clock.restart();
    }
}

// Draw game state
void drawGame(sf::RenderWindow& window, Grid& grid, PieceType& next, bool isPaused)
{
    window.clear(sf::Color::Black);
    draw_grid(grid, window);
    draw_score(grid, window);
    draw_next_piece(window, next);
    draw_controls(window);
    
    if (isPaused)
    {
        draw_pause_screen(window);
    }
    
    window.display();
}

// Controls screen
void draw_controls_screen(sf::RenderWindow& window)
{
    sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 220));
    
    sf::Text controlsTitle(UI::font);
    controlsTitle.setCharacterSize(UI::font_size * 1.2f);
    controlsTitle.setFillColor(sf::Color::Yellow);
    controlsTitle.setString("CONTROLS");
    
    std::vector<std::string> controls = {
        "Left/Right Arrow  : Move piece left/right",
        "Down Arrow  : Move piece down faster",
        "Up Arrow    : Rotate anti-clockwise",
        "Space       : Rotate clockwise",
        "P           : Pause/Resume game",
        "R           : Restart game",
        "M           : Return to menu",
        "ESC         : Quit game/Exit"
    };
    
    sf::Text backText(UI::font);
    backText.setCharacterSize(UI::font_size * 0.7f);
    backText.setFillColor(sf::Color::Cyan);
    backText.setString("Press ESC, ENTER or SPACE to return to menu");
    
    // Position elements
    unsigned int text_width = controlsTitle.getGlobalBounds().size.x;
    controlsTitle.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
        UI::pixel_cell_size * 3
    ));
    
    window.draw(overlay);
    window.draw(controlsTitle);
    
    // Draw controls list
    sf::Text controlItem(UI::font);
    controlItem.setCharacterSize(UI::font_size * 0.7f);
    controlItem.setFillColor(sf::Color::White);
    
    for (size_t i = 0; i < controls.size(); ++i)
    {
        controlItem.setString(controls[i]);
        text_width = controlItem.getGlobalBounds().size.x;
        controlItem.setPosition(sf::Vector2f(
            (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
            UI::pixel_cell_size * (6 + i * 1.5f)
        ));
        window.draw(controlItem);
    }
    
    text_width = backText.getGlobalBounds().size.x;
    backText.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
        UI::pixel_cell_size * (UI::height_in_cell - 4)
    ));
    window.draw(backText);
}

// Best score screen
void draw_best_score_screen(sf::RenderWindow& window, int bestScore)
{
    sf::RectangleShape overlay(sf::Vector2f(window.getSize().x, window.getSize().y));
    overlay.setFillColor(sf::Color(0, 0, 0, 220));
    
    sf::Text scoreTitle(UI::font);
    scoreTitle.setCharacterSize(UI::font_size * 1.2f);
    scoreTitle.setFillColor(sf::Color::Yellow);
    scoreTitle.setString("BEST SCORE");
    
    sf::Text scoreText(UI::font);
    scoreText.setCharacterSize(UI::font_size * 1.5f);
    scoreText.setFillColor(sf::Color::Green);
    scoreText.setString(std::to_string(bestScore));
    
    sf::Text backText(UI::font);
    backText.setCharacterSize(UI::font_size * 0.7f);
    backText.setFillColor(sf::Color::Cyan);
    backText.setString("Press ESC, ENTER or SPACE to return to menu");
    
    // Position elements
    unsigned int text_width = scoreTitle.getGlobalBounds().size.x;
    scoreTitle.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
        UI::pixel_cell_size * 5
    ));
    
    text_width = scoreText.getGlobalBounds().size.x;
    scoreText.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
        UI::pixel_cell_size * 8
    ));
    
    text_width = backText.getGlobalBounds().size.x;
    backText.setPosition(sf::Vector2f(
        (UI::width_in_cell * UI::pixel_cell_size - text_width) / 2,
        UI::pixel_cell_size * (UI::height_in_cell - 4)
    ));
    
    window.draw(overlay);
    window.draw(scoreTitle);
    window.draw(scoreText);
    window.draw(backText);
}

// Menu navigation helper
bool handleMenuNavigation(MenuChoice& selectedChoice, const sf::Event& event)
{
    if (const auto* key = event.getIf<sf::Event::KeyPressed>())
    {
        if (key->scancode == sf::Keyboard::Scan::Up)
        {
            // Navigation logic
            if (selectedChoice == MenuChoice::StartGame)
                selectedChoice = MenuChoice::Quit;
            else if (selectedChoice == MenuChoice::Controls)
                selectedChoice = MenuChoice::StartGame;
            else if (selectedChoice == MenuChoice::BestScore)
                selectedChoice = MenuChoice::Controls;
            else if (selectedChoice == MenuChoice::Quit)
                selectedChoice = MenuChoice::BestScore;
            return true;
        }
        else if (key->scancode == sf::Keyboard::Scan::Down)
        {
            if (selectedChoice == MenuChoice::StartGame)
                selectedChoice = MenuChoice::Controls;
            else if (selectedChoice == MenuChoice::Controls)
                selectedChoice = MenuChoice::BestScore;
            else if (selectedChoice == MenuChoice::BestScore)
                selectedChoice = MenuChoice::Quit;
            else if (selectedChoice == MenuChoice::Quit)
                selectedChoice = MenuChoice::StartGame;
            return true;
        }
    }
    return false;
}

// Execute menu selection
bool executeMenuAction(MenuChoice selectedChoice, bool& inMenu, 
                       sf::RenderWindow& window, int bestScore)
{
    switch (selectedChoice)
    {
        case MenuChoice::StartGame:
            inMenu = false;
            return true;
            
        case MenuChoice::Controls:
        {
            bool inControls = true;
            while (inControls && window.isOpen())
            {
                while (auto event = window.pollEvent())
                {
                    if (event->is<sf::Event::Closed>())
                    {
                        window.close();
                        return false;
                    }
                    
                    if (const auto* key = event->getIf<sf::Event::KeyPressed>())
                    {
                        if (key->scancode == sf::Keyboard::Scan::Escape ||
                            key->scancode == sf::Keyboard::Scan::Enter ||
                            key->scancode == sf::Keyboard::Scan::Space)
                        {
                            inControls = false;
                        }
                    }
                }
                
                window.clear(sf::Color::Black);
                draw_controls_screen(window);
                window.display();
            }
            break;
        }
            
        case MenuChoice::BestScore:
        {
            bool inBestScore = true;
            while (inBestScore && window.isOpen())
            {
                while (auto event = window.pollEvent())
                {
                    if (event->is<sf::Event::Closed>())
                    {
                        window.close();
                        return false;
                    }
                    
                    if (const auto* key = event->getIf<sf::Event::KeyPressed>())
                    {
                        if (key->scancode == sf::Keyboard::Scan::Escape ||
                            key->scancode == sf::Keyboard::Scan::Enter ||
                            key->scancode == sf::Keyboard::Scan::Space)
                        {
                            inBestScore = false;
                        }
                    }
                }
                
                window.clear(sf::Color::Black);
                draw_best_score_screen(window, bestScore);
                window.display();
            }
            break;
        }
            
        case MenuChoice::Quit:
            window.close();
            return false;
            
        default:
            break;
    }
    return false;
}

// Load best score from file
void loadBestScore(const std::string& filename, int& bestScore)
{
    std::ifstream readingScoreFile(filename, std::ios::in);
    if (readingScoreFile.is_open())
    {
        readingScoreFile >> bestScore;
        readingScoreFile.close();
    }
}

// Save best score to file
void saveBestScore(const std::string& filename, int bestScore)
{
    std::ofstream writingScoreFile(filename, std::ios::out);
    if (writingScoreFile.is_open())
    {
        writingScoreFile << bestScore;
        writingScoreFile.close();
    }
}

// Load sound effects
bool loadSounds(sf::SoundBuffer soundBuffers[], std::vector<std::unique_ptr<sf::Sound>>& sounds, const char* filenames[], size_t count)
{
    sounds.clear();
    
    for (size_t i = 0; i < count; ++i)
    {
        if (!soundBuffers[i].loadFromFile(filenames[i]))
        {
            std::cerr << "Failed to load sound: " << filenames[i] << std::endl;
            return false;
        }
        sounds.push_back(std::make_unique<sf::Sound>(soundBuffers[i]));
    }
    return true;
}

// Main game loop
void runGame()
{
    // Game state
    Grid grid(UI::row_number, UI::column_number);
    Piece current = grid.put_piece(createRandomPiece());
    PieceType next = createRandomPiece();
    bool isGameOver = false;
    bool isPaused = false;
    bool isQuit = false;
    bool goToMenu = false;
    double timeDecreaseRate = 0;
    double scoreThreshold = 200;
    
    // Initialize
    srand(static_cast<unsigned int>(time(nullptr)));
    grid = Grid(UI::row_number, UI::column_number);
    current = grid.put_piece(createRandomPiece());
    next = createRandomPiece();
    isGameOver = false;
    timeDecreaseRate = 0;
    scoreThreshold = 200;
    
    // Timing
    sf::Clock clock;
    UI::window.setFramerateLimit(60);
    
    // Load music
    sf::Music music;
    if (!music.openFromFile("../ui/sounds/music.ogg"))
    {
        std::cerr << "Failed to load music" << std::endl;
        return;
    }
    music.setLooping(true);
    music.setVolume(20.f);
    music.play();
    
    // Load sounds
    const char* soundFiles[] = {
        "../ui/sounds/clickleft.wav",
        "../ui/sounds/clickright.wav",
        "../ui/sounds/clockwise.wav",
        "../ui/sounds/anticlockwise.wav",
        "../ui/sounds/drop.wav",
        "../ui/sounds/success_linedisapear.wav",
        "../ui/sounds/higherlevelup.wav",
        "../ui/sounds/game_over.wav"
    };
    
    sf::SoundBuffer soundBuffers[8];
    std::vector<std::unique_ptr<sf::Sound>> sounds;
    
    if (!loadSounds(soundBuffers, sounds, soundFiles, 8))
    {
        std::cerr << "Failed to load sound effects" << std::endl;
        return;
    }
    
    // Set volumes
    sounds[0]->setVolume(10.f); // move left
    sounds[1]->setVolume(10.f); // move right
    sounds[2]->setVolume(10.f); // clockwise
    sounds[3]->setVolume(10.f); // anticlockwise
    sounds[4]->setVolume(15.f); // drop
    sounds[5]->setVolume(20.f); // success
    sounds[6]->setVolume(70.f); // level up
    sounds[7]->setVolume(60.f); // game over
    
    // Main loop
    while (UI::window.isOpen() && !isQuit && !goToMenu)
    {
        // Input handling based on state
        if (!isGameOver)
        {
            if (isPaused)
            {
                handlePauseInput(isPaused, isQuit, goToMenu, grid, current, next,
                                timeDecreaseRate, scoreThreshold, clock, music, *sounds[7]);
            }
            else
            {
                handleGameInput(grid, current, isPaused, isQuit, goToMenu,
                               *sounds[0], *sounds[1], *sounds[2], *sounds[3], *sounds[4]);
            }
        }
        else
        {
            handleGameOverInput(grid, current, next, isGameOver, isPaused, clock,
                               timeDecreaseRate, scoreThreshold, music, isQuit, goToMenu);
            
            if (goToMenu)
            {
                music.stop();
                continue;
            }
        }
        
        // Game update
        if (!isPaused && !isGameOver)
        {
            updateGame(grid, current, next, isGameOver, clock, timeDecreaseRate,
                      scoreThreshold, *sounds[4], *sounds[5], *sounds[6], *sounds[7],
                      music, bestScore);
        }
        
        // Rendering
        UI::window.clear(sf::Color::Black);
        
        if (!isGameOver)
        {
            draw_grid(grid, UI::window);
            draw_score(grid, UI::window);
            draw_next_piece(UI::window, next);
            draw_controls(UI::window);
            
            if (isPaused)
            {
                draw_pause_screen(UI::window);
            }
        }
        else
        {
            draw_game_over_screen(UI::window, static_cast<int>(grid.score()), bestScore);
        }
        
        UI::window.display();
        sf::sleep(sf::milliseconds(16));
    }
    
    // Cleanup
    music.stop();
    
    // Clear pending events
    while (auto ev = UI::window.pollEvent())
    {
        // Discard events
    }
}

// Main menu with improved navigation
bool showMainMenu(int bestScore)
{
    bool inMenu = true;
    MenuChoice menuSelection = MenuChoice::StartGame;
    
    while (inMenu && UI::window.isOpen())
    {
        while (auto event = UI::window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                UI::window.close();
                return false;
            }
            
            if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                // Navigation
                if (key->scancode == sf::Keyboard::Scan::Up)
                {
                    if (menuSelection == MenuChoice::StartGame)
                        menuSelection = MenuChoice::Quit;
                    else if (menuSelection == MenuChoice::Controls)
                        menuSelection = MenuChoice::StartGame;
                    else if (menuSelection == MenuChoice::BestScore)
                        menuSelection = MenuChoice::Controls;
                    else if (menuSelection == MenuChoice::Quit)
                        menuSelection = MenuChoice::BestScore;
                }
                else if (key->scancode == sf::Keyboard::Scan::Down)
                {
                    if (menuSelection == MenuChoice::StartGame)
                        menuSelection = MenuChoice::Controls;
                    else if (menuSelection == MenuChoice::Controls)
                        menuSelection = MenuChoice::BestScore;
                    else if (menuSelection == MenuChoice::BestScore)
                        menuSelection = MenuChoice::Quit;
                    else if (menuSelection == MenuChoice::Quit)
                        menuSelection = MenuChoice::StartGame;
                }
                // Selection
                else if (key->scancode == sf::Keyboard::Scan::Enter ||
                        key->scancode == sf::Keyboard::Scan::Space)
                {
                    switch (menuSelection)
                    {
                        case MenuChoice::StartGame:
                            inMenu = false;
                            return true;
                            
                        case MenuChoice::Controls:
                        {
                            bool inControls = true;
                            while (inControls && UI::window.isOpen())
                            {
                                // Handle controls screen
                                while (auto ev = UI::window.pollEvent())
                                {
                                    if (ev->is<sf::Event::Closed>())
                                    {
                                        UI::window.close();
                                        return false;
                                    }
                                    
                                    if (const auto* keyCtrl = ev->getIf<sf::Event::KeyPressed>())
                                    {
                                        if (keyCtrl->scancode == sf::Keyboard::Scan::Escape ||
                                            keyCtrl->scancode == sf::Keyboard::Scan::Enter ||
                                            keyCtrl->scancode == sf::Keyboard::Scan::Space)
                                        {
                                            inControls = false;
                                        }
                                    }
                                }
                                
                                UI::window.clear(sf::Color::Black);
                                draw_controls_screen(UI::window);
                                UI::window.display();
                            }
                            break;
                        }
                            
                        case MenuChoice::BestScore:
                        {
                            bool inBestScore = true;
                            while (inBestScore && UI::window.isOpen())
                            {
                                // Handle best score screen
                                while (auto ev = UI::window.pollEvent())
                                {
                                    if (ev->is<sf::Event::Closed>())
                                    {
                                        UI::window.close();
                                        return false;
                                    }
                                    
                                    if (const auto* keyScore = ev->getIf<sf::Event::KeyPressed>())
                                    {
                                        if (keyScore->scancode == sf::Keyboard::Scan::Escape ||
                                            keyScore->scancode == sf::Keyboard::Scan::Enter ||
                                            keyScore->scancode == sf::Keyboard::Scan::Space)
                                        {
                                            inBestScore = false;
                                        }
                                    }
                                }
                                
                                UI::window.clear(sf::Color::Black);
                                draw_best_score_screen(UI::window, bestScore);
                                UI::window.display();
                            }
                            break;
                        }
                            
                        case MenuChoice::Quit:
                            UI::window.close();
                            return false;
                            
                        default:
                            break;
                    }
                }
                else if (key->scancode == sf::Keyboard::Scan::Escape)
                {
                    UI::window.close();
                    return false;
                }
            }
        }
        
        // Draw menu
        UI::window.clear(sf::Color::Black);
        draw_menu_screen(UI::window, menuSelection, bestScore);
        UI::window.display();
    }
    
    return false;
}