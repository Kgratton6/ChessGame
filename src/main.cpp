///////////////////////////////////////////////////////////////////////////////
/// Travail : Jeu d'échecs
/// Section # : 5
/// Auteurs : Kevin Gratton, Charles-Olivier Lemay
///
/// Description du fichier : Programme permettant le lancement d'un jeu d'échec
/// possédant une interface graphique.
///////////////////////////////////////////////////////////////////////////////
#include "mainwindow.h"
#include "chessgame.h"
#include <QApplication>
#include <QPalette>

int main(int argc, char *argv[])
{
    modele::ChessGame testGame;
    testGame.initiateTests();

    QApplication a(argc, argv);
    vue::MainWindow w;
    w.show();

    return a.exec();
}
