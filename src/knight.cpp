///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente le cavalier.
///////////////////////////////////////////////////////////////////////////////
#include "knight.h"
#include "board.h"

modele::Knight::Knight()
{
    color_ = false;
    value_ = B_KNIGHT;
}

modele::Knight::Knight(bool color)
{
    color_ = color;
    if (color) {
        value_ = W_KNIGHT;
    }
    else {
        value_ = B_KNIGHT;
    }
}

modele::Knight::Knight(const Knight& other) {
    if (this != &other) {
         value_ = other.value_;
         color_ = other.color_;
    }
}

modele::Knight& modele::Knight::operator=(const Knight& other) {
    if (this != &other) {
        value_ = other.value_;
        color_ = other.color_;
    }
    return *this;
}

// Trouve les coups possibles pour une pièce sans tenir compte de la sécurité de son propre roi
vector<std::pair <int, int>> modele::Knight::getPossibleMoves(int newRow, int newColloun, Board* bard)
{
    vector<std::pair<int, int>> newMoves;
    vector<std::pair<int, int>> possiblities = { {1,2}, {2,1}, {2,-1}, {1,-2}, {-1, -2}, {-2,-1}, {-2,1}, {-1,2} };

    for (auto move: possiblities) {
        std::pair<int, int> newPosition = {newRow + move.first, newColloun + move.second};
        if (newPosition.first < 8 and newPosition.first >= 0 and
            newPosition.second < 8 and newPosition.second >= 0) {
            shared_ptr<Piece> piecePtr = bard->getPiece(newPosition.first, newPosition.second);
            if (piecePtr == nullptr or piecePtr->isWhite() != this->isWhite())
                newMoves.push_back(newPosition);
        }
    }

    return newMoves;
}
