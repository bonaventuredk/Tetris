/**
 * \file ui.h
 * \brief  This file contains functions and variables declarations used to make the 
 * user interface of Tetris. Variables are encapsulated in the namespace UI.
 * \author Alexandre Bleuler - Bonaventure Dohemeto
 * \version 1.0
 * \date 23/12/2025
 */

#ifndef UI_INCLUDE
#define UI_INCLUDE

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio/Music.hpp>
#include <SFML/Audio/Sound.hpp>  
#include <SFML/Audio/SoundBuffer.hpp>  

/**
 * \namespace UI
 * \brief A namespace to store variables linked to the UI of the game.
 */

namespace UI
{ 
    extern unsigned int row_number; /**< Number of rows of the Tetris' grid. */
    extern unsigned int column_number; /**< Number of columns of the Tetris' grid. */

    extern sf::VideoMode current_video_mode; /**< The SFML window mode to display (fullscreen). */
    extern sf::RenderWindow window;
    extern unsigned int height_in_cell; /**< The height in cells of the window. */
    extern unsigned int pixel_cell_size; /**< The size in pixel of a Cell.*/
    extern unsigned int width_in_cell; /**< The width in cells of the window. */
    extern unsigned int left_side_width_in_cell; /**< The width in cells of the part of the window to the left of the grid. */
    extern unsigned int right_side_width_in_cell; /**< The width in cells of the part of the window to the right of the grid. */

    extern sf::RectangleShape cell; /**< An SFML rectangle to display Tetris' blocks. */

    constexpr sf::Color grey{110, 110, 110}; /**< Color grey for SFML. */
    constexpr sf::Color spawn_grey{70, 70, 70}; /**< Other color grey for SFML. */
    constexpr sf::Color orange{255, 128, 0}; /**< Color orange for SFML. */
    constexpr sf::Color pink{243 , 130, 185}; /**< Color pink for SFML. */
    constexpr sf::Color purple{224, 32, 255}; /**< Color purple for SFML. */

    extern sf::Font font; /**< A font for displaying texts with SFML (https://fontstruct.com/fontstructions/show/2350408). */
    extern unsigned int font_size; /**< The size of the font in pixels. */
};

/**
 * \brief A function to draw the cells of a Tetris' grid on screen.
 * \param grid The grid from which the cell come.
 * \param window The window on which the cell will be drawn.
 * \param cell_row The row of the top left cell of the grid.
 * \param cell_column The column of the top left cell of the grid.
 * \param row The row index of the cell in the grid.
 * \param column The column index of the cell in the grid.
 * \return 
 */


void draw_cell(Grid& grid, sf::RenderWindow& window, unsigned int cell_row, unsigned int cell_column, unsigned int row, unsigned int column);

/**
 * \brief A function to draw the Tetris' grid on screen.
 * \param grid The grid to draw.
 * \param window The window on which the grid will be drawn.
 * \return 
 */

void draw_grid(Grid& grid, sf::RenderWindow& window);

/**
 * \brief A function to center a text on a line of cells on sides of the Tetris' grid.
 * \param move Indicate if it has to be centered to the left or to the right of the grid.
 * \param text The text that has to be centered.
 * \param cell_row The column of the cell on which the text starts.
 * \return 
 */


void grid_sides_center_text(Move move, sf::Text& text, unsigned int cell_row);

/**
 * \brief A function to show the player's score on screen.
 * \param grid The current game's grid which contains the player's score.
 * \param window The window on which the score will be displayed.
 * \return 
 */

void draw_score(Grid& next_piece_grid, sf::RenderWindow& window);

/**
 * \brief A function to show the piece that the player will get the next turn.
 * \param window The window on which the next piece will be displayed.
 * \param newt_type The type of the next piece.
 * \return 
 */


void draw_next_piece(sf::RenderWindow& window, PieceType& next_type);

/**
 * @brief Draws the game over screen
 * @param window The render window
 * @param score Current score
 * @param bestScore Best score
 * \return 
 */
void draw_game_over_screen(sf::RenderWindow& window, int score, int bestScore);
/**
 * \brief A function to show game controls on screen.
 * \param window The window on which the controls will be displayed.
 * \return 
 */
void draw_controls(sf::RenderWindow& window);

/**
 * \brief A function to show pause screen.
 * \param window The window on which the pause screen will be displayed.
 * \return 
 */
 void draw_pause_screen(sf::RenderWindow& window);

/**
 * @brief Enumeration for menu choices
 * \return
 */
enum class MenuChoice {StartGame,Controls,BestScore,Quit,None};

/**
 * @brief Draws the main menu screen
 * @param window The render window
 * @param selectedChoice The currently selected menu option
 * @param bestScore The best score to display
 * \return
 */
void draw_menu_screen(sf::RenderWindow& window, MenuChoice selectedChoice, int bestScore);
/**
 * @brief Displays the main menu and handles menu navigation
 * @param currentBestScore The best score to display
 * @return The menu choice selected by the player
 * \return
 */
MenuChoice showMenu(int currentBestScore);
/**
 * @brief Displays the controls screen
 * @param window The render window
 */
