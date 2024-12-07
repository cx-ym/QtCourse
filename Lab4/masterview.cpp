#include "masterview.h"
#include "ui_masterview.h"
#include <QDebug>
#include "idatabase.h"

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    this->setWindowFlag(Qt::FramelessWindowHint);

    goLoginView();

    IDatabase::getInstance();
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()
{
    loginView = new LoginView();
    pushWidgetToStackView(loginView);

    connect(loginView, SIGNAL(loginSuccess()), this, SLOT(goWellcomeView()));
}

void MasterView::goWellcomeView()
{
    wellcomeView = new WellcomeView();
    pushWidgetToStackView(wellcomeView);

    connect(wellcomeView, SIGNAL(goDepartmentView()), this, SLOT(goDepartmentView()));
    connect(wellcomeView, SIGNAL(goDoctorView()), this, SLOT(goDoctorView()));
    connect(wellcomeView, SIGNAL(goPatientView()), this, SLOT(goPatientView()));
}

void MasterView::goDoctorView()
{
    doctorView = new DoctorView();
    pushWidgetToStackView(doctorView);
}

void MasterView::goDepartmentView()
{
    departmentView = new DepartmentView();
    pushWidgetToStackView(departmentView);


}

void MasterView::goPatientView()
{
    patientView = new PatientView();
    pushWidgetToStackView(patientView);

    connect(patientView, SIGNAL(goPatientEditView()), this, SLOT(goPatientEditView()));
}

void MasterView::goPatientEditView()
{
    patientEditView = new PatientEditView();
    pushWidgetToStackView(patientEditView);
}

void MasterView::goPreviousView()
{
    int count = ui->stackedWidget->count();

    if (count > 1) {
        ui->stackedWidget->setCurrentIndex(count - 2);
        ui->labelTitle->setText(ui->stackedWidget->currentWidget()->windowTitle());

        QWidget *widget = ui->stackedWidget->widget(count - 1);
        ui->stackedWidget->removeWidget(widget);
        delete widget;
    }
}

void MasterView::pushWidgetToStackView(QWidget *widget)
{

    ui->stackedWidget->addWidget(widget);
    int count = ui->stackedWidget->count();
    ui->stackedWidget->setCurrentIndex(count - 1); //总是显示最新加入的View
    ui->labelTitle->setText(widget->windowTitle());
}


void MasterView::on_btBack_clicked()
{
    goPreviousView();
}


void MasterView::on_stackedWidget_currentChanged(int arg1)
{
    int count = ui->stackedWidget->count();
    if (count > 1) {
        ui->btBack->setEnabled(true);
    } else {
        ui->btBack->setEnabled(false);
    }

    QString title = ui->stackedWidget->currentWidget()->windowTitle();

    if (title == "欢迎") {
        ui->btLogout->setEnabled(true);
        ui->btBack->setEnabled(false);
    } else {
        ui->btLogout->setEnabled(false);
    }
}


void MasterView::on_btLogout_clicked()
{
    goPreviousView();
}

