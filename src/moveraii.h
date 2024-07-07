///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui permet de faire un mouvement temporaire
/// qui sera défait lors de la destruction de l'instance de la classe. Cela offre
/// le comportement désiré pour un seul déplacement pour chaque instanciation.
///////////////////////////////////////////////////////////////////////////////
#ifndef MOVERAII_H
#define MOVERAII_H

#include "board.h"
#include "square.h"
#include "piece.h"

class modele::MoveRAII
{
public:
    MoveRAII(modele::Board* board);

    ~MoveRAII();

    void temporaryMove(shared_ptr<modele::Square> originalSquare_, shared_ptr<modele::Square> finishSquare);

private:
    shared_ptr<modele::Square> originalSquare_;  // case originale
    shared_ptr<modele::Square> finishSquare_;    // case finale

    shared_ptr<modele::Piece> movedPiece_;  // pièce sur la case originale
    shared_ptr<modele::Piece> endPiece_;    // pièce sur la case finale

    modele::Board* board_;

    bool isOriginalFirstMove_;      // savoir si la pièce n'a pas encore été bougée
    bool isOriginalPawn_ = false;   // savoir si la pièce était un pion (possiblement avant
                                    //                                   de devenir une reine)
};

#endif // MOVERAII_H
