///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui implémente le modèle d'une partie
/// d'échec en général. La classe contient alors un échiquier et connait c'est
/// au tour de qui de jouer.
///////////////////////////////////////////////////////////////////////////////
#include "ChessGame.h"
#include "piece.h"
#include "moveraii.h"

modele::ChessGame::ChessGame()
{
    board_ = new Board();
}

modele::ChessGame::~ChessGame() {
    delete board_;
}

void modele::ChessGame::changeTurn() {
    turn_ = !turn_;
}

void modele::ChessGame::resetTurnState() {
    turn_ = true;
}

modele::Board* modele::ChessGame::getBoard() const {
    return board_;
}

// Trouve si le mouvement d'une pièce d'une case à une autre case met le roi en danger
bool modele::ChessGame::isThreat(shared_ptr<Piece> piece, shared_ptr<Square> start, shared_ptr<Square> end, bool color) const
{
    bool result = false;
    std::pair<int, int> kingPosition = {board_->getBlackKingSquare()->getPositionRow(), board_->getBlackKingSquare()->getPositionCol()};

    // choix des pièces ennemies si c'est au tour blanc, pièces noires sont ennemies
    if (color == true) {
        kingPosition = {board_->getWhiteKingSquare()->getPositionRow(), board_->getWhiteKingSquare()->getPositionCol()};
    }

    MoveRAII tempMove(board_);
    tempMove.temporaryMove(start, end);

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            shared_ptr<Piece> piece = board_->getPiece(row, col);
            if (piece != nullptr and piece->isWhite() != color) {
                vector<std::pair<int, int>> possibleMoves = piece->getPossibleMoves(row, col, board_);
                if (color)
                    kingPosition = {board_->getWhiteKingSquare()->getPositionRow(), board_->getWhiteKingSquare()->getPositionCol()};
                else
                    kingPosition = {board_->getBlackKingSquare()->getPositionRow(), board_->getBlackKingSquare()->getPositionCol()};
                // Si le king est dans les coups possibles, il n'est pas safe donc isThreat = true
                if (std::find(possibleMoves.begin(), possibleMoves.end(), kingPosition) != possibleMoves.end())
                    result = true;
            }
        }
    }
    return result;
}

//Trouve si le joueur actuel possède une pièce qu'il peut bouger
bool modele::ChessGame::isMovePossible() const {
    // Trouver toutes les pièces de la couleur au tour de jouer
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            shared_ptr<Square> square = board_->getSquare(row, col);
            shared_ptr<Piece> piece = board_->getPiece(row, col);
            if (piece != nullptr and piece->isWhite() == turn_) {
                vector<pair<int, int>> moves = piece->getPossibleMoves(row, col, board_);

                // voir si un move est possible -> si oui pas égalité (pat) et pas checkmate
                for (pair<int, int> move : moves) {
                    shared_ptr<Square> squareEnd = board_->getSquare(move.first, move.second);
                    // il n'est pas possible de se déplacer sur une piece de sa couleur
                    if (squareEnd->getPiece() != nullptr and squareEnd->getPieceColor() == turn_);
                    else if (isThreat(piece, square, squareEnd, turn_) == false)
                        return true;
                }
            }
        }
    }
    return false;
}

//Trouve si le roi du joueur actuel est attaqué
bool modele::ChessGame::isAttacked() const {

    pair<int, int> kingPosition = board_->getKingPosition(turn_);

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            shared_ptr<Square> square = board_->getSquare(row, col);
            shared_ptr<Piece> piece = board_->getPiece(row, col);
            // Trouver les pièces ennemies
            if (piece != nullptr and piece->isWhite() != turn_) {
                vector<pair<int, int>> moves = piece->getPossibleMoves(row, col, board_);

                // Si le roi est dans les moves possibles => roi est attaqué
                for (pair<int, int> move : moves) {
                    if (move.first == kingPosition.first and move.second == kingPosition.second)
                        return true;
                }
            }
        }
    }
    return false;
}

