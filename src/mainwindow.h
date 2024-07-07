///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Classe qui gère l'interface graphique du jeu d'échec.
///////////////////////////////////////////////////////////////////////////////
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton.h>
#include <QMessageBox>
#include "board.h"
#include "chessgame.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class vue::MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setupConnections();
    void initiateTests();

    void changeTurn();
    void resetTurnState();
    QPushButton* getButton(int row, int col) const;
    QPushButton* getButton(shared_ptr<modele::Square> square) const;

    void filterSquaresSelect();                                                             // Étape 1 : cliker sur la piece qu'on peut, elle ne peut pas etre vide ou posédé par une piece de l'autre joueur
    void filterPosibilities(shared_ptr<modele::Square> currentSquare);      // Étape 2 : filter les cases ou la piece peut aller

    void checkForEnd();

signals:
    void gridPressed(int row, int col);
    void boardChanged();
    void turnLabelChanged();

public slots:
    void bouttonCliqued(int row, int  colloun);
    void unSelect();
    void changeBoard();
    void initiateBoard();
    void changeTurnLabel();

private:
    Ui::MainWindow *ui;
    modele::Board* board_;
    modele::ChessGame* chessGame_;
    bool turn_ = true;                               // True = joueur 1 (white), False = joueur 2 (black)
    bool playerSelectedPiece_ = false;  // Étape 1  = false Étape 2 = true

    std::pair<int, int> currentPosition_;
    std::pair<int, int> nextPosition_;
};
#endif // MAINWINDOW_H
