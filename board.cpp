#include "board.h"
#include "mainwindow.h"
#include <QString>
#include <iostream>
#include <QMessageBox>



Board::Board(int B_TYPE)
{
    this->xPos  = 330;
    this->yPos  =  60;
    this->width = 512;
    this->border=  10;
    this->BOARDTYPE = B_TYPE;

    backButton = new QPushButton("Back",this);
    backButton->move(100, 100);

    initBoard();
    chessBoard();
}

void Board::handleSquare(int i, int j){
    if     (this->BOARDTYPE == 1)
        playHVsH  ( i, j);
    else if(this->BOARDTYPE == 2)
        PlayMinmax( i, j);
    else if(this->BOARDTYPE == 3)
        PlayMCTS  ( i, j);
}

void Board::outline(int xPos, int yPos, int Pos)
{
     QLabel *outLabel = new QLabel(this);

    if(!Pos)
        outLabel->setGeometry(xPos, yPos, this->width + 2*this->border, this->border);

    else
        outLabel->setGeometry(xPos, yPos,  this->border, this->width);

    outLabel->setStyleSheet("QLabel { background-color :rgb(170, 170, 127); color : black; }");
}

void Board::chessBoard(){
    int hor,ver;

    outline(this->xPos                             , this->yPos                             , 0);
    outline(this->xPos                             , this->yPos + this->width + this->border, 0);
    outline(this->xPos                             , this->yPos + this->border              , 1);
    outline(this->xPos + this->width + this->border, this->yPos + this->border              , 1);

    ver = this->yPos + this->border;
    for(int i=0; i<8; i++)
    {
        hor = this->xPos + this->border;
        for(int j=0; j<8; j++)
        {
            this->square[i][j] = new Square(this);
            this->square[i][j]->squareColor=(i+j)%2;
            this->square[i][j]->row=i;
            this->square[i][j]->col=j;
            this->square[i][j]->squareDisplay();
            this->square[i][j]->setGeometry(hor,ver,this->width/8,this->width/8);
            connect(square[i][j], &Square::clicked, this, &Board::handleSquare);
            hor += this->width/8;
        }
        ver += this->width/8;
    }

    //Squares index
    for (int i = 0; i < 8; ++i){
        this->square[i][0]->setText(QString::number(i+1));
        this->square[i][0]->setAlignment(Qt::AlignTop);
    }

    char c = 'b';
    for(int j=1; j<8; j++){
        QString *q = new QString(c);
        this->square[7][j]->setText(*q);
        c++;
        this->square[7][j]->setAlignment(Qt::AlignBottom);
    }
    fillTheBoard();
}

void Board::fillTheBoard(){

    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
                this->square[i][j]->display(this->pieceType*this->CURRENTBOARD[i][j]);
}

void Board::initBoard(){
    for(int i=0 ; i<8 ; i++){
        CURRENTBOARD[1][i] = -1;
        CURRENTBOARD[6][i] =  1;
    }

    for(int i=2 ; i<6 ; i++){
        for(int j=0 ; j<8 ; j++){
            CURRENTBOARD[i][j] = 0;
        }
    }

    for(int j=0 ; j<5 ; j++){
        CURRENTBOARD[0][j] = -j-2;
        CURRENTBOARD[7][j] =  j+2;
    }

    for(int j=5 ; j<8 ; j++){
        CURRENTBOARD[0][j] = -9+j;
        CURRENTBOARD[7][j] =  9-j;
    }

    if (pieceType == -1){
        CURRENTBOARD[0][3] = -6;
        CURRENTBOARD[7][3] =  6;
        CURRENTBOARD[0][4] = -5;
        CURRENTBOARD[7][4] =  5;
    }
}

void Board::selectPossibilityOfMovment(int from[2]){
    vector<vector<int>> POSSIBLEMOVMENTS;

    M->getPossibilityOfMovment(POSSIBLEMOVMENTS,from,CURRENTBOARD);

    for(int i=0; i<POSSIBLEMOVMENTS.size(); i++)
        selectSquare(POSSIBLEMOVMENTS[i][2], POSSIBLEMOVMENTS[i][3]);
}

void Board::selectSquare(int i, int j){
    square[i][j]->setStyleSheet("QLabel {background-color: rgb(255, 153, 51);}");
}

void Board::removeSelectedSquare(){
    for(int i=0; i<8; i++)
        for(int j=0; j<8; j++)
            square[i][j]->squareDisplay();
}

