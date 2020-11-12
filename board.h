#ifndef BOARD_H
#define BOARD_H

#include <QWidget>
#include <QPushButton>
#include <QMouseEvent>
#include "square.h"
#include "move.h"
#include "engine.h"

class Board : public QWidget
{
    Q_OBJECT
public:
    int xPos, yPos, width, border;
    int pieceType = 1;

    QPushButton *backButton;
    Square * square[8][8];
    int count = 0;
    int turn  = pieceType;
    int last[2];
    int VIRTUALBOARD[8][8];
    int CURRENTBOARD[8][8];
    int BOARDTYPE;

    Move   * M      = new Move(pieceType);
    Engine * ENGINE = new Engine();

    Board(int BOARDTYPE);
    void chessBoard();
    void outline(int xPos, int yPos, int Pos);
    void fillTheBoard();
    void initBoard();
    void removeSelectedSquare();
    void selectSquare(int i, int j);
    void selectPossibilityOfMovment(int from[2]);
    void playHVsH  (int i, int j);
    void PlayMinmax(int i, int j);
    void PlayMCTS  (int i, int j);
    void check();

public slots:
    void handleSquare(int i, int j);
};

#endif // BOARD_H
