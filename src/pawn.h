///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente le pion.
///////////////////////////////////////////////////////////////////////////////
#ifndef PAWN_H
#define PAWN_H

#include "piece.h"

#include "namespaces.h"

class modele::Pawn : public modele::Piece
{
public:
    Pawn();
    Pawn(bool color);
    ~Pawn() = default;

    Pawn(const Pawn& other);
    Pawn& operator=(const Pawn& other);

    vector<std::pair <int, int>> getPossibleMoves(int newRow, int newColloun, Board* bard) override;
};

#endif // PAWN_H
