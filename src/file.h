#pragma once
#include <QObject>
#include <QFile>
#include <QTextStream>

class File : public QFile
{
    Q_OBJECT
public:
    File(const QString& path,QObject* object = nullptr);
    ~File();
    bool isMassive();
    qint64 sizeFile();
    uint64_t countInFile(const QString& str);
    uint64_t countLines();
    float getAverageLineSize();
    void setLinesInFile(uint64_t totalLines);
    QString readAllData(); // почему не работает этот метод, в упор не вижу


    static constexpr int SIZE_BLOCK = 10485760; //10mb
  private:
    bool m_isMassiveFile;
    uint m_totalLines;
    std::vector<uint64_t> m_linesMap;
    QTextStream* m_textStream;
public slots:
    void readBlock(int posScrollBar);
    void updateText(const QString& text,int posScrollBar);

signals:
    void needUpdateText(const QString& text,int posScrollBar);
};


