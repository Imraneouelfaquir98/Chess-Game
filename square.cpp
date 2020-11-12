#include "square.h"


void Square::mousePressEvent(QMouseEvent *event)
{
    emit clicked(this->row,this->col);
}

void Square::squareDisplay()
{
    if(this->squareColor)
        this->setStyleSheet("QLabel {background-color: rgb(120, 120, 90);"
                            "color : rgb(211, 211, 158);}"
                            ":hover{background-color: yellow;}");
    else
        this->setStyleSheet("QLabel {background-color: rgb(211, 211, 158);"
                            "color : rgb(120, 120, 90);}"
                            ":hover{background-color: yellow;}");
}

//rgb(170,95,127)

void Square::display(int elem)
{
    switch(elem)
    {
        case  1:  this->setPixmap(QPixmap(":/Images/pawn_white.svg"));
                  this->setScaledContents(true);
                  break;
        case  2:  this->setPixmap(QPixmap(":/Images/rook_white.svg"));
                  this->setScaledContents(true);
                  break;
        case  3:  this->setPixmap(QPixmap(":/Images/knight_white.svg"));
                  this->setScaledContents(true);
                  break;
        case  6:  this->setPixmap(QPixmap(":/Images/king_white.svg"));
                  this->setScaledContents(true);
                  break;
        case  5:  this->setPixmap(QPixmap(":/Images/queen_white.svg"));
                  this->setScaledContents(true);
                  break;
        case  4:  this->setPixmap(QPixmap(":/Images/bishop_white.svg"));
                  this->setScaledContents(true);
                  break;
        case -1:  this->setPixmap(QPixmap(":/Images/pawn_black.svg"));
                  this->setScaledContents(true);
                  break;
        case -2:  this->setPixmap(QPixmap(":/Images/rook_black.svg"));
                  this->setScaledContents(true);
                  break;
        case -3:  this->setPixmap(QPixmap(":/Images/knight_black.svg"));
                  this->setScaledContents(true);
                  break;
        case -6:  this->setPixmap(QPixmap(":/Images/king_black.svg"));
                  this->setScaledContents(true);
                  break;
        case -5:  this->setPixmap(QPixmap(":/Images/queen_black.svg"));
                  this->setScaledContents(true);
                  break;
        case -4:  this->setPixmap(QPixmap(":/Images/bishop_black.svg"));
                  this->setScaledContents(true);
                  break;
        default: this->clear();
                  break;
        }
}
