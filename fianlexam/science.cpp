#include "science.h"
#include "ui_science.h"

science::science(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::science)
{
    ui->setupUi(this);
}

science::~science()
{
    delete ui;
}
