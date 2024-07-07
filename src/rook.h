///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente la tour.
///////////////////////////////////////////////////////////////////////////////
#ifndef ROOK_H
#define ROOK_H

#include "piece.h"

#include "namespaces.h"

class modele::Rook : public modele::Piece
{
public:
    Rook();
    Rook(bool color);
    ~Rook() = default;

    Rook(const Rook& other);
    Rook& operator=(const Rook& other);

    vector<std::pair <int, int>> getPossibleMoves(int newRow, int newColloun, Board* bard) override;
};

#endif // ROOK_H
