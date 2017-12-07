#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "webserv.h"

#define PORT 62388

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    sendMessage(QString msg);

private:
    Ui::MainWindow *ui;
    WebServ *serv;

private slots:
    void updateStatus(QString status);
    void sendMessageSlot();

};

#endif // MAINWINDOW_H
