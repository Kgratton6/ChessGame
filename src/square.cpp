///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente une case destinée à faire
/// partie d'un échiquer. Elle détient donc une position sur l'échiquier, une
/// couleur et peut contenir une pièce.
///////////////////////////////////////////////////////////////////////////////
#include "square.h"

modele::Square::Square() :
    row_(0),
    column_(0)
{
}
modele::Square::Square(int row, int col) :
    row_(row),
    column_(col)
{
    chooseNormalColor(row, col);
    actualColor_ = nomalColor_;
}
modele::Square::Square(int row, int col, shared_ptr<Piece> piece) :
    row_(row),
    column_(col),
    piece_(piece)
{
    chooseNormalColor(row, col);
    actualColor_ = nomalColor_;
}

void modele::Square::chooseNormalColor(int row, int col) {
    if (row% 2 == 0){
        if (col % 2 == 0)
            nomalColor_ = QString("background-color: %1").arg(COLOR_BLACK);
        else
            nomalColor_ = QString("background-color: %1").arg(COLOR_WHITE);
    }
    else {
        if (col % 2 == 0)
            nomalColor_ = QString("background-color: %1").arg(COLOR_WHITE);
        else
            nomalColor_ = QString("background-color: %1").arg(COLOR_BLACK);
    }
}

int modele::Square::getPositionCol() const
{
    return column_;
}

int modele::Square::getPositionRow() const
{
    return row_;
}

shared_ptr<modele::Piece> modele::Square::getPiece() const {
    return  piece_;
}

void modele::Square::setPiece(shared_ptr<Piece> piece) {
    piece_ = piece;
}

void modele::Square::setColor(QString color)
{
    actualColor_ = color;
}
void modele::Square::setOriginalColor() {
    actualColor_ = nomalColor_;
}
QString modele::Square::getColor() const {
    return actualColor_;
}
bool modele::Square::isOccupied() const
{
    if (piece_ == nullptr) {
        return false;
    }
    else {
        return true;
    }
}
bool modele::Square::getPieceColor() const
{
    if (isOccupied() == false) {
        return false;
    }
    else {
         return piece_->isWhite();
    }
}
bool modele::Square::getPieceIsFirstMove() const {
    if (isOccupied() == false) {
        return false;
    }
    else {
          return piece_->getIsFirstMove();
    }
}
QString modele::Square::getPieceValue() const
{
    if (isOccupied() == false) {
        return EMPTY;
    }
    else {
         return piece_->getValue();
    }
}
