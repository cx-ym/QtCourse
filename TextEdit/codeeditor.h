#ifndef CODEEDIT_H
#define CODEEDIT_H

#include <QObject>
#include <QPlainTextEdit>

class CodeEditor : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit CodeEditor(QWidget *parent = nullptr);

    void lineNumberAreaPainterEvent(QPaintEvent *event);

    int lineNumberAreaWidth();// 更新行号部分的宽度，并且设置视口部件的margin

protected:
    void resizeEvent(QResizeEvent *e) override;

private slots:
    void updateLineNumerAreaWidth(int newBlockCount);
    void highlightCurrentLine();
    void updateLineNumberArea(const QRect &rect, int dy);
public:
    void hideLineNumberArea(bool flag);

private:
    QWidget *lineNumberArea;

};

class LineNumberArea : public QWidget
{
    Q_OBJECT

public:
    LineNumberArea(CodeEditor *editor) : QWidget(editor), codeEditor(editor) {}
protected:

    void paintEvent(QPaintEvent *event) override
    {
        codeEditor->lineNumberAreaPainterEvent(event);
    }

private:
    CodeEditor *codeEditor;
};


#endif // CODEEDIT_H
