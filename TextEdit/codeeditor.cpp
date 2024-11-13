#include "codeeditor.h"
#include <QPainter>
#include <QTextBlock>



CodeEditor::CodeEditor(QWidget *parent) : QPlainTextEdit(parent)
{
    lineNumberArea = new LineNumberArea(this);

    connect(this, &CodeEditor::blockCountChanged, this, &CodeEditor::updateLineNumerAreaWidth);


    connect(this, &CodeEditor::updateRequest, this, &CodeEditor::updateLineNumberArea);


    connect(this, &CodeEditor::cursorPositionChanged, this, &CodeEditor::highlightCurrentLine);

    updateLineNumerAreaWidth(0);
    highlightCurrentLine();
    resize(300, 200);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

}


//绘制行号
void CodeEditor::lineNumberAreaPainterEvent(QPaintEvent *event)
{
    QPainter painter(lineNumberArea);
    painter.fillRect(event->rect(), Qt::lightGray);


    QTextBlock block = firstVisibleBlock();


    int blockNumber = block.blockNumber();


    int top = qRound(blockBoundingGeometry(block).translated(contentOffset()).top());
    int bottom = top + qRound(blockBoundingRect(block).height());


    while (block.isValid() && top <= event->rect().bottom()) {
        if (block.isVisible() && bottom >= event->rect().top()) {
            QString number = QString::number(blockNumber + 1);
            painter.drawText(0, top, lineNumberArea->width(), fontMetrics().height(), Qt::AlignRight, number);
        }

        block = block.next();
        top = bottom;
        bottom = top + qRound(blockBoundingRect(block).height());
        ++blockNumber;
    }
}


int CodeEditor::lineNumberAreaWidth()
{
    int digits = 1;

    int max = qMax(1, blockCount());
    while (max >= 10) {
        max /= 10;
        ++digits;
    }


    int space = 3 + fontMetrics().horizontalAdvance(QLatin1Char('9')) * digits;
    return  space;
}

//在左侧设置行号区域
void CodeEditor::resizeEvent(QResizeEvent *e)
{
    QPlainTextEdit::resizeEvent(e);

    QRect cr = contentsRect();
    lineNumberArea->setGeometry(QRect(cr.left(), cr.top(), lineNumberAreaWidth(), cr.height()));
}

// 更新行号部分的宽度，并且设置视口部件的margin
void CodeEditor::updateLineNumerAreaWidth(int /*newBlockCount*/)
{

    setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);
}


//高亮光标所在行，使用QPlainTextEdit::setExtraSelections
//设计富文本格式的一些知识
void CodeEditor::highlightCurrentLine()
{
    QList<QTextEdit::ExtraSelection> extraSelections;

    if (!isReadOnly()) {
        QTextEdit::ExtraSelection selection;
        QColor lineColor = QColor(Qt::yellow).lighter(160);

        selection.format.setBackground(lineColor);
        selection.format.setProperty(QTextFormat::FullWidthSelection, true);
        selection.cursor = textCursor();
        selection.cursor.clearSelection();
        extraSelections.append(selection);
    }
    setExtraSelections(extraSelections);
}

void CodeEditor::updateLineNumberArea(const QRect &rect, int dy)
{

    if (dy)
        lineNumberArea->scroll(0, dy);
    else
        lineNumberArea->update (0, rect.y(), lineNumberArea->width(), rect.height());


    if (rect.contains(viewport()->rect()))
        updateLineNumerAreaWidth(0);
}

void CodeEditor::hideLineNumberArea(bool flag)
{
    if (flag) {
        lineNumberArea->hide();
        setViewportMargins(0, 0, 0, 0);
    } else {

        lineNumberArea->show();
        setViewportMargins(lineNumberAreaWidth(), 0, 0, 0);

    }
}

