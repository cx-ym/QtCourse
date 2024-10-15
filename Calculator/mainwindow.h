#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStack>
#include <QMap>
#include <QPushButton>

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

    QString operand;
    QString opcode;
    QStack<QString> operands;
    QStack<QString> opcodes;
    QMap<int, QPushButton *> digitBtns;
    QMap<int, QPushButton *> binaryBtns;

    QString calculation(bool *ok = NULL);

private slots:
    void btnNumClicked();

    void btnBinaryOperatorClicked();

    void btnUnaryOperatorClickead();

    void on_btnSign_clicked();

    void on_btnDel_clicked();

    void on_btnClearAll_clicked();

    void on_btnEqual_clicked();

    void on_btnChange_clicked();

    virtual void keyPressEvent(QKeyEvent* event);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
