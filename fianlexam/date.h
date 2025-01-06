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

private:
    Ui::date *ui;
};

#endif // DATE_H
