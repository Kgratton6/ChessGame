///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente une pièce du jeu d'échec de
/// façon abstraite.
///////////////////////////////////////////////////////////////////////////////
#include "piece.h"

modele::Piece::Piece() :
    value_("-"),
    color_(false)
{
}
modele::Piece::Piece(bool color) :
    value_("-"),
    color_(color)
{
}
modele::Piece::Piece(const Piece& other) {
    if (this != &other) {
         value_ = other.value_;
         color_ = other.color_;
    }
}
modele::Piece& modele::Piece::operator=(const Piece& other) {
    if (this != &other) {
        value_ = other.value_;
        color_ = other.color_;
    }
    return *this;
}

QString modele::Piece::getValue() const {
    return value_;
}

bool modele::Piece::isWhite() const {
    return color_;
}

bool modele::Piece::getIsFirstMove() const {
    return isFirstMove_;
}
void modele::Piece::pieceMoved() {
    isFirstMove_ = false;
}
void modele::Piece::unmove() {
    isFirstMove_ = true;
}
