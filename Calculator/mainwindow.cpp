#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qdebug.h"
#include "math.h"
#include "QKeyEvent"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    digitBtns = {{Qt::Key_0, ui->btnNum0},
        {Qt::Key_1, ui->btnNum1},
        {Qt::Key_2, ui->btnNum2},
        {Qt::Key_3, ui->btnNum3},
        {Qt::Key_4, ui->btnNum4},
        {Qt::Key_5, ui->btnNum5},
        {Qt::Key_6, ui->btnNum6},
        {Qt::Key_7, ui->btnNum7},
        {Qt::Key_8, ui->btnNum8},
        {Qt::Key_9, ui->btnNum9}
    };
    binaryBtns = {{Qt::Key_Plus, ui->btnPlus},
        {Qt::Key_Minus, ui->btnMinus},
        {Qt::Key_Slash, ui->btnDivide},
        {Qt::Key_Asterisk, ui->btnMulti},
        {Qt::Key_Enter, ui->btnEqual},
    };



    //  将数字0-9的槽函数关联
    // connect(ui->btnNum0, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    // connect(ui->btnNum1, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    // connect(ui->btnNum2, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    // connect(ui->btnNum3, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    // connect(ui->btnNum4, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    // connect(ui->btnNum5, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    // connect(ui->btnNum6, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    // connect(ui->btnNum7, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    // connect(ui->btnNum8, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));
    // connect(ui->btnNum9, SIGNAL(clicked(bool)), this, SLOT(btnNumClicked()));

    foreach (auto btn, digitBtns) {
        connect(btn, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    }

    // 将加减乘除符号的槽函数关联

    foreach (auto btn, binaryBtns) {
        connect(btn, SIGNAL(clicked()), this, SLOT(btnBinaryOperatorClicked()));
    }
    // connect(ui->btnDivide, SIGNAL(clicked(bool)), this, SLOT(btnBinaryOperatorClicked()));
    // connect(ui->btnPlus, SIGNAL(clicked(bool)), this, SLOT(btnBinaryOperatorClicked()));
    // connect(ui->btnMinus, SIGNAL(clicked(bool)), this, SLOT(btnBinaryOperatorClicked()));
    // connect(ui->btnMulti, SIGNAL(clicked(bool)), this, SLOT(btnBinaryOperatorClicked()));

    //另外几个
    connect(ui->btnSqaure, SIGNAL(clicked(bool)), this, SLOT(btnUnaryOperatorClickead()));
    connect(ui->btnSqrt, SIGNAL(clicked(bool)), this, SLOT(btnUnaryOperatorClickead()));
    connect(ui->btnReciprocal, SIGNAL(clicked(bool)), this, SLOT(btnUnaryOperatorClickead()));
    connect(ui->btnPercentage, SIGNAL(clicked(bool)), this, SLOT(btnUnaryOperatorClickead()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

QString MainWindow::calculation(bool *ok)
{
    double result = 0;
    if (operands.size() == 1 && opcodes.size() == 0 && !codetmp.isEmpty()) {
        double cnt = operands.back().toDouble();
        if (codetmp == "+") {
            result = cnt + operandtmp.toDouble();
        } else if (codetmp == "-") {
            result = cnt - operandtmp.toDouble();
        } else if (codetmp == "×") {
            result = cnt * operandtmp.toDouble();
        } else if (codetmp == "/") {
            result = cnt / operandtmp.toDouble();
        }
        operands.pop_back();
        operands.push_back(QString::number(result));
        qDebug() << codetmp;
        qDebug() << operandtmp.toDouble();
    }
    qDebug() << "operands.size()=" << operands.size();
    qDebug() << "opcodes.size()=" << opcodes.size();
    if (operands.size() == 2 && opcodes.size() > 0) {
        //取操作数
        double operand1 = operands.front().toDouble();
        operands.pop_front();
        double operand2 = operands.front().toDouble();
        operands.pop_front();

        //取操作符
        QString op = opcodes.front();
        opcodes.pop_front();

        if (op == "+") {
            result = operand1 + operand2;
        } else if (op == "-") {
            result = operand1 - operand2;
        } else if (op == "×") {
            result = operand1 * operand2;
        } else if (op == "/") {
            result = operand1 / operand2;
        }

        operands.push_back(QString::number(result));

        ui->statusbar->showMessage(QString("operands is %1, opcodes is %2").arg(operands.size()).arg(opcodes.size()));
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
    operands.clear();
    opcodes.clear();
    ui->display->setText(operand);
}


void MainWindow::btnBinaryOperatorClicked()
{
    QString opcode = qobject_cast<QPushButton *>(sender())->text();
    if (operand != "") {
        operands.push_back(operand);
        operand = "";
    }
    if (opcode != "=") {
        opcodes.push_back(opcode);
        codetmp = opcode;
    }
    if (operands.size() == 2) {
        QString result = calculation();
        ui->display->setText(result);
    }
}

void MainWindow::btnUnaryOperatorClickead()
{
    double result = 0;
    if (operand != "") {
        result = operand.toDouble();
        operand = "";

    } else result = operands.back().toDouble();
    QString op = qobject_cast<QPushButton *>(sender())->text();

    operands.pop_back();
    if (op == "%")
        result /= 100.0;
    else if (op == "1/x")
        result = 1 / result;
    else if (op == "x^2")
        result *= result;
    else if (op == "√x")
        result = sqrt(result);

    operands.push_back(QString::number(result));
    ui->display->setText(QString::number(result));
}


void MainWindow::on_btnEqual_clicked()
{
    if (operand != "") {
        operands.push_back(operand);
        operandtmp = operand;
        operand = "";
    }

    QString result = calculation();
    qDebug() << "=" << result;
    ui->display->setText(result);
}

void MainWindow::on_btnChange_clicked()
{
    double result = 0;
    if (operands.size() == 0) {
        result = operand.toDouble() * -1;
        operands.push_back(QString::number(result));
    } else {
        result = operands.front().toDouble() * -1;
        operands.pop_front();
        operands.push_back(QString::number(result));
    }

    qDebug() << "result=" << result;
    qDebug() << operands.front();
    ui->display->setText(QString::number(result));
}

void MainWindow::keyPressEvent(QKeyEvent * event)
{
    foreach (auto btnkey, digitBtns.keys()) {
        if (event->key() == btnkey)
            digitBtns[btnkey]->animateClick();
    }
    foreach (auto btnkey, binaryBtns.keys()) {
        if (event->key() == btnkey)
            binaryBtns[btnkey]->animateClick();
    }
    if (event->key() == Qt::Key_Period) {
        ui->btnSign->animateClick();
    }
    if (event->key() == Qt::Key_Backspace) {
        ui->btnDel->animateClick();
    }
}


void MainWindow::on_btnClear_clicked()
{
    if (operands.size() != 0) {
        operand = "";
    }
    ui->display->setText(operand);
}

