#ifndef FILEMANAGER_H
#define FILEMANAGER_H

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


private: // приватные атрибуты
std::vector<File*> m_openFiles;


private: //приватные методы


};

#endif // FILEMANAGER_H
