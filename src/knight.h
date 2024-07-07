///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente le cavalier.
///////////////////////////////////////////////////////////////////////////////
#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"
#include "namespaces.h"

class modele::Knight : public modele::Piece
{
public:
    Knight();
    Knight(bool color);
    ~Knight() = default;

    Knight(const Knight& other);
    Knight& operator=(const Knight& other);

    vector<std::pair <int, int>> getPossibleMoves(int newRow, int newColloun, Board* bard) override;
};

#endif // KNIGHT_H
