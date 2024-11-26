#include "wellcomeview.h"
#include "ui_wellcomeview.h"

WellcomeView::WellcomeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WellcomeView)
{
    ui->setupUi(this);
}

WellcomeView::~WellcomeView()
{
    delete ui;
}
