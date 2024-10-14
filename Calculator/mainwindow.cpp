#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //  将数字0-9的槽函数关联
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

    // 将加减乘除符号的槽函数关联
    connect(ui->btnDivide, SIGNAL(clicked(bool)), this, SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnPlus, SIGNAL(clicked(bool)), this, SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnMinus, SIGNAL(clicked(bool)), this, SLOT(btnBinaryOperatorClicked()));
    connect(ui->btnMulti, SIGNAL(clicked(bool)), this, SLOT(btnBinaryOperatorClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    double result = 0;
    if (operands.size() == 2 && opcodes.size() > 0) {
        //取操作数
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        //取操作符
        QString op = opcodes.pop();
        opcodes.pop_front();

        if (op == "+") {
            result = operand1 + operand2;
        } else if (op == "-") {
            result = operand1 - operand2;
        } else if (op == "*") {
            result = operand1 * operand2;
        } else if (op == "/") {
            result = operand1 / operand2;
        }
        // operands.push_back(QString::number(result));
        ui->statusbar->showMessage("calculation is in progress");
    } else
        ui->statusbar->showMessage(QString("operands is %1, opcodes is %2").arg(operands.size()).arg(opcodes.size()));



    return QString::number(result);
}

void MainWindow::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();

    if (digit == '0' && operand == '0')
        digit = "";

    if (digit != '0' && operand == '0')
        operand = "";

    operand += digit;
    ui->display->setText(operand);

}

void MainWindow::on_btnSign_clicked()
{
    if (!operand.contains(".")) {
        operand += qobject_cast<QPushButton *>(sender())->text();
    }
    ui->display->setText(operand);
}


void MainWindow::on_btnDel_clicked()
{
    operand = operand.left(operand.length() - 1);
    ui->display->setText(operand);
}


void MainWindow::on_btnClearAll_clicked()
{
    operand.clear();
    ui->display->setText(operand);
}


void MainWindow::btnBinaryOperatorClicked()
{
    QString opcode = qobject_cast<QPushButton *>(sender())->text();
    if (operand != "") {
        operands.push_back(operand);
        operand = "";

        opcodes.push_back(opcode);
    }

    QString result = calculation();
    // operands.push_back(result);
    ui->display->setText(result);
}

void MainWindow::btnUnaryOperatorClickead()
{
    if (operand != "") {
        operands.push_back(operand);
        operand = "";
    }
}


void MainWindow::on_btnEqual_clicked()
{
    // if (operand != "") {
    //     operands.push_back(operand);
    //     operand = "";
    // }

    QString result = calculation();
    // operands.push_back(result);
    ui->display->setText(result);
}

