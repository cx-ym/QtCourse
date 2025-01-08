#include "capacity.h"
#include "ui_capacity.h"
#include "qdebug.h"
#include "math.h"
#include "QKeyEvent"

capacity::capacity(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::capacity)
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


    foreach (auto btn, digitBtns) {
        connect(btn, SIGNAL(clicked()), this, SLOT(btnNumClicked()));
    }

    ui->comboBoxBottom->setItemData(0, "mL");
    ui->comboBoxBottom->setItemData(1, "L");
    ui->comboBoxBottom->setItemData(2, "cm³");
    ui->comboBoxBottom->setItemData(3, "m³");
    ui->comboBoxBottom->setItemData(4, "in³");
    ui->comboBoxBottom->setItemData(5, "ft³");
    ui->comboBoxBottom->setItemData(6, "gal");
    ui->comboBoxBottom->setItemData(7, "qt");
    ui->comboBoxBottom->setItemData(8, "pt");
    ui->comboBoxBottom->setItemData(9, "fl oz");


    ui->comboBoxTop->setItemData(0, "mL");
    ui->comboBoxTop->setItemData(1, "L");
    ui->comboBoxTop->setItemData(2, "cm³");
    ui->comboBoxTop->setItemData(3, "m³");
    ui->comboBoxTop->setItemData(4, "in³");
    ui->comboBoxTop->setItemData(5, "ft³");
    ui->comboBoxTop->setItemData(6, "gal");
    ui->comboBoxTop->setItemData(7, "qt");
    ui->comboBoxTop->setItemData(8, "pt");
    ui->comboBoxTop->setItemData(9, "fl oz");

    Position = "top";
    ui->lineEditTop->setStyleSheet("QLineEdit { background-color: #666; color: #fff}");

    ui->lineEditBottom->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");
}

capacity::~capacity()
{
    delete ui;
}

double capacity::convertToBaseUnit(double value, const QString& unit)
{
    if (unit == "mL") return value;
    if (unit == "L") return value * 1000;
    if (unit == "cm³") return value;
    if (unit == "m³") return value * 1000000;
    if (unit == "in³") return value * 16.3871;
    if (unit == "ft³") return value * 28316.8;
    if (unit == "gal") return value * 3785.41;
    if (unit == "qt") return value * 946.353;
    if (unit == "pt") return value * 473.176;
    if (unit == "fl oz") return value * 29.5735;
    return 0;
}


double capacity::convertFromBaseUnit(double value, const QString& unit)
{
    if (unit == "mL") return value;
    if (unit == "L") return value / 1000;
    if (unit == "cm³") return value;
    if (unit == "m³") return value / 1000000;
    if (unit == "in³") return value / 16.3871;
    if (unit == "ft³") return value / 28316.8;
    if (unit == "gal") return value / 3785.41;
    if (unit == "qt") return value / 946.353;
    if (unit == "pt") return value / 473.176;
    if (unit == "fl oz") return value / 29.5735;
    return 0;
}

void capacity::exchange()
{
    double value;
    QString unitFront;
    QString unitBack;

    if(Position == "top"){
        value = ui->lineEditTop->text().toDouble();
        unitFront = ui->comboBoxTop->currentData().toString();
        unitBack = ui->comboBoxBottom->currentData().toString();
    }
    else if(Position == "bottom"){
        value = ui->lineEditBottom->text().toDouble();
        unitFront = ui->comboBoxBottom->currentData().toString();
        unitBack = ui->comboBoxTop->currentData().toString();
    }

    double result = convertToBaseUnit(value, unitFront);
    double finalResult = convertFromBaseUnit(result, unitBack);

    qDebug()<<finalResult;
    if(Position == "top"){
        ui->lineEditBottom->setText(QString::number(finalResult));
    }
    else if(Position == "bottom"){
        ui->lineEditTop->setText(QString::number(finalResult));
    }
}

void capacity::keyPressEvent(QKeyEvent * event)
{
    foreach (auto btnkey, digitBtns.keys()) {
        if (event->key() == btnkey)
            digitBtns[btnkey]->animateClick();
    }

    if (event->key() == Qt::Key_Period) {
        ui->btnSign->animateClick();
    }
    if (event->key() == Qt::Key_Backspace) {
        ui->btnDel->animateClick();
    }
}

void capacity::on_btnSign_clicked()
{
    if (!operand.contains(".")) {
        operand += qobject_cast<QPushButton *>(sender())->text();
    }
    // ui->display->setText(operand);
}


void capacity::on_btnDel_clicked()
{
    operand = operand.left(operand.length() - 1);

    if(Position == "top"){
        ui->lineEditTop->setText(operand);
    }else if(Position == "bottom"){
        ui->lineEditBottom->setText(operand);
    }
}


void capacity::on_btnClear_clicked()
{
    if (operands.size() != 0) {
        operand = "";
    }
    operand = "";
    ui->lineEditTop->setText(operand);
    ui->lineEditBottom->setText(operand);
}

void capacity::btnNumClicked()
{
    QString digit = qobject_cast<QPushButton *>(sender())->text();

    if (digit == '0' && operand == '0')
        digit = "";

    if (digit != '0' && operand == '0')
        operand = "";

    operand += digit;

    if(Position == "top"){
        ui->lineEditTop->setText(operand);
    }else if(Position == "bottom"){
        ui->lineEditBottom->setText(operand);
    }

}

void capacity::on_comboBoxBottom_currentTextChanged(const QString &arg1)
{
    exchange();
}


void capacity::on_comboBoxTop_currentTextChanged(const QString &arg1)
{
    exchange();
}


void capacity::on_lineEditTop_textChanged(const QString &arg1)
{
    if(Position == "top")
        exchange();
}


void capacity::on_lineEditTop_selectionChanged()
{
    Position = "top";
    operand = "";

    ui->lineEditTop->setStyleSheet("QLineEdit { background-color: #666; color: #fff}");

    ui->lineEditBottom->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");
}


void capacity::on_lineEditBottom_textChanged(const QString &arg1)
{
    if(Position == "bottom")
        exchange();
}


void capacity::on_lineEditBottom_selectionChanged()
{
    Position = "bottom";
    operand = "";

    ui->lineEditBottom->setStyleSheet("QLineEdit { background-color: #666; color: #fff}");

    ui->lineEditTop->setStyleSheet("QLineEdit { background-color: #fff; color: #333}");
}

