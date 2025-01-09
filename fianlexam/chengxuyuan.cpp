#include "chengxuyuan.h"
#include "ui_chengxuyuan.h"
#include "qdebug.h"
#include "math.h"
#include "QKeyEvent"

void chengxuyuan::setButtonsEnabled(QList<QPushButton*>& buttons, bool enabled) {
    for (QPushButton* button : buttons) {
        button->setEnabled(enabled);
    }
}

chengxuyuan::chengxuyuan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chengxuyuan)
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
        {Qt::Key_9, ui->btnNum9},
        {Qt::Key_A, ui->btnA},
        {Qt::Key_B, ui->btnB},
        {Qt::Key_C, ui->btnC},
        {Qt::Key_D, ui->btnD},
        {Qt::Key_E, ui->btnE},
        {Qt::Key_F, ui->btnF}
    };
    binaryBtns = {{Qt::Key_Plus, ui->btnRight},
                  {Qt::Key_Minus, ui->btnLeft},
                  {Qt::Key_Slash, ui->btnNor},
                  {Qt::Key_Asterisk, ui->btnXor},
                  {Qt::Key_Enter, ui->btnEqual},
                  };

    buttons = {ui->btnA, ui->btnB, ui->btnC, ui->btnD, ui->btnE, ui->btnF, ui->btnNum1, ui->btnNum2
              , ui->btnNum3, ui->btnNum4, ui->btnNum5, ui->btnNum6, ui->btnNum7, ui->btnNum8, ui->btnNum9};

    setButtonsEnabled(buttons, true);

    ui->btnA->setEnabled(false);
    ui->btnB->setEnabled(false);
    ui->btnC->setEnabled(false);
    ui->btnD->setEnabled(false);
    ui->btnE->setEnabled(false);
    ui->btnF->setEnabled(false);

    foreach (auto btn, digitBtns) {
        connect(btn, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    }

    connect(ui->btnAnd, SIGNAL(clicked()), this, SLOT(calculation()));
    connect(ui->btnOr, SIGNAL(clicked()), this, SLOT(calculation()));
    connect(ui->btnNor, SIGNAL(clicked()), this, SLOT(calculation()));
    connect(ui->btnXor, SIGNAL(clicked()), this, SLOT(calculation()));
    connect(ui->btnNand, SIGNAL(clicked()), this, SLOT(calculation()));

    Type = "Dec";

    ui->labelDec->setStyleSheet("QLabel { background-color: #666; color: #fff}");
    ui->lineEditDec->setStyleSheet("QLineEdit { background-color: #666; color: #fff}");

    ui->labelBin->setStyleSheet("QLabel { background-color: #fff; color: #333}");
    ui->lineEditBin->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");

    ui->labelOct->setStyleSheet("QLabel { background-color: #fff; color: #333}");
    ui->lineEditOct->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");

    ui->labelHex->setStyleSheet("QLabel { background-color: #fff; color: #333}");
    ui->lineEditHex->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");

    printContent();

}

chengxuyuan::~chengxuyuan()
{
    delete ui;
}



// 十进制转二进制
QString decimalToBinary(int decimal) {
    std::bitset<32> binary(decimal);
    return QString::fromStdString(binary.to_string());
}


// 十进制转八进制
QString decimalToOctal(int decimal) {
    std::stringstream ss;
    ss << std::oct << decimal;
    return QString::fromStdString(ss.str());
}


// 十进制转十六进制
QString decimalToHexadecimal(int decimal) {
    std::stringstream ss;
    ss << std::hex << decimal;
    return QString::fromStdString(ss.str());
}


// 二进制转十进制
int binaryToDecimal(QString& binary) {
    bool ok;
    int decimal = binary.toInt(&ok, 2);
    if (!ok) {
        return 0;
    }
    return decimal;
}


// 八进制转十进制
int octalToDecimal(QString& octal) {
    bool ok;
    int decimal = octal.toInt(&ok, 8);
    if (!ok) {
        return 0;
    }
    return decimal;
}


// 十六进制转十进制
int hexadecimalToDecimal(QString& hexadecimal) {
    bool ok;
    int decimal = hexadecimal.toInt(&ok, 16);
    if (!ok) {
        return 0;
    }
    return decimal;
}


// 二进制转八进制
QString binaryToOctal(QString& binary) {
    int decimal = binaryToDecimal(binary);
    return decimalToOctal(decimal);
}


