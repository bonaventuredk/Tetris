/**
 * \file main.cpp
 * \brief Main game execution file
 * \author Alexandre Bleuler - Bonaventure Dohemeto
 * \version 2.0
 * \date 30/12/2025
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
    const std::string scoreFileName = "best_score.txt";
    int bestScore = 0;
    
    loadBestScore(scoreFileName, bestScore);
    
    // Main program loop
    bool running = true;
    while (running && UI::window.isOpen())
    {
        // Clear any pending events
        while (auto ev = UI::window.pollEvent()) { (void)ev; }
        
        // Show main menu
        bool startGame = showMainMenu(bestScore);
        
        if (startGame)
        {
            // Run the game 
            runGame();
            
            // Save best score after game ends
            saveBestScore(scoreFileName, bestScore);
            
            // Clear events before returning to menu
            while (auto ev = UI::window.pollEvent()) { (void)ev; }
            
        }
        else
        {
            running = false;
        }
    }
    
    saveBestScore(scoreFileName, bestScore);
    
    return 0;
}