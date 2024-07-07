///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui gère l'interface graphique du jeu d'échec.
///////////////////////////////////////////////////////////////////////////////
#include "mainwindow.h"
#include "piece.h"
#include "board.h"
#include "./ui_mainwindow.h"
#include "chessgame.h"

vue::MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupConnections();
    ui->normalGameButton->setChecked(true);
    initiateBoard();
    setWindowTitle( "Chess game : Kevin Gratton and Charles-Olivier Lemay");
}
vue::MainWindow::~MainWindow()
{
    delete ui;
    delete board_;
    delete chessGame_;
}

void vue::MainWindow::setupConnections()
{
    connect(ui->undoSelectionButton, SIGNAL(clicked()), this, SLOT(unSelect()));
    connect(ui->buttonRestartGame, SIGNAL(clicked()), this, SLOT(initiateBoard()));
    connect(this, SIGNAL(turnLabelChanged()), this, SLOT(changeTurnLabel()));

    connect(this, SIGNAL(gridPressed(int,int)), this, SLOT(bouttonCliqued(int,int)));
    connect(this, SIGNAL(boardChanged()), this, SLOT(changeBoard()));

    for(int row = 0; row < 8; row++)
    {
        for(int col = 0; col < 8; col++)
        {
            QLayoutItem* item = ui->gridBoard->itemAtPosition(row, col);
            QWidget* widget = item->widget();
            QPushButton* button = dynamic_cast<QPushButton*>(widget);

            connect(button, &QPushButton::clicked, this, [=](){
                            emit gridPressed(row,col);
                        });
        }
    }
}

void vue::MainWindow::initiateBoard()
{
    chessGame_ = new modele::ChessGame();
    board_ = chessGame_->getBoard();
    board_->clear();
    resetTurnState();

    if (ui->normalGameButton->isChecked()) {
        board_->initiatePieces();
    }
    else {
        board_->initiatePiecesEndgame();
    }

    filterSquaresSelect();
    board_->resetColors();
    ui->statusbar->showMessage(EMPTY);
    emit boardChanged();
}

void vue::MainWindow::unSelect() {
    board_->resetColors();
    filterSquaresSelect();
    playerSelectedPiece_ = false;
    emit boardChanged();
}

void vue::MainWindow::changeTurn() {
    turn_ = !turn_;
    chessGame_->changeTurn();
    emit turnLabelChanged();
}

void vue::MainWindow::resetTurnState() {
    playerSelectedPiece_ = false;
    turn_ = true;
    chessGame_->resetTurnState();
    emit turnLabelChanged();
}

QPushButton* vue::MainWindow::getButton(int row, int col) const {
    return  dynamic_cast<QPushButton*>(ui->gridBoard->itemAtPosition(row, col)->widget());
}
QPushButton* vue::MainWindow::getButton(shared_ptr<modele::Square> square) const {
    return  dynamic_cast<QPushButton*>(ui->gridBoard->itemAtPosition(square->getPositionRow(), square->getPositionCol())->widget());
}

void vue::MainWindow::changeTurnLabel() {
    if (turn_) {
        ui->currentTurnLabel->setText("White");
    }
    else {
        ui->currentTurnLabel->setText("Black");
    }
}

// Désactive toutes les Squares ou le joueur n'a pas de piece pour lui permettre de choisir une piece a bouger
void vue::MainWindow::filterSquaresSelect() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++)
        {
              shared_ptr<modele::Square> square = board_->getSquare(row, col);

            if (square->isOccupied() == true and turn_ == square->getPieceColor())  {
                getButton(square)->setDisabled(false);
            }
            else {
               getButton(square)->setDisabled(true);
            }
        }
    }
}

// active seulement les boutons où le joueur peut aller une fois sa pièce choisie
void vue::MainWindow::filterPosibilities(shared_ptr<modele::Square> currentSquare)
{
     // Desactiver tous les boutons
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++)
        {
            getButton(row, col)->setDisabled(true);
        }
   }

    // Réactiver les bouton ou le joueur peut aller et les mettre en couleur
   vector<std::pair<int, int>> possiblesMoves = currentSquare->getPiece()->getPossibleMoves(currentPosition_.first, currentPosition_.second, board_);
   for (auto move : possiblesMoves)
   {
        shared_ptr<modele::Square> possibleSquare = board_->getSquare(move.first, move.second);

        if (chessGame_->isThreat(currentSquare->getPiece(), currentSquare, possibleSquare, turn_)) {
            ;
        }
        else if (possibleSquare->isOccupied() == true) {
            if (possibleSquare->getPieceColor() != turn_) {
                 possibleSquare->setColor(POSSBLE_MOVE_COLOR);
                 getButton(possibleSquare)->setDisabled(false);
            }
        }
        else {
            possibleSquare->setColor(POSSBLE_MOVE_COLOR);
            getButton(possibleSquare)->setDisabled(false);
        }
    }
}

void vue::MainWindow::checkForEnd() {
    if (chessGame_->isMovePossible() == false) {
        if (chessGame_->isAttacked() == true) {
            if (turn_ == true) {
                ui->statusbar->showMessage("Black player won");
            }
            else {
                ui->statusbar->showMessage("White player Won");
            }
        }
        else
            ui->statusbar->showMessage("Pat");
    }
}

void vue::MainWindow::bouttonCliqued(int row, int  colloun)
{
    playerSelectedPiece_ = !playerSelectedPiece_;
    shared_ptr<modele::Square> currentSquare = board_->getSquare(row, colloun);

    if (playerSelectedPiece_)  // État 1
    {
        currentPosition_ = {row, colloun};
        currentSquare->setColor(SELECT_COLOR);
        filterPosibilities(currentSquare);
    }
    else                                    // État 2
    {
        nextPosition_ = {row, colloun};
        changeTurn();

        board_->movePiece(currentPosition_.first, currentPosition_.second, nextPosition_.first, nextPosition_.second );
        board_->resetColors();

        filterSquaresSelect();
        checkForEnd();
    }
    emit boardChanged();
}

void vue::MainWindow::changeBoard() {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++)
        {
            shared_ptr<modele::Square> square = board_->getSquare(row, col);
            QPushButton* button = getButton(square);

            button->setText(square->getPieceValue());
            button->setStyleSheet(square->getColor());
        }
    }
}
