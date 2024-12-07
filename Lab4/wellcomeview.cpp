#include "wellcomeview.h"
#include "ui_wellcomeview.h"
#include <QDebug>

WellcomeView::WellcomeView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WellcomeView)
{
    qDebug() << "create wellcome";
    ui->setupUi(this);
}

WellcomeView::~WellcomeView()
{
    qDebug() << "destroy wellcome";
    delete ui;
}

void WellcomeView::on_pushButton_clicked()
{
    emit goDepartmentView();
}


void WellcomeView::on_pushButton_2_clicked()
{
    emit goDoctorView();
}


void WellcomeView::on_pushButton_3_clicked()
{
    emit goPatientView();
}

