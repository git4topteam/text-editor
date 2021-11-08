#pragma once
#include <QObject>
#include <QFile>
#include "file.h"

class FileManager : public QObject
{
    Q_OBJECT
public:
    FileManager(QObject* object = nullptr);
    ~FileManager();
    int openFile(const QString& path);
    int saveFile(const QString& path);
    File *getFile(int index = -1);
    void closeFile(size_t index);

private: // приватные атрибуты
    std::vector<File*> m_openFiles;


private: //приватные методы


};