void Board::playHVsH(int i, int j){
    if(!count){
        if(turn*CURRENTBOARD[i][j] > 0){
            int from[2] = {i, j};
            selectPossibilityOfMovment(from);
            square[i][j]->setStyleSheet("QLabel {background-color: rgb(114, 159, 207);}");
            last[0] = i; last[1] = j;
            count++;
        }
    }
    else if(count){
        int to[2] = {i, j};
        if(CURRENTBOARD[i][j]*CURRENTBOARD[last[0]][last[1]] > 0
                || !M->isMovmentPossible(last[0],last[1],to[0],to[1],CURRENTBOARD)
                ||  M->areTheKingCheckedFor(last[0],last[1],to[0],to[1],CURRENTBOARD,turn))
        {
            int from[2] = {i, j};
            removeSelectedSquare();
            last[0] = i; last[1] = j;

            if(CURRENTBOARD[i][j]*CURRENTBOARD[last[0]][last[1]] > 0){
                square[i][j]->setStyleSheet("QLabel {background-color: rgb(114, 159, 207);}");
                if(turn*CURRENTBOARD[i][j]*pieceType > 0)
                    selectPossibilityOfMovment(from);
            }
        }
        else if(abs(CURRENTBOARD[last[0]][last[1]]) !=6
                &&  turn*CURRENTBOARD[last[0]][last[1]] > 0
                &&  M->isMovmentPossible(last[0],last[1],to[0],to[1],CURRENTBOARD)
                && !M->areTheKingCheckedFor(last[0],last[1],to[0],to[1],CURRENTBOARD,turn))
        {
            count = 0;
            turn = -1*turn;
            M->move(last,to,CURRENTBOARD);
            fillTheBoard();
            removeSelectedSquare();
            check();
        }
        else if(abs(CURRENTBOARD[last[0]][last[1]]) == 6
                &&  turn*CURRENTBOARD[last[0]][last[1]] > 0
                &&  M->isMovmentPossible(last[0],last[1],to[0],to[1],CURRENTBOARD)
                && !M->isThisSquareChecked(to[0],to[1],CURRENTBOARD,turn))
        {
            count = 0;
            turn = -1*turn;
            M->move(last,to,CURRENTBOARD);
            fillTheBoard();
            removeSelectedSquare();
            check();
        }
    }
}

void Board::PlayMinmax(int i,int j){
    if(turn == 1){
        if(!count){
            if(turn*CURRENTBOARD[i][j] > 0){
                int from[2] = {i, j};
                selectPossibilityOfMovment(from);
                square[i][j]->setStyleSheet("QLabel {background-color: rgb(114, 159, 207);}");
                last[0] = i; last[1] = j;
                count++;
            }
        }
        else if(count){
            int to[2] = {i, j};
            if(CURRENTBOARD[i][j]*CURRENTBOARD[last[0]][last[1]] > 0
                    || !M->isMovmentPossible(last[0],last[1],to[0],to[1],CURRENTBOARD)
                    ||  M->areTheKingCheckedFor(last[0],last[1],to[0],to[1],CURRENTBOARD,turn))
            {
                int from[2] = {i, j};
                removeSelectedSquare();
                last[0] = i; last[1] = j;

                if(CURRENTBOARD[i][j]*CURRENTBOARD[last[0]][last[1]] > 0){
                    square[i][j]->setStyleSheet("QLabel {background-color: rgb(114, 159, 207);}");
                    if(turn*CURRENTBOARD[i][j]*pieceType > 0)
                        selectPossibilityOfMovment(from);
                }
            }
            else if(abs(CURRENTBOARD[last[0]][last[1]]) !=6
                    &&  turn*CURRENTBOARD[last[0]][last[1]] > 0
                    &&  M->isMovmentPossible(last[0],last[1],to[0],to[1],CURRENTBOARD)
                    && !M->areTheKingCheckedFor(last[0],last[1],to[0],to[1],CURRENTBOARD,turn))
            {
                count = 0;
                turn = -1*turn;
                M->move(last,to,CURRENTBOARD);
                check();
                PlayMinmax(0,0);
            }
            else if(abs(CURRENTBOARD[last[0]][last[1]]) == 6
                    &&  turn*CURRENTBOARD[last[0]][last[1]] > 0
                    &&  M->isMovmentPossible(last[0],last[1],to[0],to[1],CURRENTBOARD)
                    && !M->isThisSquareChecked(to[0],to[1],CURRENTBOARD,turn))
            {
                count = 0;
                turn = -1*turn;
                M->move(last,to,CURRENTBOARD);
                check();
                PlayMinmax(0,0);
            }
        }
    }
    else if(turn == -1){
        removeSelectedSquare();
        fillTheBoard();
        vector<int> MV = ENGINE->minimaxRoot(CURRENTBOARD,-10000,10000,3);
        int from[2]={MV[0],MV[1]}, to[2] = {MV[2],MV[3]};
        M->move(from,to,CURRENTBOARD);
        turn = -1*turn;
        fillTheBoard();
        check();
    }
}

void Board::PlayMCTS(int i, int j){

}

void Board::check(){
    if(M->check(CURRENTBOARD,turn)){
        if(pieceType*turn == 1){
            QMessageBox::information(this, "Check mat", "Black win");
            initBoard();
            fillTheBoard();
        }
        else{
            QMessageBox::information(this, "Check mat", "White win");
            initBoard();
            fillTheBoard();
        }
    }
}

