///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente une pièce du jeu d'échec de
/// façon abstraite.
///////////////////////////////////////////////////////////////////////////////
#ifndef PIECE_H
#define PIECE_H

#include "namespaces.h"
#include <memory>
#include <QString>
using namespace std;

#define W_KING        "♔"
#define W_QUEEN    "♕"
#define W_ROOK       "♖"
#define W_BISHOP   "♗"
#define W_KNIGHT  "♘"
#define W_PAWN      "♙"
#define B_KING        "♚"
#define B_QUEEN    "♛"
#define B_ROOK       "♜"
#define B_BISHOP   "♝"
#define B_KNIGHT  "♞"
#define B_PAWN      "♟︎"
#define EMPTY " "

#define COLOR_WHITE "rgb(237, 222, 200);color: rgb(0, 0, 0);"
#define COLOR_BLACK "rgb(175, 135, 108);color: rgb(0, 0, 0);"
#define SELECT_COLOR "color: rgb(0, 0, 0)"
#define POSSBLE_MOVE_COLOR "background-color: rgb(59, 134, 65); color: rgb(0, 0, 0);"

class modele::Piece
{
public:
    Piece();
    Piece(bool color);
    ~Piece() = default;

    Piece(const Piece& other);
    Piece& operator=(const Piece& other);

    QString getValue() const;
    bool  isWhite() const;
    bool getIsFirstMove() const;
    void pieceMoved();
    void unmove();

    virtual vector<std::pair<int, int>> getPossibleMoves(int newRow, int newColloun, class Board* bard) = 0;

protected:
    QString value_;          // string pour representer la piece
    bool color_;                 // true = white, false = black
    bool isFirstMove_ = true;
};

#endif // PIECE_H
