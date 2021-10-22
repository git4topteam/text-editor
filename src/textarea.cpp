#include "textarea.h"
#include <QTextStream>
#include <QDebug>
#include <cmath>
#include <future>

TextArea::TextArea(QWidget * wdg) : QTextEdit(wdg), m_file(nullptr)
{
    setText("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    append("Test line");
    m_maxValueScrollBar = 1000; //test
}

TextArea::~TextArea()
{

}

void TextArea::setFile(File* file)
{
    m_file = file;
    if(file->isMassive()){

        connect(this->verticalScrollBar(),&QScrollBar::valueChanged,m_file,[this]{
            m_file->readBlock(this->verticalScrollBar()->value(),this->verticalScrollBar()->maximum());
        });

        connect(m_file,&File::needUpdateText,this,&TextArea::updateText);

        this->setText(m_file->read(File::SIZE_BLOCK)); // прочитаем какую то малую часть

        int lines = this->toPlainText().count("\n");
       adaptScrollBar(lines,m_file->sizeFile());

        std::async(std::launch::async,[this](){this->adaptScrollBar(m_file);});

    }else {
        this->setText(m_file->readAll()); // если файл небольшой - читаем все
    }
}


void TextArea::resizeEvent(QResizeEvent *e)
{

    int posScrollBarBeforeResize = verticalScrollBar()->value();
    QTextEdit::resizeEvent(e);

    verticalScrollBar()->setMinimum(0);
    verticalScrollBar()->setMaximum(m_maxValueScrollBar);
    verticalScrollBar()->setValue(posScrollBarBeforeResize);

    qDebug() << verticalScrollBar()->maximum();
    qDebug() << verticalScrollBar()->value();
}

void TextArea::adaptScrollBar(File* file)
{
    int lines = file->countInFile("\n");
    setRangeScrollBar(0,lines);
}

void TextArea::adaptScrollBar(int lines)
{
    setRangeScrollBar(0,lines);
}

void TextArea::adaptScrollBar(int lines, int sizeFile)
{
    int maxValueScrollBar = std::ceil((lines * sizeFile) / File::SIZE_BLOCK); //возможна ошибка скролла,после округления
    setRangeScrollBar(0,maxValueScrollBar);
}

void TextArea::setRangeScrollBar(int min, int max)
{
    verticalScrollBar()->setMinimum(min);
    verticalScrollBar()->setMaximum(max);
    m_maxValueScrollBar = max;
}



void TextArea::updateText(const QString &text)
{
    this->setText(text);
}






