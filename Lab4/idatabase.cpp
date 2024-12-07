#include "idatabase.h"
#include <QUuid>

void IDatabase::ininDatabase()
{
    database = QSqlDatabase::addDatabase("QSQLITE");
    QString aFile = "E:/QTworkspace/Lab4/Lab4db.db";
    database.setDatabaseName(aFile);

    if (!database.open())
        qDebug() << "failed to open database";
    else
        qDebug() << "open database successful";
}

bool IDatabase::initPatientModel()
{
    PatientModel = new QSqlTableModel(this, database);
    PatientModel->setTable("patient");
    PatientModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    PatientModel->setSort(PatientModel->fieldIndex("name"), Qt::AscendingOrder);
    if (!PatientModel->select())
        return false;

    thePatientSelection = new QItemSelectionModel(PatientModel);
    return true;
}

bool IDatabase::searchPatient(QString filter)
{
    PatientModel->setFilter(filter);
    return PatientModel->select();
}

bool IDatabase::deleteCurrentPatient()
{
    QModelIndex curIndex = thePatientSelection->currentIndex();
    PatientModel->removeRow(curIndex.row());
    PatientModel->submitAll();
    PatientModel->select();
}

bool IDatabase::submitPatient()
{
    return PatientModel->submitAll();
}

void IDatabase::revertPatient()
{
    PatientModel->revertAll();
}

int IDatabase::AddNewPatient()
{
    PatientModel->insertRow(PatientModel->rowCount(), QModelIndex());
    QModelIndex curIndex = PatientModel->index(PatientModel->rowCount() - 1, 1);

    int curRecNo = curIndex.row();
    QSqlRecord curRec = PatientModel->record(curRecNo);
    curRec.setValue("CREATEDTIMESTAMP", QDateTime::currentDateTime().toString("yyyy-MM-dd"));
    curRec.setValue("ID", QUuid::createUuid().toString(QUuid::WithoutBraces));

    PatientModel->setRecord(curRecNo, curRec);

    return curIndex.row();
}

QString IDatabase::userLogin(QString userName, QString password)
{
    QSqlQuery query;
    query.prepare("select USERNAME,PASSWORD from User where USERNAME =  :USER");
    query.bindValue(":USER", userName);
    query.exec();
    if (!query.exec()) {
        // 数据库操作失败，返回更具体的错误信息
        return "Database operation failed: " + query.lastError().text();
    }

    if (query.first() && query.value("username").isValid()) {
        QString passwd = query.value("password").toString();
        if (passwd == password) {
            qDebug() << "login success";
            return "login success";
        } else {
            qDebug() << "wrong Password";
            return "wrong Password";
        }
    } else {
        qDebug() << "No Such User";
        return "wrong Username";
    }
}

IDatabase::IDatabase(QObject *parent)
    : QObject{parent}
{
    ininDatabase();
}
