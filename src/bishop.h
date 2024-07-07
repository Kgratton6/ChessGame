///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente le fou.
///////////////////////////////////////////////////////////////////////////////
#ifndef BISHOP_H
#define BISHOP_H


#include "piece.h"

#include "namespaces.h"

class modele::Bishop : public modele::Piece
{
public:
    Bishop();
    Bishop(bool color);
    ~Bishop() = default;

    Bishop(const Bishop& other);
    Bishop& operator=(const Bishop& other);

    vector<std::pair <int, int>> getPossibleMoves(int newRow, int newColloun, Board* bard) override;
};

#endif // BISHOP_H
