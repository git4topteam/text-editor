#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "aboutdialog.h"

#include <QDebug>
#include <QPushButton>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_fileManager = new FileManager(this);
    QPushButton *addTabButton = new QPushButton("+",ui->tabWidget);

    connect(addTabButton,&QPushButton::clicked,this,&MainWindow::addTextArea);
    connect(ui->tabWidget,&QTabWidget::tabCloseRequested,this,&MainWindow::closeTab);
    setWindowTitle("TopTeam Text Editor");


    ui->tabWidget->setCornerWidget(addTabButton,Qt::TopLeftCorner);
    ui->tabWidget->setTabsClosable(true);
    ui->tabWidget->setMovable(true);

    addTextArea();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    Q_UNUSED(event);
    //    for(auto& textArea : m_textAreas){
    //    textArea->resize(textArea->width(),textArea->height());
    //    }

    TextArea& area = *m_textAreas.at(ui->tabWidget->currentIndex());
    area.resize(area.width(),area.height());
}

int MainWindow::getNumDoc()
{
    //1 2 4 5
    for(int i = 0 ; static_cast<size_t> (i) < m_counterNoNameDoc.size(); i++){

        if((i+1) != m_counterNoNameDoc.at(i)){
            //int dif = counterNewDoc.at(i) - (i+1);
            m_counterNoNameDoc.insert(m_counterNoNameDoc.begin() + i, i + 1);
            return i+1;

        }
    }

    if(m_counterNoNameDoc.empty()){
        m_counterNoNameDoc.push_back(1);
        return m_counterNoNameDoc.back();
    }else{
        m_counterNoNameDoc.push_back( m_counterNoNameDoc.back() + 1 );
        return m_counterNoNameDoc.back();
    }
}

void MainWindow::addTextArea(int index)
{
    Q_UNUSED(index);

    TextArea* area = new TextArea(this);

    QString numDoc = QString::number(getNumDoc());

    ui->tabWidget->addTab(area,"new "+numDoc+" ");
    ui->tabWidget->setCurrentWidget(area);

    m_textAreas.push_back(area);
}

void MainWindow::on_actionTarget_1_2_triggered()
{
    QString pathFile = QFileDialog::getOpenFileName(0, "Open File", ""); //"*.txt " , если добавить это, будет искать только по этой маске
    if(pathFile == ""){
        return void();
    }

    if(!m_fileManager->openFile(pathFile)){
        QMessageBox msg;
        msg.setText("Ошибка");
        msg.setInformativeText("Не удалось открыть файл!");
        msg.setStandardButtons(QMessageBox::Ok);
        msg.exec();
        return void();
    }

    m_textAreas[ui->tabWidget->currentIndex()]->setFile(m_fileManager->getFile());

    int pos = ui->tabWidget->tabText(ui->tabWidget->currentIndex()).indexOf(" ");
    int numDoc = ui->tabWidget->tabText(ui->tabWidget->currentIndex()).right(pos).toInt();
    m_counterNoNameDoc.erase(std::remove(m_counterNoNameDoc.begin(), m_counterNoNameDoc.end(), numDoc), m_counterNoNameDoc.end());

    int posSeparator = pathFile.lastIndexOf("/");
    int dif = pathFile.length() - posSeparator;
    QString fileName = pathFile.right(dif-1);
    ui->tabWidget->setTabText(ui->tabWidget->currentIndex(),fileName);
}

void MainWindow::closeTab(int index)
{
    //не удалять из счетчика безымянных документов, если файл привязан, ведь у него уже есть имя
    if(!m_textAreas.at(index)->fileIsAssigned()){

        int pos = ui->tabWidget->tabText(index).indexOf(" ");
        int numDoc = ui->tabWidget->tabText(index).right(pos).toInt();

        m_counterNoNameDoc.erase(std::remove(m_counterNoNameDoc.begin(), m_counterNoNameDoc.end(), numDoc), m_counterNoNameDoc.end());
    }

    ui->tabWidget->removeTab(index);
    m_fileManager->closeFile(index);
    delete m_textAreas[index];
    m_textAreas.erase(m_textAreas.begin() + index);




    if(m_textAreas.empty()){
        addTextArea();  // если последний элемент, то просто очищаем текстарею
    }

}

void MainWindow::slotAbout()
{
    AboutDialog dlg(this);
    dlg.exec();
}

void MainWindow::slotNew()
{
    addTextArea();
}

void MainWindow::slotExit()
{
    exit(0);
}