// 二进制转十六进制
QString binaryToHexadecimal(QString& binary) {
    int decimal = binaryToDecimal(binary);
    return decimalToHexadecimal(decimal);
}


// 八进制转二进制
QString octalToBinary(QString& octal) {
    int decimal = octalToDecimal(octal);
    return decimalToBinary(decimal);
}


// 八进制转十六进制
QString octalToHexadecimal(QString& octal) {
    int decimal = octalToDecimal(octal);
    return decimalToHexadecimal(decimal);
}


// 十六进制转二进制
QString hexadecimalToBinary(QString& hexadecimal) {
    int decimal = hexadecimalToDecimal(hexadecimal);
    return decimalToBinary(decimal);
}


// 十六进制转八进制
QString hexadecimalToOctal(QString& hexadecimal) {
    int decimal = hexadecimalToDecimal(hexadecimal);
    return decimalToOctal(decimal);
}

void chengxuyuan::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();

    if (digit == '0' && operand == '0')
        digit = "";

    if (digit != '0' && operand == '0')
        operand = "";

    operand += digit;


    qDebug()<<"hello";
    printContent();
}

void chengxuyuan::on_btnClear_clicked()
{
    if (operands.size() != 0) {
        operand = "";
    }
    printContent();
}

void chengxuyuan::keyPressEvent(QKeyEvent * event)
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

void chengxuyuan::on_btnChange_clicked()
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

void chengxuyuan::on_btnEqual_clicked()
{
    if (operand != "") {
        operands.push_back(operand);
        operandtmp = operand;
        operand = "";
    }

    calculation();
}

void chengxuyuan::on_btnDel_clicked()
{
    operand = operand.left(operand.length() - 1);
    ui->display->setText(operand);
    printContent();
}


void chengxuyuan::on_btnClearAll_clicked()
{
    operand.clear();
    operands.clear();
    opcodes.clear();
    ui->display->setText(operand);
    printContent();
}

void chengxuyuan::on_btnSign_clicked()
{
    if (!operand.contains(".")) {
        operand += qobject_cast<QPushButton *>(sender())->text();
    }
    ui->display->setText(operand);
}




void chengxuyuan::on_btnLeft_clicked()
{
    setButtonsEnabled(buttons, true);

    ui->btnA->setEnabled(false);
    ui->btnB->setEnabled(false);
    ui->btnC->setEnabled(false);
    ui->btnD->setEnabled(false);
    ui->btnE->setEnabled(false);
    ui->btnF->setEnabled(false);
    QString opcode = qobject_cast<QPushButton *>(sender())->text();
    if (operand != "") {
        QString binValue = ui->lineEditBin->text();
        operands.push_back(binValue);
        operand = "";
    }
    if (opcode != "=") {
        opcodes.push_back(opcode);
        codetmp = opcode;
    }
    if (operands.size() == 2) {
        calculation();

    }
}


void chengxuyuan::on_btnRight_clicked()
{
    setButtonsEnabled(buttons, true);

    ui->btnA->setEnabled(false);
    ui->btnB->setEnabled(false);
    ui->btnC->setEnabled(false);
    ui->btnD->setEnabled(false);
    ui->btnE->setEnabled(false);
    ui->btnF->setEnabled(false);
    QString opcode = qobject_cast<QPushButton *>(sender())->text();
    if (operand != "") {
        QString binValue = ui->lineEditBin->text();
        operands.push_back(binValue);
        operand = "";
    }
    if (opcode != "=") {
        opcodes.push_back(opcode);
        codetmp = opcode;
    }
    if (operands.size() == 2) {
        calculation();

    }
}


void chengxuyuan::on_lineEditHex_selectionChanged()
{

    Type = "Hex";
    QString tmp = ui->lineEditHex->text();
    operand = tmp;
    qDebug()<<"operand=" <<operand;

    setButtonsEnabled(buttons, true);

    ui->labelHex->setStyleSheet("QLabel { background-color: #666; color: #fff}");
    ui->lineEditHex->setStyleSheet("QLineEdit { background-color: #666; color: #fff}");

    ui->labelBin->setStyleSheet("QLabel { background-color: #fff; color: #333}");
    ui->lineEditBin->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");

    ui->labelOct->setStyleSheet("QLabel { background-color: #fff; color: #333}");
    ui->lineEditOct->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");

    ui->labelDec->setStyleSheet("QLabel { background-color: #fff; color: #333}");
    ui->lineEditDec->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");

    printContent();
    operand = "";
}


