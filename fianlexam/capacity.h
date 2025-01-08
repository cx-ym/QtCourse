#ifndef CAPACITY_H
#define CAPACITY_H

#include <QMap>
#include <QStack>
#include <QPushButton>
#include <QWidget>

namespace Ui {
class capacity;
}

class capacity : public QWidget
{
    Q_OBJECT

public:
    explicit capacity(QWidget *parent = nullptr);
    ~capacity();

    QString operand;
    QString Position;
    QString operandtmp;
    QString opcode;
    QString codetmp;
    QStack<QString> operands;
    QStack<QString> opcodes;

    QMap<int, QPushButton *> digitBtns;

    void exchange();

    double convertToBaseUnit(double value, const QString& unit);

    double convertFromBaseUnit(double value, const QString& unit);

private slots:
    void btnNumClicked();

    void on_btnSign_clicked();

    void on_btnDel_clicked();

    void on_btnClear_clicked();

    virtual void keyPressEvent(QKeyEvent* event);

    void on_comboBoxBottom_currentTextChanged(const QString &arg1);

    void on_comboBoxTop_currentTextChanged(const QString &arg1);

    void on_lineEditTop_textChanged(const QString &arg1);

    void on_lineEditTop_selectionChanged();

    void on_lineEditBottom_textChanged(const QString &arg1);

    void on_lineEditBottom_selectionChanged();

private:
    Ui::capacity *ui;
};

#endif // CAPACITY_H
