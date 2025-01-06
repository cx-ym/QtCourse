#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "normal.h"
#include "science.h"
#include "date.h"
#include "chengxuyuan.h"
#include "change.h"

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
    void gotoChange();

private slots:
    void on_normal_triggered();

    void on_science_triggered();

    void on_programmer_triggered();

    void on_date_triggered();

    void on_change_triggered();

private:
    void pushWidgetToStackView(QWidget* widget);

private:
    Ui::MainWindow *ui;

    normal* Normal;
    science* Science;
    chengxuyuan* cxy;
    date* Date;
    change* Change;
};
#endif // MAINWINDOW_H
