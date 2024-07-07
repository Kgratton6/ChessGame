///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui permet de faire un mouvement temporaire
/// qui sera défait lors de la destruction de l'instance de la classe. Cela offre
/// le comportement désiré pour un seul déplacement pour chaque instanciation.
///////////////////////////////////////////////////////////////////////////////
#include "moveraii.h"
#include "board.h"
#include "pawn.h"

modele::MoveRAII::MoveRAII(modele::Board* board) :
    board_(board)
{};

modele::MoveRAII::~MoveRAII()
{
    board_->movePiece(finishSquare_->getPositionRow(), finishSquare_->getPositionCol(),
                      originalSquare_->getPositionRow(), originalSquare_->getPositionCol());

    if (isOriginalPawn_ == true) {
        modele::Pawn newPawn { movedPiece_->isWhite()};
        shared_ptr<modele::Pawn> newPawnPtr = make_shared<modele::Pawn>(newPawn);
        // Remettre si le pion a déjà bougé ou non
        if (isOriginalFirstMove_ == false)
            newPawnPtr->pieceMoved();

        board_->replacePiece(newPawnPtr, movedPiece_);
    }

    if (endPiece_ != nullptr) {
        finishSquare_->setPiece(endPiece_);
        board_->addPiece(endPiece_);
    }

    if (isOriginalFirstMove_ == true) {
        movedPiece_->unmove();
    }
};

void modele::MoveRAII::temporaryMove(shared_ptr<modele::Square> startingSquare, shared_ptr<modele::Square> finishSquare)
{
    movedPiece_ = startingSquare->getPiece();
    endPiece_ = finishSquare->getPiece();

    isOriginalFirstMove_ = movedPiece_->getIsFirstMove();

    if (movedPiece_->getValue() == W_PAWN or movedPiece_->getValue() == B_PAWN)
        isOriginalPawn_ = true;

    originalSquare_ = startingSquare;
    finishSquare_ = finishSquare;

    board_->movePiece(originalSquare_->getPositionRow(), originalSquare_->getPositionCol(),
                      finishSquare_->getPositionRow(), finishSquare_->getPositionCol());

    // le pointeur a peut être changé pour une reine
    movedPiece_ = finishSquare_->getPiece();
};
