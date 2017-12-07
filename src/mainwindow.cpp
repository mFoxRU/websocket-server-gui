#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("WebSocket Server @ localhost:"+QString::number(PORT));

    serv = new WebServ(PORT);
    connect(serv, WebServ::gotConnection, this, [this]{updateStatus("Connected");});
    connect(serv, WebServ::lostConnection, this, [this]{updateStatus("Disconnected");});
    connect(serv, WebServ::gotMessage, this->ui->text_output, QTextEdit::append);
    connect(this->ui->button_send, QPushButton::clicked, this, MainWindow::sendMessageSlot);
    connect(this, MainWindow::sendMessage, serv, WebServ::sendMessage);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete serv;
}

void MainWindow::updateStatus(QString status)
{
    ui->status_bar->showMessage(status);
}

void MainWindow::sendMessageSlot()
{
    QString msg = this->ui->input_send->currentText();
    emit this->sendMessage(msg);
    if (this->ui->input_send->findText(msg) == -1)
        this->ui->input_send->addItem(msg);
}

