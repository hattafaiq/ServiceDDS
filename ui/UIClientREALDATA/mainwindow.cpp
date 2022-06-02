#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->initgraf();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initgraf()
{

}

