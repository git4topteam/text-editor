#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "aboutdialog.h"

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
    //connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(slotExit()));
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
