#ifndef MASTERVIEW_H
#define MASTERVIEW_H

#include <QWidget>
#include "loginview.h"
#include "doctorview.h"
#include "patienteditview.h"
#include "patientview.h"
#include "wellcomeview.h"
#include "departmentview.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MasterView;
}
QT_END_NAMESPACE

class MasterView : public QWidget
{
    Q_OBJECT

public:
    MasterView(QWidget *parent = nullptr);
    ~MasterView();



public slots:
    void goLoginView();
    void goWellcomeView();
    void goDoctorView();
    void goDepartmentView();
    void goPatientView();
    void goPatientEditView(int rowNo);
    void goPreviousView();

private slots:
    void on_btBack_clicked();

    void on_stackedWidget_currentChanged(int arg1);

    void on_btLogout_clicked();

private:
    void pushWidgetToStackView(QWidget* widget);

    Ui::MasterView *ui;

    WellcomeView *wellcomeView;
    DoctorView *doctorView;
    PatientEditView *patientEditView;
    DepartmentView *departmentView;
    LoginView *loginView;
    PatientView *patientView;

};
#endif // MASTERVIEW_H
