#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"
#include "tabdocument.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("TopTeam Text Editor");
    createUI();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::createUI()
{
    ui->tabPanel->clear();
    //ui->tabPanel->setTabsClosable(true);
    //connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
}

void MainWindow::slotNew()
{
    int index = ui->tabPanel->addTab(new TabDocument(), tr("New Document %1").arg(new_document_counter_++));
    ui->tabPanel->setCurrentIndex(index);
}

void MainWindow::slotCloseTab(int index)
{
    if (TabDocument * tab = static_cast<TabDocument*>(ui->tabPanel->widget(index)); tab->close()) {
        tab->deleteLater();
    }
}

void MainWindow::slotExit()
{
    close();
}

void MainWindow::slotAbout()
{
    AboutDialog dlg;
    dlg.exec();
}
