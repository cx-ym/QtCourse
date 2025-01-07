#ifndef CHENGXUYUAN_H
#define CHENGXUYUAN_H

#include <QWidget>
#include <QStack>
#include <QMap>
#include <QPushButton>
#include <QString>
#include <iostream>
#include <sstream>
#include <string>
#include <bitset>


namespace Ui {
class chengxuyuan;
}

class chengxuyuan : public QWidget
{
    Q_OBJECT

public:
    explicit chengxuyuan(QWidget *parent = nullptr);
    ~chengxuyuan();

    QString Type;
    QString operand;
    QString operandtmp;
    QString opcode;
    QString codetmp;
    QStack<QString> operands;
    QStack<QString> opcodes;
    QMap<int, QPushButton *> digitBtns;
    QMap<int, QPushButton *> binaryBtns;
    QList<QPushButton*> buttons;


    void printContent();
    void calculation();
    void setButtonsEnabled(QList<QPushButton*>& buttons, bool enabled);

private slots:
    void btnNumClicked();

    void on_btnSign_clicked();

    void on_btnDel_clicked();

    void on_btnClearAll_clicked();

    void on_btnEqual_clicked();

    void on_btnChange_clicked();

    virtual void keyPressEvent(QKeyEvent* event);

    void on_btnClear_clicked();

    void on_btnLeft_clicked();

    void on_btnRight_clicked();


    void on_lineEditHex_selectionChanged();

    void on_lineEditDec_selectionChanged();

    void on_lineEditOct_selectionChanged();

    void on_lineEditBin_selectionChanged();


    void on_btnAnd_clicked();

    void on_btnOr_clicked();

    void on_btnNot_clicked();

    void on_btnNand_clicked();

    void on_btnNor_clicked();

    void on_btnXor_clicked();

private:
    Ui::chengxuyuan *ui;

};

#endif // CHENGXUYUAN_H
