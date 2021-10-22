#include "file.h"

File::File(const QString &path, QObject* object) : QFile(path,object),
    m_isMassiveFile(false)
{
    //здесь узнаем о файле , например, размер файла, нужно ли включать ленивую загрузку

    if(size() > 20000){ // порог для ленивой загрузки, нужно указавывать в настройках
        m_lazyReader = new LazyReader(this);
        connect(m_lazyReader,&LazyReader::readFinished,this,&File::updateText);
        m_isMassiveFile = true;
    }

}

bool File::isMassive()
{
    return m_isMassiveFile;
}

uint64_t File::sizeFile()
{
    return size();
}

int File::countInFile(const QString &str)
{
    if(!seek(0)){
        return 0;
    }

    uint counter = 0;

    QByteArray byteArray;
    while(!atEnd()){
        byteArray = read(52428800); // 50mb

        for(int i = 0; i < byteArray.size();i++){
            if(str == byteArray.at(i)){
                counter++;
            }

        }
    }

    return counter;

}



void File::readBlock(int posScrollBar,int maxScrollbarPos)
{
    m_lazyReader->readBlock(posScrollBar,maxScrollbarPos);
}

void File::updateText(const QString &text)
{
    emit needUpdateText(text);
}
