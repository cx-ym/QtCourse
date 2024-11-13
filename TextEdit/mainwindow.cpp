#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "replacedialog.h"
#include "searchdialog.h"
#include "QFileDialog"
#include "QMessageBox"
#include "QTextStream"
#include "QColorDialog"
#include "QFontDialog"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    textChanged = false;
    on_actionNew_triggered();

    statusLabel.setMaximumWidth(280);
    statusLabel.setText("length: " + QString::number(0) + "   lines: " + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusLabel);

    statusCursorLabel.setMaximumWidth(280);
    statusCursorLabel.setText("Ln: " + QString::number(0) + "   Col: " + QString::number(1));
    ui->statusbar->addPermanentWidget(&statusCursorLabel);

    QLabel *author = new QLabel(ui->statusbar);
    author->setText(tr("杨成熙"));
    ui->statusbar->addPermanentWidget(author);

    ui->actionCopy->setEnabled(false);
    ui->actionCut->setEnabled(false);
    ui->actionUndo->setEnabled(false);
    ui->actionRedo->setEnabled(false);
    // ui->actionPaste->setEnabled(false);

    ui->actionStatusBar->setChecked(true);
    ui->actionToolbar->setChecked(true);
    ui->actionLineNumbers->setChecked(false);
    on_actionLineNumbers_triggered(false);

    //connect(ui->actionLineNumbers, SIGNAL(triggered(bool)), ui->TextEdit, SLOT(hideLineNumberArea(bool)));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionAbout_triggered()
{
    AboutDialog dlg;
    dlg.exec();
}


void MainWindow::on_actionFind_triggered()
{
    SearchDialog sdl(this, ui->TextEdit);
    sdl.exec();
}


void MainWindow::on_actionReplace_triggered()
{
    ReplaceDialog rdl(this, ui->TextEdit);
    rdl.exec();
}


void MainWindow::on_actionNew_triggered()
{
    if (!userEditConfirm())
        return ;

    filePath = "";
    ui->TextEdit->clear();
    this->setWindowTitle(tr("新建文本文件 - 编辑器"));

    textChanged = false;
}


void MainWindow::on_actionOpen_triggered()
{
    if (!userEditConfirm())
        return ;

    QString filename = QFileDialog::getOpenFileName(this, "打开文件", ".", tr("Text files (*.txt) ;;All(*.*)"));
    QFile file(filename);

    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "打开文件失败");
        return ;
    }

    filePath = filename;

    QTextStream in(&file);
    QString text = in.readAll();
    ui->TextEdit->insertPlainText(text);
    file.close();

    this->setWindowTitle(QFileInfo(filename).absoluteFilePath());

    textChanged = false;
}


void MainWindow::on_actionSaveAs_triggered()
{
    QString filename = QFileDialog::getSaveFileName(this, "保存文件", ".",
                       tr("Text files (*.txt)"));
    QFile file(filename);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "打开文件失败");
        return ;
    }
    filePath = filename;
    QTextStream out(&file);
    QString text = ui->TextEdit->toPlainText();
    out << text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());

}


void MainWindow::on_actionSave_triggered()
{
    if (filePath == "") {
        QString filename = QFileDialog::getSaveFileName(this, "保存文件", ".",
                           tr("Text files (*.txt)"));
        QFile file(filename);
        if (!file.open(QFile::WriteOnly | QFile::Text)) {
            QMessageBox::warning(this, "..", "打开保存文件失败");
            return ;
        }
        file.close();
        filePath = filename;
    }

    QFile file(filePath);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        QMessageBox::warning(this, "..", "打开保存文件失败");
        return ;
    }
    QTextStream out(&file);
    QString text = ui->TextEdit->toPlainText();
    out << text;
    file.flush();
    file.close();

    this->setWindowTitle(QFileInfo(filePath).absoluteFilePath());
    textChanged = false;
}


void MainWindow::on_TextEdit_textChanged()
{
    if (!textChanged) {
        this->setWindowTitle("*" + this->windowTitle());
        textChanged = true;
    }
    statusLabel.setText("length: " + QString::number(ui->TextEdit->toPlainText().length()) + "   lines: " + QString::number(
                            ui->TextEdit->document()->lineCount()));


}

