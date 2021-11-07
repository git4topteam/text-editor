#include "tabdocument.h"
#include <QCloseEvent>
#include <QMessageBox>
#include <QRandomGenerator>

TabDocument::TabDocument(QWidget *parent) : QWidget(parent)
{

}

void TabDocument::closeEvent(QCloseEvent *event)
{
    if (QRandomGenerator::global()->generate() & 1) {
        QMessageBox msgBox;
        msgBox.setText("Fuck off!");
        msgBox.exec();
        event->ignore();
    } else {
        event->accept();
    }
}
