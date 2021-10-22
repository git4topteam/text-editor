#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_fileManager = new FileManager(this);



    initTextArea();
}

void MainWindow::testLoadFile() // потом эта функция переедет в событие нажатие кнопки
{
    QString pathFile = QFileDialog::getOpenFileName(0, "Открыть файл", "", "*.txt ");

    if(!m_fileManager->openFile(pathFile)){
        QMessageBox msg;
        msg.setText("Ошибка");
        msg.setInformativeText("Не удалось открыть файл!");
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
    }
    int currentIndexInTab = 0; // в дальнейшем,получить индекс открытой вкладки в таб виджете
    m_textAreas[currentIndexInTab]->setFile(m_fileManager->getFile());
}

void MainWindow::testAddNewFile()
{
    //тест
    static int index = 0;
    index++;  //потом переделаю на конкретную вкладку


    initTextArea(index);
}

//void MainWindow::resizeEvent(QResizeEvent *event)
//{
//    if(m_textAreas.size() > 0){ // test
//    qDebug() << m_textAreas.back()->width();
//    qDebug() << m_textAreas.back()->height();
//    }

//}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initTextArea(int index)
{
    TextArea* area = new TextArea(this);
//   area->resize(600,300);
//   area->show();
       QGridLayout *mainLayout = new QGridLayout(); // потом нужно будет добавить в таб виджет

       mainLayout->addWidget(area, 0, 0);
       mainLayout->addWidget(area, 1, 0);

       ui->centralwidget->setLayout(mainLayout);


    m_textAreas.push_back(area);
}





























