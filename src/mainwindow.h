#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void slotNew();
    void slotExit();
    void slotAbout();

    void slotCloseTab(int index);

private:
    Ui::MainWindow *ui;

    size_t new_document_counter_{1};
private:
    void createUI();
};
