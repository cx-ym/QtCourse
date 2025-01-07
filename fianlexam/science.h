#ifndef SCIENCE_H
#define SCIENCE_H

#include <QWidget>
#include <QStack>
#include <QMap>
#include <QPushButton>
#include <QDebug>

namespace Ui {
class science;
}

class science : public QWidget
{
    Q_OBJECT

public:
    explicit science(QWidget *parent = nullptr);
    ~science();

    QString operand;
    QString operandtmp;
    QString opcode;
    QString codetmp;
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

    void on_btnClear_clicked();

    void on_btnSin_clicked();

    void on_btnCos_clicked();

    void on_btnTan_clicked();

    void on_btnLog_clicked();

private:
    Ui::science *ui;
};

#endif // SCIENCE_H