void draw_controls_screen(sf::RenderWindow& window);

/**
 * @brief Displays the best score screen
 * @param window The render window
 * @param bestScore The best score to display
 */
void draw_best_score_screen(sf::RenderWindow& window, int bestScore);

/**
 * @brief Handles the menu navigation
 * @param selectedChoice Reference to the currently selected menu option
 * @param event The SFML event
 * @return True if a menu action was performed
 */
bool handleMenuNavigation(MenuChoice& selectedChoice, const sf::Event& event);

/**
 * @brief Executes the selected menu action
 * @param selectedChoice The menu choice selected
 * @param inMenu Reference to menu state flag
 * @param window Reference to the render window
 * @param bestScore The current best score
 * @return True if the game should start
 */
bool executeMenuAction(MenuChoice selectedChoice, bool& inMenu, 
                       sf::RenderWindow& window, int bestScore);

/**
 * @brief Initializes the game state
 * @details Sets up grid, current and next piece, and game parameters.
 * @param grid Reference to the game grid
 * @param current Reference to the current piece
 * @param next Reference to the next piece
 * @param gameOver Reference to the game over flag
 * @param timeDecreaseRate Reference to speed increase rate
 * @param scoreThreshold Reference to score threshold for level up
 */
void initializeGame(Grid& grid, Piece& current, PieceType& next, bool& gameOver, 
                    double& timeDecreaseRate, double& scoreThreshold);

/**
 * @brief Restarts the game
 * @details Resets the game to its initial state and restarts the music.
 */
void restartGame(Grid& grid, Piece& current, PieceType& next, bool& gameOver, 
                 bool& isPaused, sf::Clock& clock, double& timeDecreaseRate, 
                 double& scoreThreshold, sf::Music& music);

/**
 * @brief Handles player input during gameplay
 * @details Processes movement, rotation, drop, and menu navigation keys.
 */
void handleGameInput(Grid& grid, Piece& current, bool& isPaused, bool& isQuit,
                     bool& goToMenu, sf::Sound& moveLeftSound, sf::Sound& moveRightSound,
                     sf::Sound& clockwiseSound, sf::Sound& anticlockwiseSound,
                     sf::Sound& dropSound);

/**
 * @brief Handles input when game is paused
 * @details Allows resuming, quitting, or returning to menu while paused.
 */
void handlePauseInput(bool& isPaused, bool& isQuit, bool& goToMenu, Grid& grid,
                      Piece& current, PieceType& next, double& timeDecreaseRate,
                      double& scoreThreshold, sf::Clock& clock, sf::Music& music,
                      sf::Sound& pauseSound);

/**
 * @brief Handles input when game is over
 * @details Allows restarting or quitting the game after Game Over.
 */
void handleGameOverInput(Grid& grid, Piece& current, PieceType& next, 
                         bool& gameOver, bool& isPaused, sf::Clock& clock, 
                         double& timeDecreaseRate, double& scoreThreshold, 
                         sf::Music& music, bool& isQuit, bool& goToMenu);

/**
 * @brief Updates game logic: movement, collision, scoring
 * @details Updates piece position, checks for lines, updates score and speed.
 */
void updateGame(Grid& grid, Piece& current, PieceType& next, bool& gameOver,
                sf::Clock& clock, double& timeDecreaseRate, double& scoreThreshold,
                sf::Sound& dropSound, sf::Sound& successSound, sf::Sound& levelUpSound,
                sf::Sound& gameOverSound, sf::Music& music, int& bestScore);

/**
 * @brief Renders the current game state
 * @details Draws the grid, current and next pieces, and pause overlay if needed.
 */
void drawGame(sf::RenderWindow& window, Grid& grid, PieceType& next, bool isPaused);
/**
 * @brief Loads the best score from file
 * @param filename The name of the score file
 */
void loadBestScore(const std::string& filename, int& bestScore);

/**
 * @brief Saves the best score to file
 * @param filename The name of the score file
 */
void saveBestScore(const std::string& filename, int bestScore);

/**
 * @brief Loads all game sounds.
 *
 * @param soundBuffers Array of sound buffers to load.
 * @param sounds Vector of unique_ptr<sf::Sound> to store the sounds.
 * @param filenames Array of filenames corresponding to the sounds.
 * @param count Number of sounds to load.
 *
 * @note The sound effects were downloaded from Pixabay:
 *       https://pixabay.com/fr/sound-effects/search/musique-pour-tetris/ and
 *       https://www.voicy.network/fr/search/tetris-sound-effects
 *
 * @return True if all sounds were loaded successfully.
 */
bool loadSounds(sf::SoundBuffer soundBuffers[], std::vector<std::unique_ptr<sf::Sound>>& sounds, const char* filenames[], size_t count);

/**
 * @brief Runs the main game loop.
 *
 * @details This function initializes the game state and continuously updates,
 * processes events, and renders graphics until the game is exited.
 */
void runGame();

/**
 * @brief Main menu loop
 * @return True if game should start, false if should quit
 */
bool showMainMenu(int bestScore);


#endif
