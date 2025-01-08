#include "date.h"
#include "ui_date.h"

date::date(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::date)
{
    ui->setupUi(this);

    // 获取当前日期
    QDate currentDate = QDate::currentDate();

    ui->dateEdit->setDate(currentDate);
    ui->dateEdit_2->setDate(currentDate);
    ui->dateEdit_4->setDate(currentDate);

    for (int i = 0; i <= 999; ++i) {
        ui->comboBox_3->addItem(QString("%1").arg(i));
    }
    for (int i = 0; i <= 999; ++i) {
        ui->comboBox_4->addItem(QString("%1").arg(i));
    }
    for (int i = 0; i <= 999; ++i) {
        ui->comboBox_2->addItem(QString("%1").arg(i));
    }

    ui->radioButton->setChecked(true);
    ui->lineEdit_2->setText(currentDate.toString("yyyy-MM-dd"));

    ui->stackedWidget->setCurrentIndex(0);
}

date::~date()
{
    delete ui;
}

void date::on_dateEdit_dateChanged(const QDate &date)
{

    QDateTime time1 = ui->dateEdit->dateTime();

    QDateTime time2 = ui->dateEdit_2->dateTime();

    int days = time1.daysTo(time2);


    for(int i = 1; i <= days; i++)
    {
        QDateTime nextWeek = time1.addDays(i);
        qDebug()<<"nextWeek=="<<nextWeek.toString("yyyy-MM-dd");
    }

    if(days < 0)
        days = -days;
    ui->lineEdit->setText(QString::number(days));

    qDebug() << "time2 - time1=" << days ;


}


void date::on_dateEdit_2_dateChanged(const QDate &date)
{
    QDateTime time1 = ui->dateEdit->dateTime();

    QDateTime time2 = ui->dateEdit_2->dateTime();

    int days = time1.daysTo(time2);


    for(int i = 1; i <= days; i++)
    {
        QDateTime nextWeek = time1.addDays(i);
        qDebug()<<"nextWeek=="<<nextWeek.toString("yyyy-MM-dd");
    }

    if(days < 0)
        days = -days;
    ui->lineEdit->setText(QString::number(days));
    qDebug() << "time2 - time1=" << days ;
}


void date::on_comboBox_currentIndexChanged(int index)
{
    qDebug()<<index;
    if(index == 0){
        ui->stackedWidget->setCurrentIndex(0);
    }
    if(index == 1){
        ui->stackedWidget->setCurrentIndex(1);
    }
}





void date::on_comboBox_2_currentTextChanged(const QString &arg1)
{
    qDebug()<<arg1;
    QString dateString = ui->lineEdit_2->text();
    QDate currentDate = QDate::fromString(dateString, "yyyy-MM-dd");
    QDate newDate;
    // int month = ui->comboBox_3->currentText().toInt();
    // int day = ui->comboBox_4->currentText().toInt();

    if(ui->radioButton->isChecked()){
        // newDate = currentDate.addDays(day);
        // newDate = currentDate.addMonths(month);
        newDate = currentDate.addYears(arg1.toInt());
    }
    else{
        // newDate = currentDate.addDays(-day);
        // newDate = currentDate.addMonths(-month);
        newDate = currentDate.addYears(-arg1.toInt());
    }

    ui->lineEdit_2->setText(newDate.toString("yyyy-MM-dd"));
}


void date::on_comboBox_4_currentTextChanged(const QString &arg1)
{
    qDebug()<<arg1;
    QString dateString = ui->lineEdit_2->text();
    QDate currentDate = QDate::fromString(dateString, "yyyy-MM-dd");
    QDate newDate;
    // int month = ui->comboBox_3->currentText().toInt();
    // int year = ui->comboBox_2->currentText().toInt();

    if(ui->radioButton->isChecked()){
        newDate = currentDate.addDays(arg1.toInt());
        // newDate = currentDate.addYears(year);
        // newDate = currentDate.addMonths(month);
    }
    else{
        newDate = currentDate.addDays(-arg1.toInt());
        // newDate = currentDate.addMonths(-month);
        // newDate = currentDate.addYears(-year);
    }

    ui->lineEdit_2->setText(newDate.toString("yyyy-MM-dd"));
}


void date::on_comboBox_3_currentTextChanged(const QString &arg1)
{
    qDebug()<<arg1;
    QString dateString = ui->lineEdit_2->text();
    QDate currentDate = QDate::fromString(dateString, "yyyy-MM-dd");
    QDate newDate;
    // int year = ui->comboBox_2->currentText().toInt();
    // int day = ui->comboBox_4->currentText().toInt();

    if(ui->radioButton->isChecked()){
        newDate = currentDate.addMonths(arg1.toInt());
        // newDate = currentDate.addDays(day);
        // newDate = currentDate.addYears(year);
    }
    else{
        newDate = currentDate.addMonths(-arg1.toInt());
        // newDate = currentDate.addDays(-day);
        // newDate = currentDate.addYears(-year);
    }

    ui->lineEdit_2->setText(newDate.toString("yyyy-MM-dd"));
}


void date::on_dateEdit_4_dateChanged(const QDate &date)
{
    qDebug()<<date;
    QDate newDate;
    QDate currentDate = date;
    int year = ui->comboBox_2->currentText().toInt();
    int month = ui->comboBox_3->currentText().toInt();
    int day = ui->comboBox_4->currentText().toInt();

    qDebug()<<"year="<<year<<"month="<<month<<"day="<<day;
    if(ui->radioButton->isChecked()){
        currentDate = currentDate.addMonths(month);
        currentDate = currentDate.addDays(day);
        currentDate = currentDate.addYears(year);
        qDebug()<<"hello";
    }
    else{
        currentDate = currentDate.addMonths(-month);
        currentDate = currentDate.addDays(-day);
        currentDate = currentDate.addYears(-year);
    }
    qDebug()<<newDate;
    newDate = currentDate;
    ui->lineEdit_2->setText(newDate.toString("yyyy-MM-dd"));
}

