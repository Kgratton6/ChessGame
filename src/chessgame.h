///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente le modèle d'une partie
/// d'échec en général. La classe contient alors un échiquier et connait c'est
/// au tour de qui de jouer.
///////////////////////////////////////////////////////////////////////////////
#ifndef CHESSGAME_H
#define CHESSGAME_H


#include "board.h"

class modele::ChessGame
{
public:
    ChessGame();
    ~ChessGame();

    void changeTurn();      // Change le joueur à qui c'est le tour de jouer
    void resetTurnState();  // Tour au blanc par défaut (turn_ = true)

    // Vérifie si un mouvement metterait son roi en danger
    bool isThreat(shared_ptr<Piece> piece, shared_ptr<Square> start, shared_ptr<Square> end, bool color) const;
    // Vérifie si le joueur actuel possède au moins un mouvement légal à jouer
    bool isMovePossible() const;
    // Vérifie si le roi du joueur actuel se fait attaquer
    bool isAttacked() const;

    Board* getBoard() const;

    void initiateTests();

private:
    Board* board_;
    bool turn_ = true;       // True = joeur 1 (white), False = joueur 2 (black)
};

#endif // CHESSGAME_H
