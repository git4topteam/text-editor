#include "filemanager.h"

FileManager::FileManager(QObject *object) : QObject(object)
{

}

FileManager::~FileManager()
{
    for(auto& file : m_openFiles){
    file->close();
    }
}

int FileManager::openFile(const QString &path)
{
  File* file = new File(path,this);

   if(!file->open(QIODevice::ReadWrite | QIODevice::Append | QIODevice::Text)){
    return 0;
   }

   m_openFiles.push_back(file);

   return 1;
}

int FileManager::saveFile(const QString &path)
{

}

File *FileManager::getFile(int index)
{
    if(index == -1){
     index = m_openFiles.size() - 1; // не передали индекс - берем последний открытый файл
    }


    return m_openFiles.at(index);
}


