#include "tcpserver.h"

tcpserver::tcpserver(QObject* parent) : QObject(parent) {
    server = new QTcpServer(this);
    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if (!server->listen(QHostAddress::any, 54000))
    {
        qDebug() << "Server not started";
    }

    else {
        qDebug() << "Server started";
    }
}

void tcpserver::newConnection() {
    QTcpSocket* socket = server->nextPendingConnection();
    socket->write("(5)");
}
