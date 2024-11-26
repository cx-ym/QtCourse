#ifndef WELLCOMEVIEW_H
#define WELLCOMEVIEW_H

#include <QWidget>

namespace Ui {
class WellcomeView;
}

class WellcomeView : public QWidget
{
    Q_OBJECT

public:
    explicit WellcomeView(QWidget *parent = nullptr);
    ~WellcomeView();

private:
    Ui::WellcomeView *ui;
};

#endif // WELLCOMEVIEW_H
