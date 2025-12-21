# 🎮 Tetris Project

Un jeu Tetris classique développé en C++ avec interface graphique, réalisé en binôme.

## Binôme: 

    * Alexandre Bleuler 
    * Bonaventure Dohemeto

![Description de l'image](tetrominoes_notations.png)


## Table des Matières

- [Description](#-description) 
- [Fonctionnalités](#-fonctionnalités)
- [Déroulement du jeu/Coups valides et interdits](#-deroulement)
- [Aborescence du Projet](#-structure-du-projet)
- [Feuille de Route](#-feuille-de-route)


##  Description

**Tetris Project** est une implémentation du célèbre jeu Tetris en C++ moderne.


###  Fonctionnalités A Implémentées
- [ ] Grille de jeu (10x20) standard
- [ ] Les 7 pièces classiques
- [ ] Système de rotation des pièces
- [ ] Mouvement (gauche/droite/descente rapide)
- [ ] Suppression des lignes complètes
- [ ] Système de scoring progressif
- [ ] Augmentation de la difficulté avec les niveaux
- [ ] Interface graphique
- [ ] Contrôles clavier


## Déroulement du jeu/Coups valides et interdits

## Déroulement du jeu        

- [ ] Une pièce apparaît en haut de la grille.

- [ ] Le joueur peut la déplacer (haut, bas, droite,gauche) ou la faire tourner.

- [ ] La pièce tombe progressivement.

- [ ] Lorsqu’elle touche le bas ou un bloc déjà posé : elle se verrouille, on génère une nouvelle pièce.

- [ ] Les lignes complètes sont supprimées automatiquement.

- [ ] Le score augmente.

- [ ] La vitesse augmente au fur et à mesure des niveaux.

- [ ] Si une pièce ne peut pas apparaître (entièrement) => perdu.

## Coups valides

- [ ] Déplacements

        -Déplacer la pièce vers la gauche (si pas d’obstacle)

        -Déplacer la pièce vers la droite

        -Faire une descente rapide

        -Faire un hard drop (descente instantanée)

- [ ] Rotations

        -Tourner la pièce dans le sens horaire

        -Tourner la pièce dans le sens antihoraire

- [ ] Actions spéciales

        -Pause du jeu

- [ ] Actions de jeu correctes

        -Verrouiller une pièce lorsqu’elle touche le fond

        -Supprimer les lignes complètes

        -Passer au niveau supérieur

        -Engendrer une nouvelle pièce selon les règles

## Coups interdits

- [ ] Déplacements interdits

        -Sortir de la grille (à gauche, à droite ou sous le bas)

        -Monter la pièce vers le haut

        -Pénétrer dans un bloc déjà placé

        -Déplacer une pièce après qu’elle soit verrouillée

- [ ] Rotations invalides

        -Tourner si une rotation ferait sortir la pièce de la grille

        -Tourner si la pièce entre dans un bloc déjà occupé

        -Tourner alors que la pièce est déjà verrouillée

- [ ] Autres actions impossibles

        -Faire apparaître une nouvelle pièce si l’espace de spawn (l’endroit où les nouvelles pièces apparaissent au début) est occupé

        -Modifier le score de manière manuelle

        -Supprimer une ligne qui n’est pas entièrement remplie

        -Ralentir la gravité

        -Déplacer une pièce lorsque le jeu est en pause

##  Aborescence du Projet

        TetrisProject/
        ├── core/
        │ ├── include/
        │ │ └── core_class.h
        │ └── src/
        │   └── core_class.cpp
        │   └── main.cpp
        ├── doc/
        ├── sounds/
        │ ├── music.ogg
        │ ├── move.wav
        │ ├── rotate.wav
        │ └── drop.wav
        ├── tests/
        ├── CMakeLists.txt
        ├── DoxyFile
        ├── .gitignore
        └── README.md
 

### Architecture des Classes

1. **Block** : Représente un bloc individuel avec ses coordonnées (ligne, colonne)
2. **Cell** : Représente une cellule de la grille, pouvant être vide ou pleine
3. **Piece** : Groupe de 4 blocs formant une pièce Tetris, avec gestion des rotations
4. **Grid** : Grille de jeu contenant les cellules, gère la logique du jeu
5. **Enumérations** :
   - `Move` : Déplacements possibles (haut, bas, gauche, droite, rotations)
   - `PieceType` : Les 7 types de pièces Tetris

## Feuille de Route

### Tâche 1: Implémentation des classes de base ✓
- [x] Classe `Block`
- [x] Classe `Cell` 
- [x] Classe `Piece`
- [x] Classe `Grid`

### Tâche 2: Logique du jeu ✓
- [x] Mouvement des pièces
- [x] Rotation des pièces
- [x] Détection des collisions
- [x] Suppression des lignes complètes
- [x] Génération aléatoire des pièces

### Tâche 3: Interface graphique ✓
- [x] Affichage de la grille
- [x] Affichage des pièces
- [x] Contrôles clavier
- [x] Système audio

### Tâche 4: Fonctionnalités avancées
- [ ] Système de scoring (points par ligne, etc.)
- [ ] Niveaux de difficulté progressive
- [ ] Menu principal et écrans d'interface
- [ ] Sauvegarde des meilleurs scores
- [ ] Effets visuels (animations et autres)

### Tâche 5:

### Compilation avec CMake
```bash
mkdir build
cd build
cmake ..
make
./tetrix_game
        

    
       
        

