#include "chengxuyuan.h"
#include "ui_chengxuyuan.h"

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
        {Qt::Key_9, ui->btnNum9}
    };
    binaryBtns = {{Qt::Key_Plus, ui->btnPlus},
                  {Qt::Key_Minus, ui->btnLeft},
                  {Qt::Key_Slash, ui->btnNor},
                  {Qt::Key_Asterisk, ui->btnXor},
                  {Qt::Key_Enter, ui->btnEqual},
                  };


}

chengxuyuan::~chengxuyuan()
{
    delete ui;
}
