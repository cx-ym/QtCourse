#ifndef NORMAL_H
#define NORMAL_H

#include <QStack>
#include <QMap>
#include <QPushButton>

namespace Ui {
class normal;
}

class normal : public QWidget
{
    Q_OBJECT

public:
    explicit normal(QWidget *parent = nullptr);
    ~normal();

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


signals:
    void gotoScience();

private:
    Ui::normal *ui;
};

#endif // NORMAL_H
