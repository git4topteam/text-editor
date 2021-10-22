#include "lazyreader.h"

LazyReader::LazyReader(QObject *object) : QObject(object)
{

}

void LazyReader::readBlock(int posScrollBar, int maxScrollBarPos)
{
    QString text = "fg";
    emit readFinished(text);
}
