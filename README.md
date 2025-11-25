# 🎮 Tetrix Project

Un jeu Tetris classique développé en C++ avec interface graphique, réalisé en binôme.

## Binôme: 

    * Alexandre Bleuler 
    * Bonaventure Dohemeto
    

## Table des Matières

- [Description](#-description)
- [Fonctionnalités](#-fonctionnalités)
- [Aborescence du Projet](#-structure-du-projet)
- [Feuille de Route](#-feuille-de-route)

##  Description

**Tetrix Project** est une implémentation du célèbre jeu Tetris en C++ moderne.


###  Fonctionnalités A Implémentées
- [ ] Grille de jeu (10x20) standard
- [ ] Les 7 blocks classiques
- [ ] Système de rotation des pièces
- [ ] Mouvement (gauche/droite/descente rapide)
- [ ] Suppression des lignes complètes
- [ ] Système de scoring progressif
- [ ] Augmentation de la difficulté avec les niveaux
- [ ] Interface graphique
- [ ] Contrôles clavier


##  Aborescence du Projet

        TetrixProject/
        ├── src/ 
        │ ├── main.cpp 
        │ ├── Game.cpp # Logique principale du jeu
        │ ├── Grid.cpp # Gestion de la grille de jeu
        │ ├── Block.cpp # Définition des pièces 
        │ └── ResuGraphique.cpp # Interface graphique
        ├── include/ 
        │ ├── Game.h
        │ ├── Grid.h
        │ ├── Block.h
        │ └── ResuGraphique.h
        ├── tests/ # Tests unitaires
        │ ├── test_Grid.cpp
        │ ├── test_Block.cpp
        │ └── test_Game.cpp
        ├── CMakeLists.txt # Configuration CMake
        ├── .gitignore # Fichiers ignorés par Git
        └── README.md # Documentation du projet
 
#####################
## Feuille de Route##
#####################
## Tache 1: 
        - Initialisation Git et règles de collaboration
        - Squelette des classes principales
    
## Tache 2: Modules de Base

    -Grid:

        -Structure de données (10*20)
        -Détection des collisions
        -Verrouillage des blocks
        
    -Block:
    
        -Implémentation des 7 blocks
        -Système de rotation
        -Gestion des couleurs et états
        
## Tache 3: Logique

    Game:
        
        -Boucle de jeu
        -Gestion du temps
        -Génération aléatoire des blocks
        -Système de Scoring et Niveaux
        -Conditions de Game Over

## Tache 4: Interface Graphique / Sonorité et Autres

## Tache 5: Tests et finalisation