bool MainWindow::userEditConfirm()
{
    if (textChanged) {
        QString path = filePath != "" ? filePath : "无标题.txt";

        QMessageBox msg(this);
        msg.setIcon(QMessageBox::Question);
        msg.setWindowTitle("..");
        msg.setWindowFlag(Qt::Drawer);
        msg.setText(QString("是否将更改保存到\n") + "\"" + path + "\" ?");
        msg.setStandardButtons(QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);

        int r = msg.exec();
        switch (r) {
        case QMessageBox::Yes:
            on_actionSave_triggered();
            break;
        case QMessageBox::No:
            ui->TextEdit->clear();
            textChanged = false;
            break;
        case QMessageBox::Cancel:
            return false;
        }
    }

    return true;
}




void MainWindow::on_actionUndo_triggered()
{
    ui->TextEdit->undo();
}


void MainWindow::on_actionCut_triggered()
{
    ui->TextEdit->cut();

}

void MainWindow::on_actionCopy_triggered()
{
    ui->TextEdit->copy();
}


void MainWindow::on_actionPaste_triggered()
{
    ui->TextEdit->paste();
}


void MainWindow::on_actionRedo_triggered()
{
    ui->TextEdit->redo();
}


void MainWindow::on_TextEdit_copyAvailable(bool b)
{
    ui->actionCopy->setEnabled(b);
    ui->actionCut->setEnabled(b);
}


void MainWindow::on_TextEdit_redoAvailable(bool b)
{
    ui->actionRedo->setEnabled(b);
}


void MainWindow::on_TextEdit_undoAvailable(bool b)
{
    ui->actionUndo->setEnabled(b);
}


void MainWindow::on_actionFontColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "选择颜色");
    if (color.isValid()) {
        ui->TextEdit->setStyleSheet(QString("QPlainTextEdit {color: %1}").arg(color.name()));
    }
}


void MainWindow::on_actionFontbgc_triggered()
{

}


void MainWindow::on_actionEditerColor_triggered()
{
    QColor color = QColorDialog::getColor(Qt::black, this, "选择颜色");
    if (color.isValid()) {
        ui->TextEdit->setStyleSheet(QString("QPlainTextEdit {background-color: %1}").arg(color.name()));
    }
}


void MainWindow::on_actionAutoWrap_triggered()
{
    QPlainTextEdit::LineWrapMode mode = ui->TextEdit->lineWrapMode();

    if (mode == QTextEdit::NoWrap) {
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::WidgetWidth);

        ui->actionAutoWrap->setCheckable(true);
    } else {
        ui->TextEdit->setLineWrapMode(QPlainTextEdit::NoWrap);

        ui->actionAutoWrap->setCheckable(false);
    }
}


void MainWindow::on_actionFont_triggered()
{
    bool ok = false;
    QFont font = QFontDialog::getFont(&ok, this);
    if (ok) {
        ui->TextEdit->setFont(font);
    }
}


void MainWindow::on_actionToolbar_triggered()
{
    bool visible = ui->toolBar->isVisible();
    ui->toolBar->setVisible(!visible);
    ui->actionToolbar->setCheckable(!visible);
}


void MainWindow::on_actionStatusBar_triggered()
{
    bool visible = ui->statusbar->isVisible();
    ui->statusbar->setVisible(!visible);
    ui->actionStatusBar->setCheckable(!visible);
}


void MainWindow::on_actionSelectAll_triggered()
{
    ui->TextEdit->selectAll();
}


void MainWindow::on_actionExit_triggered()
{
    if (userEditConfirm()) {
        exit(0);
    }

}


void MainWindow::on_TextEdit_cursorPositionChanged()
{
    int col = 0;
    int ln = 0;
    int flg = -1;
    int pos = ui->TextEdit->textCursor().position();
    QString text = ui->TextEdit->toPlainText();

    for (int i = 0; i < pos; i++) {
        if (text[i] == '\n') {
            ln++;
            flg = i;
        }
    }
    flg++;
    col = pos - flg;
    statusCursorLabel.setText("length: " + QString::number(ln + 1) + "   lines: " + QString::number(col + 1));
}


void MainWindow::on_actionLineNumbers_triggered(bool checked)
{
    ui->TextEdit->hideLineNumberArea(!checked);
}

