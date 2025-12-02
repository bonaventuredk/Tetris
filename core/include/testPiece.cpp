#include <iostream>
#include <vector>
#include <string>
#include <cassert>

#include "core_class.h"

//Test de Piece
void printPieceInfo(const Piece& piece, const std::string& testName) {
    std::cout << "\n=== " << testName << " ===" << std::endl;
    std::cout << "Type de piece: ";
    
    switch(piece.type()) {
        case PieceType::I: std::cout << "I"; break;
        case PieceType::O: std::cout << "O"; break;
        case PieceType::T: std::cout << "T"; break;
        case PieceType::J: std::cout << "J"; break;
        case PieceType::L: std::cout << "L"; break;
        case PieceType::S: std::cout << "S"; break;
        case PieceType::Z: std::cout << "Z"; break;
    }
    
    std::cout << "\nPivot: (" << piece.pivot_row() << ", " << piece.pivot_col() << ")";
    std::cout << "\nBlocs (" << piece.size() << "):\n";
    
    auto blocks = piece.getBlocks();
    for(size_t i = 0; i < blocks.size(); ++i) {
        std::cout << "  Bloc " << i << ": (" 
                  << blocks[i].row() << ", " 
                  << blocks[i].column() << ")\n";
    }
}

void testCreation() {
    std::cout << "\n TEST DE CREATION \n";
    Piece pieceI(PieceType::I, 0, 0);
    Piece pieceO(PieceType::O, 0, 0);
    // Test avec position de pivot différente
    Piece pieceT2(PieceType::T, 5, 3);
}

void testMouvements() {
    std::cout << "\n\n TEST DES MOUVEMENTS\n";
    
    Piece piece(PieceType::T, 0, 0);
    printPieceInfo(piece, "Position initiale");
    
    // Déplacement vers la droite
    piece.move(Move::right, 3);
    printPieceInfo(piece, "Apres deplacement droit de 3");
    
    // Déplacement vers le bas
    piece.move(Move::down, 2);
    printPieceInfo(piece, "Apres deplacement bas de 2");
    
    // Déplacement vers la gauche
    piece.move(Move::left, 1);
    printPieceInfo(piece, "Apres deplacement gauche de 1");
    
    // Déplacement vers le haut
    piece.move(Move::up, 1);
    printPieceInfo(piece, "Apres deplacement haut de 1");
}
void testRotations() {
    std::cout << "\n\n TEST DES ROTATIONS\n";
    
    Piece piece(PieceType::T, 3, 3);
    printPieceInfo(piece, "Position initiale");
    
    // Rotation directe
    piece.rotateDirect();
    printPieceInfo(piece, "Apres rotation directe");
    
    // Test rotation indirecte
    piece.rotateIndirect();
    printPieceInfo(piece, "Apres rotation indirecte");
    
}
int main()
{
    std::cout << "Piece Test";
    std::cout << "\n";

    //testCreation();
    testMouvements();
    testRotations();
    return 0;
}