#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "client.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //this->tampil();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::tampil()
{

}



