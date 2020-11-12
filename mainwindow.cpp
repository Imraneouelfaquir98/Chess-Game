#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    boardHVsH   = new Board(1);
    boardMinMax = new Board(2);
    connect(boardHVsH->backButton, SIGNAL (clicked()), this, SLOT (on_back_HVsH_clicked()));
    connect(boardMinMax->backButton, SIGNAL (clicked()), this, SLOT (on_back_MinMax_clicked()));
    ui->stackedWidget->insertWidget(4,boardHVsH);
    ui->stackedWidget->insertWidget(7,boardMinMax);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_play_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->page_2));
}

void MainWindow::on_back_1_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(ui->Home_page));
}

void MainWindow::on_againstIA_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_againstHuman_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_back_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_back_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_start_H_vs_H_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
}

void MainWindow::on_back_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::on_back_HVsH_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_MinMaxPage_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_back_MinMax_clicked()
{
    ui->stackedWidget->setCurrentIndex(5);
}

void MainWindow::on_start_MinMax_clicked()
{
    ui->stackedWidget->setCurrentIndex(ui->stackedWidget->indexOf(boardMinMax));
}
