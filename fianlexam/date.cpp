#include "date.h"
#include "ui_date.h"

date::date(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::date)
{
    ui->setupUi(this);
}

date::~date()
{
    delete ui;
}
