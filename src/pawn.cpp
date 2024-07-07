///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente le pion.
///////////////////////////////////////////////////////////////////////////////
#include "pawn.h"
#include "board.h"

modele::Pawn::Pawn()
{
    color_ = false;
    value_ = B_PAWN;
}

modele::Pawn::Pawn(bool color)
{
    color_ = color;
    if (color) {
        value_ = W_PAWN;
    }
    else {
        value_ = B_PAWN;
    }
}

modele::Pawn::Pawn(const Pawn& other) {
    if (this != &other) {
         value_ = other.value_;
         color_ = other.color_;
    }
}

modele::Pawn& modele::Pawn::operator=(const Pawn& other) {
    if (this != &other) {
        value_ = other.value_;
        color_ = other.color_;
    }
    return *this;
}

// Trouve les coups possibles pour une pièce sans tenir compte de la sécurité de son propre roi
vector<std::pair <int, int>> modele::Pawn::getPossibleMoves(int newRow, int newColloun, Board* bard)
{
    vector<std::pair<int, int>> newMoves;
    vector<std::pair<int, int>> direction;
    vector<std::pair<int, int>> diagonale;

   if (!color_) {
       direction = { {1, 0} };
       diagonale = { {1, 1}, {1, -1}};
   }
   else {
       direction = { {-1, 0} };
       diagonale = { {-1, 1}, {-1, -1}};
   }

   int countDirection;
   if (isFirstMove_) {
       countDirection = 0;
   }
   else {
       countDirection = 1;
   }

   for (auto dir : direction) {

       int row = newRow + dir.first;
       int col = newColloun + dir.second;

       while (col<8 and col>=0 and row<8 and row>=0) {
           if (countDirection > 1) {
               break;
           }
           shared_ptr<Piece> piecePtr = bard->getPiece(row, col);
           if (piecePtr != nullptr) {
               break;
           }
           newMoves.push_back({row, col});
           row += dir.first;
           col += dir.second;
           countDirection++;
       }
   }

   for (auto dir: diagonale) {
       int row = newRow + dir.first;
       int col = newColloun + dir.second;
       std::pair<int, int> newPosition = {newRow + dir.first, newColloun + dir.second};
       if (newPosition.first < 8 and newPosition.first >= 0 and
           newPosition.second < 8 and newPosition.second >= 0) {
           shared_ptr<Piece> piecePtr2 = bard->getPiece(row, col);
           if (piecePtr2 != nullptr) {
               newMoves.push_back({row, col});
           }
       }
   }
   return newMoves;
}

