#pragma once

#include <QWidget>

class TabDocument : public QWidget
{
    Q_OBJECT
public:
    explicit TabDocument(QWidget *parent = nullptr);

protected:
    void closeEvent(QCloseEvent *event) override;

signals:

};