void chengxuyuan::on_lineEditDec_selectionChanged()
{
    setButtonsEnabled(buttons, true);

    ui->btnA->setEnabled(false);
    ui->btnB->setEnabled(false);
    ui->btnC->setEnabled(false);
    ui->btnD->setEnabled(false);
    ui->btnE->setEnabled(false);
    ui->btnF->setEnabled(false);

    Type = "Dec";
    QString tmp = ui->lineEditDec->text();
    operand = tmp;
    qDebug()<<"operand=" <<operand;



    ui->labelDec->setStyleSheet("QLabel { background-color: #666; color: #fff}");
    ui->lineEditDec->setStyleSheet("QLineEdit { background-color: #666; color: #fff}");

    ui->labelBin->setStyleSheet("QLabel { background-color: #fff; color: #333}");
    ui->lineEditBin->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");

    ui->labelOct->setStyleSheet("QLabel { background-color: #fff; color: #333}");
    ui->lineEditOct->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");

    ui->labelHex->setStyleSheet("QLabel { background-color: #fff; color: #333}");
    ui->lineEditHex->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");

    printContent();
    operand = "";
}


void chengxuyuan::on_lineEditOct_selectionChanged()
{
    Type = "Oct";
    QString tmp = ui->lineEditOct->text();
    operand = tmp;
    qDebug()<<"operand=" <<operand;

    setButtonsEnabled(buttons, true);

    ui->btnA->setEnabled(false);
    ui->btnB->setEnabled(false);
    ui->btnC->setEnabled(false);
    ui->btnD->setEnabled(false);
    ui->btnE->setEnabled(false);
    ui->btnF->setEnabled(false);
    ui->btnNum8->setEnabled(false);
    ui->btnNum9->setEnabled(false);

    ui->labelOct->setStyleSheet("QLabel { background-color: #666; color: #fff}");
    ui->lineEditOct->setStyleSheet("QLineEdit { background-color: #666; color: #fff}");

    ui->labelBin->setStyleSheet("QLabel { background-color: #fff; color: #333}");
    ui->lineEditBin->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");

    ui->labelHex->setStyleSheet("QLabel { background-color: #fff; color: #333}");
    ui->lineEditHex->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");

    ui->labelDec->setStyleSheet("QLabel { background-color: #fff; color: #333}");
    ui->lineEditDec->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");

    printContent();
    operand = "";
}


void chengxuyuan::on_lineEditBin_selectionChanged()
{
    Type = "Bin";
    QString tmp = ui->lineEditBin->text();
    operand = tmp;
    qDebug()<<"operand=" <<operand;

    setButtonsEnabled(buttons, true);

    ui->btnA->setEnabled(false);
    ui->btnB->setEnabled(false);
    ui->btnC->setEnabled(false);
    ui->btnD->setEnabled(false);
    ui->btnE->setEnabled(false);
    ui->btnF->setEnabled(false);
    ui->btnNum3->setEnabled(false);
    ui->btnNum4->setEnabled(false);
    ui->btnNum5->setEnabled(false);
    ui->btnNum2->setEnabled(false);
    ui->btnNum6->setEnabled(false);
    ui->btnNum7->setEnabled(false);
    ui->btnNum8->setEnabled(false);
    ui->btnNum9->setEnabled(false);

    ui->labelBin->setStyleSheet("QLabel { background-color: #666; color: #fff}");
    ui->lineEditBin->setStyleSheet("QLineEdit { background-color: #666; color: #fff}");

    ui->labelHex->setStyleSheet("QLabel { background-color: #fff; color: #333}");
    ui->lineEditHex->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");

    ui->labelOct->setStyleSheet("QLabel { background-color: #fff; color: #333}");
    ui->lineEditOct->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");

    ui->labelDec->setStyleSheet("QLabel { background-color: #fff; color: #333}");
    ui->lineEditDec->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");

    printContent();
    operand = "";
}

