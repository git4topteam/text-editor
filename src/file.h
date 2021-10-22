#ifndef FILEPROPERTIES_H
#define FILEPROPERTIES_H

#include <QObject>
#include <QFile>
#include "lazyreader.h"

class File : public QFile
{
    Q_OBJECT
public:
    File(const QString& path,QObject* object = nullptr);
    bool isMassive();
    uint64_t sizeFile();
    int countInFile(const QString& str);
    static constexpr int SIZE_BLOCK = 100000;

  private:
    LazyReader* m_lazyReader;
    bool m_isMassiveFile;
public slots:
    void readBlock(int posScrollBar,int maxScrollbarPos);
    void updateText(const QString& text);
signals:
    void needUpdateText(const QString& text);
};

#endif // FILEPROPERTIES_H
