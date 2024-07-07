///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente la reine.
///////////////////////////////////////////////////////////////////////////////
#include "queen.h"
#include "board.h"

modele::Queen::Queen()
{
    color_ = false;
    value_ = B_QUEEN;
}

modele::Queen::Queen(bool color)
{
    color_ = color;
    if (color) {
        value_ = W_QUEEN;
    }
    else {
        value_ = B_QUEEN;
    }
}

modele::Queen::Queen(const Queen& other) {
    if (this != &other) {
        value_ = other.value_;
        color_ = other.color_;
    }
}

modele::Queen& modele::Queen::operator=(const Queen& other) {
    if (this != &other) {
        value_ = other.value_;
        color_ = other.color_;
    }
    return *this;
}

// Trouve les coups possibles pour une pièce sans tenir compte de la sécurité de son propre roi
vector<std::pair <int, int>> modele::Queen::getPossibleMoves(int newRow, int newColloun, Board* bard)
{
    vector<std::pair<int, int>> newMoves;
   vector<std::pair<int, int>> direction = { {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

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

