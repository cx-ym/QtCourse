#include "change.h"
#include "ui_change.h"

change::change(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::change)
{
    ui->setupUi(this);
}

change::~change()
{
    delete ui;
}
