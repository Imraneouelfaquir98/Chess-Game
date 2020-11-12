#ifndef SQUARE_H
#define SQUARE_H

#include <QLabel>
#include <QWidget>
#include <QMouseEvent>
#include <Qt>

class Square : public QLabel
{
    Q_OBJECT
public:
    int squareColor, row, col;
    Square(QWidget* pParent=0, Qt::WindowFlags f=0) : QLabel(pParent, f) {};
    Square(const QString& text, QWidget* pParent = 0, Qt::WindowFlags f = 0) : QLabel(text, pParent, f){};

    //Methods
    void mousePressEvent(QMouseEvent *event);
    void display(int elem);
    void squareDisplay();
signals:
    void clicked(int row, int col);
};

#endif // SQUARE_H
