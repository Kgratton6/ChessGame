///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Ensemble de nos 2 différents namespaces :
///                          modèle et vue.
///////////////////////////////////////////////////////////////////////////////
#ifndef NAMESPACES_H
#define NAMESPACES_H

namespace modele
{
    class Piece;
    class King;
    class Knight;
    class Bishop;
    class Pawn;
    class Queen;
    class Rook;
    class Square;
    class Board;
    class ChessGame;
    class MoveRAII;
};

namespace vue
{
    class MainWindow;
};

#endif // NAMESPACES_H
