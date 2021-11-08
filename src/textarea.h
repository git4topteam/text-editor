#pragma once
#include <QObject>
#include <QTextEdit>
#include <QScrollBar>
#include "file.h"


class TextArea : public QTextEdit { // наследуемся, чтобы добавить возможность нумерации строк, подцветку выделенной строки и тд
    Q_OBJECT
public:
    explicit TextArea(QWidget *wdg = nullptr);

    // move оператор нужно реализовать и конструктор копирования?


    ~TextArea();
    void setFile(File* file);
    bool fileIsAssigned();



protected:
  void resizeEvent(QResizeEvent *e) override;
  void closeEvent(QCloseEvent *event) override;
 // void scrollContentsBy(int dx, int dy) override;

 private:
    File* m_file;

    int m_maxValueScrollBar;
private:
    void adaptScrollBarBasedFile(File *file);
    void adaptScrollBar(int lines);
    void adaptScrollBar(int lines, qint64 sizeFile);
    void setRangeScrollBar(int min,int max);



private slots:
    void test();
    void updateText(const QString& text, int posScrollBar);


};

