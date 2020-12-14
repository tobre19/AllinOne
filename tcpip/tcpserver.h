#ifndef TCPSERVER_H
#define TCPSERVER_H
#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class tcpserver : public QObject
{
    Q_OBJECT

public:
    explicit tcpserver(QObject *parent = 0);

signals:

public slots:
    void newConnection();

private:
    QTcpServer* server;
};



#endif // TCPSERVER_H
