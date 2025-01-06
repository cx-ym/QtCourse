#include "chengxuyuan.h"
#include "ui_chengxuyuan.h"

chengxuyuan::chengxuyuan(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::chengxuyuan)
{
    ui->setupUi(this);
}

chengxuyuan::~chengxuyuan()
{
    delete ui;
}
