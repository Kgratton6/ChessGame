///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente l'échiquier dans un jeu
/// d'échec. Il est composé de cases qui elles-mêmes détiennent des pièces.
/// Celles ci appartiennent soit au joueur noir au blanc.
///////////////////////////////////////////////////////////////////////////////
#ifndef BOARD_H
#define BOARD_H

#include "piece.h"
#include "square.h"
#include "QMessageBox"

class modele::Board
{
public:
    Board();
    Board(vector<shared_ptr<Square>> squares);
    ~Board() = default;

    void clear();

    shared_ptr<Square> getSquare(int row, int col) const;
    shared_ptr<Piece> getPiece(int row, int col) const;
    void setPiece(int row, int col, shared_ptr<Piece> piece);

    const vector<shared_ptr<Piece>>& getWhitePieces() const;
    const vector<shared_ptr<Piece>>& getBlackPieces() const;
    const shared_ptr<Square>& getBlackKingSquare() const;
    const shared_ptr<Square>& getWhiteKingSquare() const;
    std::pair<int, int> getKingPosition(bool color) const;

    void setBlackKingSquare(shared_ptr<Square>);
    void setWhiteKingSquare(shared_ptr<Square>);

    void addPiece(shared_ptr<Piece> piece);
    void replacePiece(shared_ptr<Piece> pieceAdd, shared_ptr<Piece> pieceRemove);

    void resetColors();

    void createKing(int row, int col, bool color);
    void createQueen(int row, int col, bool color);
    void createRook(int row, int col, bool color);
    void createBishop(int row, int col, bool color);
    void createKnight(int row, int col, bool color);
    void createPawn(int row, int col, bool color);

    void initiatePieces();
    void initiatePiecesTests();
    void initiatePiecesEndgame();

    //Bouger une piece d'une case à une autre et si une piece est enlevé, on l'enleve dans la bonne liste
    void movePiece(int rowStart, int colStart, int rowFinish, int colFinish);

private:
    vector<shared_ptr<Square>> squares_;
    vector<shared_ptr<Piece>> whitePieces_;
    vector<shared_ptr<Piece>> blackPieces_;

    shared_ptr<Square> whiteKingSquare_;
    shared_ptr<Square> blackKingSquare_;
};

#endif // BOARD_H
