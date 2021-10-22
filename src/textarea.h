#ifndef TEXTAREA_H
#define TEXTAREA_H
#include <QObject>
#include <QTextEdit>
#include <QScrollBar>
#include "file.h"


class TextArea : public QTextEdit { // наследуемся, чтобы добавить возможность нумерации строк, подцветку выделенной строки и тд
    Q_OBJECT
public:
    explicit TextArea(QWidget *wdg = nullptr);
    ~TextArea();
    void setFile(File* file);



protected:
   void resizeEvent(QResizeEvent *e) override;


 private:
    File* m_file;

    int m_maxValueScrollBar;
private:
    void adaptScrollBar(File *file);
    void adaptScrollBar(int lines);
    void adaptScrollBar(int lines,int sizeFile);
    void setRangeScrollBar(int min,int max);



private slots:
    void updateText(const QString& text);


};
#endif // TEXTAREA_H
