#include "patienteditview.h"
#include "ui_patienteditview.h"
#include "idatabase.h"
#include <QSqlTableModel>

PatientEditView::PatientEditView(QWidget *parent, int index) :
    QWidget(parent),
    ui(new Ui::PatientEditView)
{
    ui->setupUi(this);

    dataMapper = new QDataWidgetMapper();
    QSqlTableModel *tableModel = IDatabase::getInstance().PatientModel;
    dataMapper->setModel(IDatabase::getInstance().PatientModel);
    dataMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);

    dataMapper->addMapping(ui->dbEditID, tableModel->fieldIndex("ID"));
    dataMapper->addMapping(ui->dbEditName, tableModel->fieldIndex("NAME"));
    dataMapper->addMapping(ui->dbEditIDCard, tableModel->fieldIndex("ID_CARD"));
    dataMapper->addMapping(ui->dbSpinHeight, tableModel->fieldIndex("HEIGHT"));
    dataMapper->addMapping(ui->dbSpinWeight, tableModel->fieldIndex("WEIGHT"));
    dataMapper->addMapping(ui->dbEditMobile, tableModel->fieldIndex("MOBILEPHONE"));
    dataMapper->addMapping(ui->dbDateEditDOB, tableModel->fieldIndex("DOB"));
    dataMapper->addMapping(ui->dbComboSex, tableModel->fieldIndex("SEX"));
    dataMapper->addMapping(ui->dbCreatedTimestamp, tableModel->fieldIndex("CREATEDTIMESTAMP"));

    dataMapper->setCurrentIndex(index);
}

PatientEditView::~PatientEditView()
{
    delete ui;
}

void PatientEditView::on_pushButton_clicked()
{
    IDatabase::getInstance().submitPatient();
    emit goPreviousView();
}


void PatientEditView::on_pushButton_2_clicked()
{
    IDatabase::getInstance().revertPatient();
    emit goPreviousView();
}

