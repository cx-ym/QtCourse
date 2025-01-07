#include "science.h"
#include "ui_science.h"
#include "math.h"
#include "QKeyEvent"


science::science(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::science)
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


    foreach (auto btn, digitBtns) {
        connect(btn, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    }

    // 将加减乘除符号的槽函数关联

    foreach (auto btn, binaryBtns) {
        connect(btn, SIGNAL(clicked()), this, SLOT(btnBinaryOperatorClicked()));
    }

    //另外几个
    connect(ui->btnSqaure, SIGNAL(clicked(bool)), this, SLOT(btnBinaryOperatorClicked()));

    connect(ui->btnSqrt, SIGNAL(clicked(bool)), this, SLOT(btnUnaryOperatorClickead()));
    connect(ui->btnReciprocal, SIGNAL(clicked(bool)), this, SLOT(btnUnaryOperatorClickead()));
    connect(ui->btnPercentage, SIGNAL(clicked(bool)), this, SLOT(btnUnaryOperatorClickead()));
}

science::~science()
{
    delete ui;
}

QString science::calculation(bool *ok)
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
        } else if (op == "x^n"){
            qDebug()<<"operand1="<<operand1<<" operand2="<<operand2;
            result = pow(operand1, operand2);
        }

        operands.push_back(QString::number(result));
        // ui->statusbar->showMessage(QString("operands is %1, opcodes is %2").arg(operands.size()).arg(opcodes.size()));
    } //else
    // ui->statusbar->showMessage(QString("operands is %1, opcodes is %2").arg(operands.size()).arg(opcodes.size()));



    return QString::number(result);
}

void science::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();

    if (digit == '0' && operand == '0')
        digit = "";

    if (digit != '0' && operand == '0')
        operand = "";

    operand += digit;

    ui->display->setText(operand);

}

void science::on_btnSign_clicked()
{
    if (!operand.contains(".")) {
        operand += qobject_cast<QPushButton *>(sender())->text();
    }
    ui->display->setText(operand);
}


void science::on_btnDel_clicked()
{
    operand = operand.left(operand.length() - 1);
    ui->display->setText(operand);
}


void science::on_btnClearAll_clicked()
{
    operand.clear();
    operands.clear();
    opcodes.clear();
    ui->display->setText(operand);
}


void science::btnBinaryOperatorClicked()
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

void science::btnUnaryOperatorClickead()
{
    double result = 0;
    if (operands.size() == 0) {
        qDebug()<<"operand is not empty";
        result = operand.toDouble();
        operand = "";

    } else {
        result = operands.back().toDouble();
        operands.pop_back();
    }

    QString op = qobject_cast<QPushButton *>(sender())->text();


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


void science::on_btnEqual_clicked()
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

void science::on_btnChange_clicked()
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

void science::keyPressEvent(QKeyEvent * event)
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


void science::on_btnClear_clicked()
{
    if (operands.size() != 0) {
        operand = "";
    }
    ui->display->setText(operand);
}


void science::on_btnSin_clicked()
{
    qDebug()<<"sin能用";

    double result = 0;
    if(operands.size() == 0){
        result = sin(operand.toDouble() * 180 / M_PI);
        qDebug()<<"operand join the operands";
        operands.push_back(QString::number(result));
        operand = "";
    } else {
        result = sin(operands.back().toDouble()* M_PI / 180.0);
        operands.pop_back();
        operand = "";
        operands.push_back(QString::number(result));
    }

    qDebug() << "result=" << result;
    qDebug() << operands.front();
    ui->display->setText(QString::number(result));
}


void science::on_btnCos_clicked()
{
    qDebug()<<"cos能用";
    double result = 0;
    if(operands.size() == 0){
        result = cos(operand.toDouble() * 180 / M_PI);
        qDebug()<<"operand join the operands";
        operands.push_back(QString::number(result));
        operand = "";
    } else {
        result = cos(operands.back().toDouble()* M_PI / 180.0);
        operands.pop_back();
        operand = "";
        operands.push_back(QString::number(result));
    }

    qDebug() << "result=" << result;
    qDebug() << operands.front();
    ui->display->setText(QString::number(result));
}


void science::on_btnTan_clicked()
{
    qDebug()<<"tan能用";
    double result = 0;
    if(operands.size() == 0){
        result = tan(operand.toDouble() * 180 / M_PI);
        qDebug()<<"operand join the operands";
        operands.push_back(QString::number(result));
        operand = "";
    } else {
        result = tan(operands.back().toDouble()* M_PI / 180.0);
        operands.pop_back();
        operand = "";
        operands.push_back(QString::number(result));
    }

    qDebug() << "result=" << result;
    qDebug() << operands.front();
    ui->display->setText(QString::number(result));
}





void science::on_btnLog_clicked()
{
    qDebug()<<"ln能用";
    double result = 0;
    if(operands.size() == 0){
        result = log(operand.toDouble());
        qDebug()<<"operand join the operands";
        operands.push_back(QString::number(result));
        operand = "";
    } else {
        result = log(operands.back().toDouble());
        operands.pop_back();
        operand = "";
        operands.push_back(QString::number(result));
    }

    qDebug() << "result=" << result;
    qDebug() << operands.front();
    ui->display->setText(QString::number(result));
}


void science::on_btnReciprocal_clicked()
{
    qDebug()<<"log能用";
    double result = 0;
    if(operands.size() == 0){
        result = log10(operand.toDouble());
        qDebug()<<"operand join the operands";
        operands.push_back(QString::number(result));
        operand = "";
    } else {
        result = log10(operands.back().toDouble());
        operands.pop_back();
        operand = "";
        operands.push_back(QString::number(result));
    }

    qDebug() << "result=" << result;
    qDebug() << operands.front();
    ui->display->setText(QString::number(result));
}