void modele::ChessGame::initiateTests() {

    board_->clear();
    board_->initiatePiecesTests();

    // Tester la couleur des pieces :
    assert(false == board_->getPiece(0, 0)->isWhite());
    assert(false == board_->getPiece(0, 1)->isWhite());
    assert(false == board_->getPiece(0, 2)->isWhite());
    assert(false == board_->getPiece(0, 0)->isWhite());
    assert(false == board_->getPiece(0, 1)->isWhite());
    assert(false == board_->getPiece(0, 2)->isWhite());

    // Tester les types de pieces
    assert(B_KING == board_->getPiece(0, 0)->getValue());
    assert(B_ROOK == board_->getPiece(0, 1)->getValue());
    assert(B_BISHOP == board_->getPiece(0, 2)->getValue());
    assert(W_QUEEN == board_->getPiece(7, 0)->getValue());
    assert(W_KNIGHT == board_->getPiece(7, 1)->getValue());
    assert(W_PAWN == board_->getPiece(7, 2)->getValue());

    // Tester le changement de tour pour les joueurs
    assert(true == turn_);
    changeTurn();
    assert(false == turn_);
    resetTurnState();
    assert(true == turn_);

    board_->clear();
    board_->initiatePieces();

    // Tester les coups possibles pour pions blancs au début du jeu
    vector<std::pair <int, int>> testPossibleMoves;
    assert(testPossibleMoves == board_->getPiece(7,2)->getPossibleMoves(7, 2, board_)); // fou
    assert(testPossibleMoves == board_->getPiece(7,0)->getPossibleMoves(7, 0, board_)); // rook
    assert(testPossibleMoves == board_->getPiece(7,3)->getPossibleMoves(7, 3, board_)); // reine
    assert(testPossibleMoves == board_->getPiece(7,4)->getPossibleMoves(7, 4, board_)); // roi
    testPossibleMoves.insert(testPossibleMoves.end(), { {5,0}, {4, 0} });
    assert(testPossibleMoves == board_->getPiece(6,0)->getPossibleMoves(6, 0, board_)); // pion
    testPossibleMoves.clear();
    testPossibleMoves.insert(testPossibleMoves.end(), {{5, 0}, {5, 2}});
    assert(testPossibleMoves == board_->getPiece(7,1)->getPossibleMoves(7, 1, board_)); // cavalier

    // Tester les coups possibles pour les pions noirs au début du jeu
    testPossibleMoves.clear();
    assert(testPossibleMoves == board_->getPiece(0,2)->getPossibleMoves(0, 2, board_)); // fou
    assert(testPossibleMoves == board_->getPiece(0,0)->getPossibleMoves(0, 0, board_)); // rook
    assert(testPossibleMoves == board_->getPiece(0,3)->getPossibleMoves(0, 3, board_)); // reine
    assert(testPossibleMoves == board_->getPiece(0,4)->getPossibleMoves(0, 4, board_)); // roi
    testPossibleMoves.insert(testPossibleMoves.end(), { {2,0}, {3, 0} });
    assert(testPossibleMoves == board_->getPiece(1,0)->getPossibleMoves(1, 0, board_)); // pion
    testPossibleMoves.clear();
    testPossibleMoves.insert(testPossibleMoves.end(), {{2, 2}, {2, 0}});
    assert(testPossibleMoves == board_->getPiece(0,1)->getPossibleMoves(0, 1, board_)); // cavalier

    board_->clear();
    board_->initiatePiecesEndgame();
    assert(true == isMovePossible());

    // Position échec et mat
    board_->clear();
    board_->createKing(7, 0, true);
    board_->createKing(0, 5, false);
    board_->createQueen(6, 1, false);
    board_->createRook(4, 1, false);
    assert(true == isAttacked());
    assert(false == isMovePossible());

    // Position pat
    board_->clear();
    board_->createKing(7, 0, true);
    board_->createKing(0, 5, false);
    board_->createQueen(5, 1, false);
    board_->createRook(4, 1, false);
    assert(false == isAttacked());
    assert(false == isMovePossible());
    assert(true == isThreat(board_->getPiece(7,0), board_->getSquare(7, 0), board_->getSquare(7, 1), true));

    // Autres tests :
    //verifier le changements d'un pawn en queen
    board_->createPawn(6, 7, false);
    board_->movePiece(6, 7, 7, 7);
    assert(B_QUEEN == board_->getPiece(7, 7)->getValue());
}
