#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->btnNum0, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    connect(ui->btnNum1, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    connect(ui->btnNum2, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    connect(ui->btnNum3, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    connect(ui->btnNum4, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    connect(ui->btnNum5, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    connect(ui->btnNum6, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    connect(ui->btnNum7, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    connect(ui->btnNum8, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    connect(ui->btnNum9, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::btnNumClicked()
{
    QString str = ui->display->text();
    str += qobject_cast<QPushButton *>(sender())->text();

    ui->display->setText(str);
    ui->statusbar->showMessage("btn clicked");

}


void MainWindow::on_btnSign_clicked()
{
    QString str = ui->display->text();
    if (!str.contains(".")) {
        str += qobject_cast<QPushButton *>(sender())->text();
    }
    ui->display->setText(str);
}


void MainWindow::on_btnDel_clicked()
{
    QString str = ui->display->text();
    str = str.left(str.length() - 1);
    ui->display->setText(str);
}

