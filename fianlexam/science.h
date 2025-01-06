#ifndef SCIENCE_H
#define SCIENCE_H

#include <QWidget>

namespace Ui {
class science;
}

class science : public QWidget
{
    Q_OBJECT

public:
    explicit science(QWidget *parent = nullptr);
    ~science();

private:
    Ui::science *ui;
};

#endif // SCIENCE_H
