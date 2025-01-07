#ifndef CHENGXUYUAN_H
#define CHENGXUYUAN_H

#include <QWidget>
#include <QStack>
#include <QMap>
#include <QPushButton>


namespace Ui {
class chengxuyuan;
}

class chengxuyuan : public QWidget
{
    Q_OBJECT

public:
    explicit chengxuyuan(QWidget *parent = nullptr);
    ~chengxuyuan();

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

    void on_science_triggered();

private:
    Ui::chengxuyuan *ui;
};

#endif // CHENGXUYUAN_H
