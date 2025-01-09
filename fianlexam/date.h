#ifndef DATE_H
#define DATE_H

#include <QWidget>

namespace Ui {
class date;
}

class date : public QWidget
{
    Q_OBJECT

public:
    explicit date(QWidget *parent = nullptr);
    ~date();

private slots:
    void on_dateEdit_dateChanged(const QDate &date);

    void on_dateEdit_2_dateChanged(const QDate &date);

    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentTextChanged(const QString &arg1);

    void on_comboBox_4_currentTextChanged(const QString &arg1);

    void on_comboBox_3_currentTextChanged(const QString &arg1);

    void on_dateEdit_4_dateChanged(const QDate &date);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

private:
    Ui::date *ui;
};

#endif // DATE_H
