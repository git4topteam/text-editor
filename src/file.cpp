#include "file.h"


File::File(const QString &path, QObject* object) : QFile(path,object),
    m_isMassiveFile(false),
    m_totalLines(0)
{
    //здесь узнаем о файле , например, размер файла, нужно ли включать ленивую загрузку

    if(sizeFile() > SIZE_BLOCK){ // порог для ленивой загрузки, нужно указавывать в настройках
        m_isMassiveFile = true;
    }

    m_textStream = new QTextStream(this);

}

File::~File() {
    delete m_textStream;
}

bool File::isMassive()
{
    return m_isMassiveFile;
}

qint64 File::sizeFile()
{
    return size();
}

uint64_t File::countLines()
{
    uint64_t lines =  countInFile("\n");
    setLinesInFile(lines);
    return  lines;
}

float File::getAverageLineSize()
{
    if(m_totalLines == 0){
        m_totalLines = countLines();
    }

    return sizeFile() / m_totalLines;
}

uint64_t File::countInFile(const QString &str)
{
    if(!seek(0)){
        return 0;
    }
    if(str == '\n'){
        m_linesMap.erase(m_linesMap.begin(),m_linesMap.end());
    }

    uint64_t counter = 0;
    uint64_t currentSize = 0;

    QByteArray byteArray;
    while(!atEnd()){
        byteArray = read(SIZE_BLOCK * 5); // 50mb
        for(int i = 0; i < byteArray.size();i++){
            if(str == byteArray.at(i)){
                counter++;

                if(str == '\n'){
                    m_linesMap.push_back(currentSize + i);
                }
            }

        }

        currentSize += byteArray.size();

    }

    return counter;

}

void File::setLinesInFile(uint64_t totalLines)
{
    m_totalLines = totalLines;
}

QString File::readAllData()
{
 auto text = m_textStream->read(SIZE_BLOCK);
    return m_textStream->read(SIZE_BLOCK);
}


void File::readBlock(int posScrollBar)
{
    if((size_t)posScrollBar < m_linesMap.size()){
        seek(m_linesMap.at(posScrollBar));
    }else if((size_t)posScrollBar > m_linesMap.size()){
        seek(m_linesMap.at(m_linesMap.size()-1));
    }else if(posScrollBar == 0){
        seek(0);
    }

    // QString text = read(SIZE_BLOCK);
    QString text = m_textStream->read(SIZE_BLOCK);

    needUpdateText(text,posScrollBar);
}

void File::updateText(const QString &text, int posScrollBar)
{
    emit needUpdateText(text,posScrollBar);
}
