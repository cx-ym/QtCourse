#include "masterview.h"
#include "ui_masterview.h"
#include <QDebug>

MasterView::MasterView(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MasterView)
{
    ui->setupUi(this);

    goLoginView();
}

MasterView::~MasterView()
{
    delete ui;
}

void MasterView::goLoginView()
{
    loginView = new LoginView();
    pushWidgetToStackView(loginView);
}

void MasterView::goWellcomeView()
{
    wellcomeView = new WellcomeView();
    pushWidgetToStackView(wellcomeView);
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

