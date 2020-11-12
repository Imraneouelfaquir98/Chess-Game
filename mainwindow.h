#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "board.h"
#include "square.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Board *boardHVsH;
    Board *boardMinMax;

private slots:
    void on_play_clicked();
    void on_back_1_clicked();
    void on_againstIA_clicked();
    void on_againstHuman_clicked();
    void on_back_2_clicked();
    void on_back_3_clicked();
    void on_start_H_vs_H_clicked();
    void on_back_HVsH_clicked();
    void on_back_4_clicked();
    void on_MinMaxPage_clicked();
    void on_back_MinMax_clicked();

    void on_start_MinMax_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
