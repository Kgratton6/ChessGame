///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente le fou.
///////////////////////////////////////////////////////////////////////////////
#include "bishop.h"
#include "board.h"

modele::Bishop::Bishop()
{
    color_ = false;
    value_ = B_BISHOP;
}

modele::Bishop::Bishop(bool color)
{
    color_ = color;
    if (color) {
        value_ = W_BISHOP;
    }
    else {
        value_ = B_BISHOP;
    }
}

modele::Bishop::Bishop(const Bishop& other) {
    if (this != &other) {
         value_ = other.value_;
         color_ = other.color_;
    }
}

modele::Bishop& modele::Bishop::operator=(const Bishop& other) {
    if (this != &other) {
        value_ = other.value_;
        color_ = other.color_;
    }
    return *this;
}

// Trouve les coups possibles pour une pièce sans tenir compte de la sécurité de son propre roi
vector<std::pair <int, int>> modele::Bishop::getPossibleMoves(int newRow, int newColloun, Board* bard)
{
    vector<std::pair<int, int>> newMoves;
    vector<std::pair<int, int>> direction = { {1, 1}, {-1, 1}, {-1, -1}, {1, -1}};

    for (auto dir : direction) {
        int row = newRow + dir.first;
        int col = newColloun + dir.second;

        while (col<8 and col>=0 and row<8 and row>=0) {
            shared_ptr<Piece> piecePtr = bard->getPiece(row, col);
            if (piecePtr != nullptr) {
                if (piecePtr->isWhite() != this->isWhite())
                    newMoves.push_back({row, col});
                break;
            }
            newMoves.push_back({row, col});
            row += dir.first;
            col += dir.second;
        }
    }
    return newMoves;
}
