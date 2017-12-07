#ifndef WEBSERV_H
#define WEBSERV_H

#include <QObject>
#include "QtWebSockets/qwebsocketserver.h"
#include "QtWebSockets/qwebsocket.h"

class WebServ: public QObject
{
    Q_OBJECT
public:
    WebServ(int port, QString name="WebSocket server", QObject *parent = Q_NULLPTR);
    ~WebServ();

public slots:
    void sendMessage(QString msg);

signals:
    gotConnection();
    lostConnection();
    gotMessage(QString msg);

private:
    QWebSocketServer *webSocketServer;
    QWebSocket *client;
    bool connected = false;

private slots:
    void onConnection();
    void onConnectionLost();

};

#endif // WEBSERV_H
