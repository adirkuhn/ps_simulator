#ifndef SENDER_H
#define SENDER_H

#include <QHostAddress>
#include <QtNetwork>
#include <QJsonArray>
#include <QJsonObject>
#include <Simulator/simulatordata.h>

class Sender
{
private:
    QHostAddress groupAddress;
    QUdpSocket *udpSocket;
    int messageNo;

public:
    Sender();
    void sendDatagram(QJsonObject dataToSend);
    QJsonObject encodeData(SimulatorData *simData);
};

#endif // SENDER_H
