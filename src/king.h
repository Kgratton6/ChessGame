///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente le roi.
///////////////////////////////////////////////////////////////////////////////
#ifndef KING_H
#define KING_H

#include <cassert>
#include <stdexcept>
#include "piece.h"

#include "namespaces.h"

class KingsError : public logic_error
{
public:
    using logic_error::logic_error;      // Héritage des constructeurs
};

class modele::King : public modele::Piece
{
public:
    King();
    King(bool color);
    ~King();

    King(const King& other);
    King& operator=(const King& other);
    static void resetInstanceCount();
    static void incrementInsanceCount();

    vector<std::pair <int, int>> getPossibleMoves(int newRow, int newColloun, Board* bard) override;
private:
    static int instanceCount;
};

#endif // KING_H
