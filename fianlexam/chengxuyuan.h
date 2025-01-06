#ifndef CHENGXUYUAN_H
#define CHENGXUYUAN_H

#include <QWidget>

namespace Ui {
class chengxuyuan;
}

class chengxuyuan : public QWidget
{
    Q_OBJECT

public:
    explicit chengxuyuan(QWidget *parent = nullptr);
    ~chengxuyuan();

private:
    Ui::chengxuyuan *ui;
};

#endif // CHENGXUYUAN_H
