///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente le roi.
///////////////////////////////////////////////////////////////////////////////
#include "king.h"
#include "board.h"

int modele::King::instanceCount = 0;

modele::King::King()
{
    incrementInsanceCount();
    if (instanceCount > 2) {
        throw KingsError("You cant have more than 2 kings!!!");
    }
    instanceCount++;
    color_ = false;
    value_ = B_KING;
}

modele::King::King(bool color)
{
    incrementInsanceCount();
    if (instanceCount > 2) {
        throw KingsError("You cant have more than 2 kings!!!");
    }
    color_ = color;
    if (color) {
        value_ = W_KING;
    }
    else {
        value_ = B_KING;
    }
}
modele::King::~King() {
    instanceCount--;
}

modele::King::King(const King& other) {
    if (this != &other) {
         value_ = other.value_;
         color_ = other.color_;
    }
}

modele::King& modele::King::operator=(const King& other) {
    if (this != &other) {
        value_ = other.value_;
        color_ = other.color_;
    }
    return *this;
}

void modele::King::resetInstanceCount() {
    instanceCount = 0;
}
void modele::King::incrementInsanceCount() {
    instanceCount++;
}

// Trouve les coups possibles pour une pièce sans tenir compte de la sécurité de son propre roi
vector<std::pair <int, int>> modele::King::getPossibleMoves(int newRow, int newColloun, Board* bard)
{
    vector<std::pair<int, int>> newMoves;
    vector<std::pair<int, int>> possiblities = { {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1}};

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

