#ifndef CLIENTSOCKET_H
#define CLIENTSOCKET_H
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <netdb.h>
#include "error.h"
#include <QTextStream>
#include <QTcpSocket>

class ClientSocket : public QObject
{
Q_OBJECT
public :
     ClientSocket();
public slots :
    void connect(std::string, int);  // en provenance de l'IHM et se connecte au serveur
    void write(std::string data); // en provenance de l'IHM et écrit sur la socket
private slots :
    void _disconnected();
    void _connected();
    void read();
signals :
    void onConnected();
    void onDisconnected();
    void onMessage(std::string);
private:
    std::string address;
    int port;
    QTcpSocket socket;
};

#endif // CLIENTSOCKET_H
