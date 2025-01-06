#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    gotoNormal();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::gotoNormal()
{
    Normal = new normal();
    pushWidgetToStackView(Normal);
    this->setWindowTitle("标准型");
}

void MainWindow::gotoScience()
{
    Science = new science();
    pushWidgetToStackView(Science);
    this->setWindowTitle("科学型");
}

void MainWindow::gotoProgrammer()
{
    cxy = new chengxuyuan();
    pushWidgetToStackView(cxy);
    this->setWindowTitle("程序员模式");
}

void MainWindow::gotoDate()
{
    Date = new date();
    pushWidgetToStackView(Date);
    this->setWindowTitle("日期计算模式");
}

void MainWindow::gotoChange()
{
    Change = new change();
    pushWidgetToStackView(Change);
    this->setWindowTitle("汇率与容量转换");
}

void MainWindow::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count - 1); //总是显示最新加入的View
    // ui->labelTitle->setText(widget->windowTitle());
}

void MainWindow::on_normal_triggered()
{
    gotoNormal();
}


void MainWindow::on_science_triggered()
{
    gotoScience();
}


void MainWindow::on_programmer_triggered()
{
    gotoProgrammer();
}


void MainWindow::on_date_triggered()
{
    gotoDate();
}


void MainWindow::on_change_triggered()
{
    gotoChange();
}

