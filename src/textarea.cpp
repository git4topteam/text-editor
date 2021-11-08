#include "textarea.h"


#include <QTextStream>
#include <QDebug>
#include <cmath>
#include <thread>
#include <QCloseEvent>
#include <QMessageBox>
#include <QRandomGenerator>

TextArea::TextArea(QWidget * wdg) : QTextEdit(wdg), m_file(nullptr),m_maxValueScrollBar(0)
{


}

TextArea::~TextArea()
{
    qDebug() << "deleted";
}

void TextArea::setFile(File* file)
{
    m_file = file;
    if(file->isMassive()){

        connect(this->verticalScrollBar(),&QScrollBar::valueChanged,m_file,&File::readBlock); //связь - слот на изменение скроллбара
        connect(this->verticalScrollBar(),&QScrollBar::valueChanged,this,&TextArea::test);
        connect(m_file,&File::needUpdateText,this,&TextArea::updateText); //файл достал кусок текста и передает его  в TextArea

        m_file->readBlock(0); // прочитаем какую то малую часть, и вставим текст

        int lines = this->toPlainText().count("\n");
        adaptScrollBar(lines,m_file->sizeFile());

        std::thread t(&TextArea::adaptScrollBarBasedFile,this, m_file);
        t.detach();


    }else {
        connect(m_file,&File::needUpdateText,this,&TextArea::updateText);
        m_file->readBlock(0);

        //вместо этого должно быть m_file->readAllData() , но этот метод не работает...
    }
}

bool TextArea::fileIsAssigned()
{
    if(m_file != nullptr){
    return true;
    }else{
    return false;
    }
}


void TextArea::resizeEvent(QResizeEvent *e)
{
    if(m_file != nullptr){
        if(!m_file->isMassive()){
            QTextEdit::resizeEvent(e);
            return void();
        }else{
            int posScrollBarBeforeResize = verticalScrollBar()->sliderPosition();
            QTextEdit::resizeEvent(e);

            verticalScrollBar()->setMinimum(0);
            verticalScrollBar()->setMaximum(m_maxValueScrollBar);

            verticalScrollBar()->setValue(posScrollBarBeforeResize);
            verticalScrollBar()->setSliderPosition(posScrollBarBeforeResize);

        }
    }else{
        QTextEdit::resizeEvent(e);
        return void();
    }

}

void TextArea::closeEvent(QCloseEvent *event)
{
    if (QRandomGenerator::global()->generate() & 1) {
        QMessageBox msgBox;
        msgBox.setText("Fuck off!");
        msgBox.exec();
        event->ignore();
    } else {
        event->accept();
    }
}


void TextArea::adaptScrollBarBasedFile(File* file)
{
    uint64_t lines = file->countLines();
    setRangeScrollBar(0,lines);

}

void TextArea::adaptScrollBar(int lines)
{
    setRangeScrollBar(0,lines);
}

void TextArea::adaptScrollBar(int lines, qint64 sizeFile)
{
    int maxValueScrollBar = std::ceil((lines * sizeFile) / File::SIZE_BLOCK); //возможна ошибка скролла,после округления
    setRangeScrollBar(0,maxValueScrollBar);
}

void TextArea::setRangeScrollBar(int min, int max)
{
    verticalScrollBar()->setMinimum(min);
    verticalScrollBar()->setMaximum(max);
    m_maxValueScrollBar = max;

    //102262649
}

void TextArea::test()
{
    qDebug() << verticalScrollBar()->maximum();
    qDebug() << verticalScrollBar()->value();
}


void TextArea::updateText(const QString &text,int posScrollBar)
{
    verticalScrollBar()->blockSignals(true);
    this->setText(text);
    verticalScrollBar()->setMaximum(m_maxValueScrollBar); // по хорошему нужно что это убрать, отключить какой то сигнал об обновлении скрола
    verticalScrollBar()->setValue(posScrollBar);
    verticalScrollBar()->blockSignals(false);

    qDebug() << "updateText" << m_maxValueScrollBar;
}



