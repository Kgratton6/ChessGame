///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente la reine.
///////////////////////////////////////////////////////////////////////////////
#ifndef QUEEN_H
#define QUEEN_H

#include "piece.h"

#include "namespaces.h"

class modele::Queen : public modele::Piece
{
public:
    Queen();
    Queen(bool color);
    ~Queen() = default;

    Queen(const Queen& other);
    Queen& operator=(const Queen& other);

    vector<std::pair <int, int>> getPossibleMoves(int newRow, int newColloun, Board* bard) override;
};

#endif // QUEEN_H
