///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente une case destinée à faire
/// partie d'un échiquer. Elle détient donc une position sur l'échiquier, une
/// couleur et peut contenir une pièce.
///////////////////////////////////////////////////////////////////////////////
#ifndef SQUARE_H
#define SQUARE_H

#include "piece.h"
#include <QString>

class modele::Square
{
public:
    Square();
    Square(int row, int col);
    Square(int row, int col, shared_ptr<Piece> piece);
    ~Square() = default;

    int getPositionCol() const ;
    int getPositionRow() const ;
    shared_ptr<Piece> getPiece() const ;
    void setPiece(shared_ptr<Piece> piece);

    QString getColor() const;
    void setColor(QString color);
    void setOriginalColor();

    bool isOccupied() const ;
    bool getPieceColor() const ;
    bool getPieceIsFirstMove() const;
    QString getPieceValue() const;

private:
    int row_;
    int column_;
    QString nomalColor_;
    QString actualColor_;
    shared_ptr<Piece> piece_;

    void chooseNormalColor(int row, int col);
};
#endif // SQUARE_H