void chengxuyuan::printContent(){
    if(Type == "Dec"){
        qDebug()<<"进入Dec";
        QString result = operand;
        ui->lineEditBin->setText(decimalToBinary(result.toInt()));
        ui->lineEditDec->setText(result);
        ui->display->setText(result);
        ui->lineEditOct->setText(decimalToOctal(result.toInt()));
        ui->lineEditHex->setText(decimalToHexadecimal(result.toInt()));
    }
    else if(Type == "Hex"){
        qDebug()<<"进入Hex";
        QString result = operand;
        ui->lineEditBin->setText(hexadecimalToBinary(result));
        ui->lineEditDec->setText(QString::number(hexadecimalToDecimal(result)));
        ui->display->setText(result);
        ui->lineEditOct->setText(hexadecimalToOctal(result));
        ui->lineEditHex->setText(result);
    }
    else if(Type == "Oct"){
        qDebug()<<"进入Oct";
        QString result = operand;
        ui->lineEditBin->setText(octalToBinary(result));
        ui->lineEditDec->setText(QString::number(octalToDecimal(result)));
        ui->display->setText(result);
        ui->lineEditOct->setText(result);
        ui->lineEditHex->setText(octalToHexadecimal(result));
    }
    else if(Type == "Bin"){
        qDebug()<<"进入Bin";
        QString result = operand;

        ui->lineEditBin->setText(result);
        ui->lineEditDec->setText(QString::number(binaryToDecimal(result)));
        ui->display->setText(result);
        ui->lineEditOct->setText(binaryToOctal(result));
        ui->lineEditHex->setText(binaryToHexadecimal(result));
        qDebug()<<"ui->lineEditDec->text() = "<<ui->lineEditDec->text();
    }

}

void chengxuyuan::calculation(){
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
        QString flag;

        int num1 = operand1;
        int num2 = operand2;

        int result;

        if (op == "AND") {


            qDebug()<<"operand1="<<operand1<<op<<"operand2="<<operand2;

            result = num1 & num2;
            qDebug()<<"reslut="<<result;
            qDebug()<<"operand="<<operand;

        } else if (op == "OR") {
            result = num1 | num2;

        }  else if (op == "NAND") {
            result = ~(num1 & num2);
        }else if (op == "NOR") {
            result = ~(num1 | num2);
        }else if (op == "XOR") {
            result = num1 ^ num2;
        }else if(op == "<<"){
            result = num1 << num2;
            if(Type == "Bin"){
                QString s = QString::number(num1);
                bool ok;
                num1 = s.toInt(&ok, 2);
                result = num1 << num2;
                QString result1 = decimalToBinary(result);

                result = result1.toInt();
            }
            else if(Type == "Oct"){
                QString s = QString::number(num1);
                bool ok;
                num1 = s.toInt(&ok, 8);
                result = num1 << num2;
                QString result1 = decimalToOctal(result);

                result = result1.toInt();
            }
            else if(Type == "Hex"){
                QString s = QString::number(num1);
                bool ok;
                num1 = s.toInt(&ok, 16);
                result = num1 << num2;
                QString result1 = decimalToHexadecimal(result);

                result = result1.toInt();
            }

        }
        else if(op == ">>"){
            result = num1 >> num2;
            if(Type == "Bin"){
                QString s = QString::number(num1);
                bool ok;
                num1 = s.toInt(&ok, 2);
                result = num1 >> num2;
                QString result1 = decimalToBinary(result);

                result = result1.toInt();
            }
            else if(Type == "Oct"){
                QString s = QString::number(num1);
                bool ok;
                num1 = s.toInt(&ok, 8);
                result = num1 >> num2;
                QString result1 = decimalToOctal(result);

                result = result1.toInt();
            }
            else if(Type == "Hex"){
                QString s = QString::number(num1);
                bool ok;
                num1 = s.toInt(&ok, 16);
                result = num1 >> num2;
                QString result1 = decimalToHexadecimal(result);

                result = result1.toInt();
            }

        }

        operand = QString::number(result);
        flag = operand;

        operands.push_back(flag);
        qDebug()<<"operands.push_back="<<flag;
        printContent();
        qDebug()<<ui->lineEditDec->text();
        operand = "";
        // ui->statusbar->showMessage(QString("operands is %1, opcodes is %2").arg(operands.size()).arg(opcodes.size()));
    }
}


void chengxuyuan::on_btnAnd_clicked()
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
        calculation();

    }

}


void chengxuyuan::on_btnOr_clicked()
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
        calculation();

    }

}


void chengxuyuan::on_btnNot_clicked()
{
    int num = operand.toInt();
    int result = ~num;

    operand = QString::number(result);
    printContent();
    operand = "";
}


void chengxuyuan::on_btnNand_clicked()
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
        calculation();

    }

}


void chengxuyuan::on_btnNor_clicked()
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
        calculation();

    }

}


void chengxuyuan::on_btnXor_clicked()
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
        calculation();

    }

}

