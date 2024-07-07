///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente l'échiquier dans un jeu
/// d'échec. Il est composé de cases qui elles-mêmes détiennent des pièces.
/// Celles ci appartiennent soit au joueur noir au blanc.
///////////////////////////////////////////////////////////////////////////////
#include "board.h"
#include "square.h"
#include <iostream>
#include "piece.h"
#include "queen.h"
#include "knight.h"
#include "king.h"
#include "rook.h"
#include "bishop.h"
#include "pawn.h"

modele::Board::Board() // Création d'un board vide. les squares ont des pointeurs piece égaux à nullptr, dont aucune piece
{
    clear();
}
modele::Board::Board(vector<shared_ptr<Square>> squares) :
    squares_(squares)
{
}
void modele::Board::clear() {
    King::resetInstanceCount();
    vector<shared_ptr<Square>> squares;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            shared_ptr<Square> newSquare = make_shared<Square>(i, j, nullptr);
            squares.push_back(newSquare);
        }
    }
    squares_ = squares;
    whitePieces_.clear();
    blackPieces_.clear();
}

shared_ptr<modele::Square> modele::Board::getSquare(int row, int col) const
{
    return squares_[8*row + col];
}

shared_ptr<modele::Piece> modele::Board::getPiece(int row, int col) const
{
    return getSquare(row, col)->getPiece();
}

void modele::Board::setPiece(int row, int col, shared_ptr<Piece> piece)
{
    if (piece->getValue() == W_KING)
        whiteKingSquare_ = getSquare(row, col);

    if (piece->getValue() == B_KING)
        blackKingSquare_ = getSquare(row, col);

    shared_ptr<Square> square = getSquare(row, col);
    square->setPiece(piece);
    if (piece->isWhite()) {
        whitePieces_.push_back(piece);
    }
    else {
        blackPieces_.push_back(piece);
    }
}

void modele::Board::setBlackKingSquare(shared_ptr<Square> square) {
    blackKingSquare_ = square;
}

void modele::Board::setWhiteKingSquare(shared_ptr<Square> square) {
    whiteKingSquare_ = square;
};

void modele::Board::resetColors(){
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++)
        {
            getSquare(row, col)->setOriginalColor();
        }
    }
}

const vector<shared_ptr<modele::Piece>>& modele::Board::getWhitePieces() const {
    return whitePieces_;
};

const vector<shared_ptr<modele::Piece>>& modele::Board::getBlackPieces() const {
    return blackPieces_;
};

const shared_ptr<modele::Square>& modele::Board::getBlackKingSquare() const {
    return blackKingSquare_;
};

const shared_ptr<modele::Square>& modele::Board::getWhiteKingSquare() const {
    return whiteKingSquare_;
};

std::pair<int, int> modele::Board::getKingPosition(bool color) const {
    if (color)
        return { whiteKingSquare_->getPositionRow(), whiteKingSquare_->getPositionCol() };
    return { blackKingSquare_->getPositionRow(), blackKingSquare_->getPositionCol() };
}

void modele::Board::addPiece(shared_ptr<Piece> piece) {
    if (piece->isWhite())
        whitePieces_.push_back(piece);
    else
        blackPieces_.push_back(piece);
};

void modele::Board::replacePiece(shared_ptr<Piece> pieceAdd, shared_ptr<Piece> pieceRemove) {
    for (shared_ptr<Square> square : squares_) {
        if (square->getPiece() == pieceRemove) {
            square->setPiece(pieceAdd);
            break;
        }
    }
};

void modele::Board::movePiece(int rowStart, int colStart, int rowFinish, int colFinish)
{
    shared_ptr<Piece> PieceStart = getPiece(rowStart, colStart);
    shared_ptr<Piece> PieceEnd = getPiece(rowFinish, colFinish);
    shared_ptr<Square> finishSquare = getSquare(rowFinish, colFinish);
    shared_ptr<Square> startSquare = getSquare(rowStart, colStart);

    PieceStart->pieceMoved();

    if (PieceStart->getValue() == W_KING)
        whiteKingSquare_ = finishSquare;
    else if (PieceStart->getValue() == B_KING)
        blackKingSquare_ = finishSquare;

    if ( rowFinish == 7 or rowFinish == 0) {
        if ( PieceStart->getValue()  == W_PAWN or PieceStart->getValue() == B_PAWN) {
            Queen newQueen { PieceStart->isWhite()};
            shared_ptr<Queen> newQueenPtr = make_shared<Queen>(newQueen);
            replacePiece(newQueenPtr, PieceStart);
            PieceStart = newQueenPtr;
        }
    }

    //Enlever la piece de la liste des pieces noir ou blanches
    if (PieceEnd != nullptr)
    {
        if (PieceEnd->isWhite())
        {
            for (int i = 0; i < whitePieces_.size(); i++) {
                if (PieceEnd == whitePieces_[i]) {
                    whitePieces_.erase(whitePieces_.begin() + i);
                    break;
                }
            }
        }
        else
        {
            for (int i = 0; i < blackPieces_.size(); i++) {
                if (PieceEnd == blackPieces_[i]) {
                    blackPieces_.erase(blackPieces_.begin() + i);
                    break;
                }
            }
        }
    }
    finishSquare->setPiece(PieceStart);
    startSquare->setPiece(nullptr);
}

void modele::Board::initiatePieces() {
    createRook(0, 0, false);
    createRook(0, 7, false);
    createKnight(0, 1, false);
    createKnight(0, 6, false);
    createBishop(0, 2, false);
    createBishop(0, 5, false);
    createQueen(0, 3, false );
    createKing(0, 4, false );
    for (int i = 0; i < 8; i++){
            createPawn(1, i, false );
    }
    createRook(7, 0, true);
    createRook(7, 7, true);
    createKnight(7, 1, true);
    createKnight(7, 6, true);
    createBishop(7, 2, true);
    createBishop(7, 5, true);
    createQueen(7, 3, true );
    createKing(7, 4, true );
    for (int i = 0; i < 8; i++){
            createPawn(6, i, true );
    }
}

void modele::Board::initiatePiecesTests() {
    createKing(0, 0, false);
    createRook(0, 1, false);
    createBishop(0, 2, false);
    createQueen(7, 0, true);
    createKnight(7, 1, true);
    createPawn(7, 2, true);
}

void modele::Board::initiatePiecesEndgame() {
    createKing(3, 2, false );
    createKing(7, 7, true );
    createKing(4, 4, true );
    createRook(1, 1, false );
    createBishop(2, 2, true );
    createPawn(1, 6, false );
}

void modele::Board::createKing(int row, int col, bool color) {
    try {
        setPiece(row, col, make_shared<King>( color ));
    }
    catch (KingsError& e) {
        QMessageBox messageErreur;
        messageErreur.critical(0, "Error :", e.what());
    }
}
void modele::Board::createQueen(int row, int col, bool color) {
    setPiece(row, col, make_shared<Queen>( color ));
}
void modele::Board::createRook(int row, int col, bool color) {
    setPiece(row, col, make_shared<Rook>( color ));
}
void modele::Board::createBishop(int row, int col, bool color) {
    setPiece(row, col, make_shared<Bishop>( color ));
}
void modele::Board::createKnight(int row, int col, bool color) {
    setPiece(row, col, make_shared<Knight>( color ));
}
void modele::Board::createPawn(int row, int col, bool color) {
    setPiece(row, col, make_shared<Pawn>( color ));
}

