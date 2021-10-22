#ifndef LAZYREADER_H
#define LAZYREADER_H

#include <QObject>
#include <QFile>

class LazyReader : public QObject // возможно этот класс нах не нужен, но это не точно
{
    Q_OBJECT
public:
    LazyReader(QObject* object = nullptr);
    void readBlock(int posScrollBar, int maxScrollBarPos);
private:
    QFile* m_file;

 signals:
    void readFinished(const QString& text );
};

#endif // LAZYREADER_H
