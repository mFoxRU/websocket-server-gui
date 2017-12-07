#include "webserv.h"

#include <QDebug>

QT_USE_NAMESPACE

WebServ::WebServ(int port, QString name, QObject *parent): QObject(parent)
{
    webSocketServer = new QWebSocketServer(name, QWebSocketServer::NonSecureMode, this);
    webSocketServer->listen(QHostAddress::Any, port);
    connect(webSocketServer, QWebSocketServer::newConnection, this, WebServ::onConnection);
    client = new QWebSocket();

}

WebServ::~WebServ() {
    webSocketServer->close();
}


void WebServ::sendMessage(QString msg) {
    if (connected && client->isValid()) {
        client->sendTextMessage(msg);
    }
}

void WebServ::onConnection() {
    if (connected) {
        webSocketServer->nextPendingConnection()->close();
        return;
    }

    connected = true;
    client = webSocketServer->nextPendingConnection();
    connect(client, QWebSocket::textMessageReceived, this, WebServ::gotMessage);
    connect(client, QWebSocket::disconnected, this, WebServ::onConnectionLost);
    emit gotConnection();
}

void WebServ::onConnectionLost()
{
    connected = false;
    emit lostConnection();
    client->deleteLater();
}

