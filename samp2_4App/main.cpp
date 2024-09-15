#include "qwmainwind.h"
#include <QApplication>
#include <QMainWindow>
#include <QToolBar>
#include <QAction>
#include <QMessageBox>
#include <QToolButton>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QWMainWind w;
    w.show();
    QToolBar *toolBar = w.addToolBar("My Toolbar");
    QToolButton *toolButton = new QToolButton();
    toolButton->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    // 创建一个动作（例如一个按钮）
    QAction *action = new QAction(QIcon(":/images/images/20.ico"), "关于", &w);
    toolButton->setDefaultAction(action);

    toolBar->addWidget(toolButton);
    // 连接点击信号和槽函数
    QObject::connect(action, &QAction::triggered, [&]() {
        // 这里添加点击按钮后的处理代码
        QMessageBox::information(&w, "Info", "杨成熙2022414040236");
    });

    w.show();
    return a.exec();
}
