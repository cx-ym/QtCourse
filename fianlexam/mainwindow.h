#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTranslator>
#include "normal.h"
#include "science.h"
#include "date.h"
#include "chengxuyuan.h"
#include "currency.h"
#include "capacity.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void gotoNormal();
    void gotoScience();
    void gotoProgrammer();
    void gotoDate();
    void gotoCurrency();
    void gotoCapacity();

private slots:
    void on_normal_triggered();

    void on_science_triggered();

    void on_programmer_triggered();

    void on_date_triggered();

    void on_currency_triggered();

    void on_capacity_triggered();

    void on_Chinexe_triggered();

    void on_English_triggered();

private:
    void pushWidgetToStackView(QWidget* widget);

private:
    Ui::MainWindow *ui;

    QTranslator * translator;
    normal* Normal;
    science* Science;
    chengxuyuan* cxy;
    date* Date;
    currency* Currency;
    capacity* Capacity;
};
#endif // MAINWINDOW_H
