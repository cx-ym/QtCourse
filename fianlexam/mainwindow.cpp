#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    translator = new QTranslator(this);

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

void MainWindow::gotoCurrency()
{
    Currency = new currency();
    pushWidgetToStackView(Currency);
    this->setWindowTitle("货币换算模式");
}

void MainWindow::gotoCapacity()
{
    Capacity = new capacity();
    pushWidgetToStackView(Capacity);
    this->setWindowTitle("容量换算模式");
}



void MainWindow::pushWidgetToStackView(QWidget *widget)
{
    ui->stackedWidget->addWidget(widget);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count - 1);
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




void MainWindow::on_currency_triggered()
{
    gotoCurrency();
}


void MainWindow::on_capacity_triggered()
{
    gotoCapacity();
}


void MainWindow::on_Chinexe_triggered()
{
    translator->load(":/calculator_zh_CN.qm");
    qDebug() << "安装中文";
    qApp->installTranslator(this->translator);
    //刷新UI
    this->ui->retranslateUi(this);
}


void MainWindow::on_English_triggered()
{
    translator->load(":/calculator_en_US.qm");
    qDebug() << "安装英文";
    qApp->installTranslator(this->translator);
    //刷新UI
    this->ui->retranslateUi(this);
}

