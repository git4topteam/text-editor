#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "filemanager.h"
#include "textarea.h"
#include <QVBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void testLoadFile();
    void testAddNewFile(); //типо новая вкладка
protected:
//   void resizeEvent(QResizeEvent *event) override;



private:
    std::vector<TextArea*> m_textAreas; // у нас же будет много текстАрей, как в NotePad , предлагаю сделать, при нажатии на + , создавать еще одно окно с новым файлом. GRISHA KRASNOV
    FileManager* m_fileManager;
    Ui::MainWindow *ui;

 private:
    void initTextArea(int index = 0);

};
#endif // MAINWINDOW_H
