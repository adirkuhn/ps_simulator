#include "Sender.h"
#include <QDebug>

Sender::Sender()
{
    groupAddress = QHostAddress("179.106.217.203");
    messageNo = 1;
    udpSocket = new QUdpSocket;

    qDebug() << QString("Ready to multicast datagrams to group %1 on port 45454.").arg(groupAddress.toString());

}

void Sender::sendDatagram(QJsonObject dataToSend) {
    QJsonDocument jsonDocument(dataToSend);

    qDebug() << QString("Now sending datagram %1.").arg(messageNo);

    //QByteArray datagram = "Multicast message " + QByteArray::number(messageNo);
    QByteArray datagram = jsonDocument.toJson();

    qDebug() << datagram;

    udpSocket->writeDatagram(datagram, datagram.size(), groupAddress, 45454);
    messageNo++;
}

QJsonObject Sender::encodeData(SimulatorData *simData) {
    QJsonObject object;
    QJsonObject breakers;
    QJsonObject buses;
    QJsonObject trafos;


    //breakers encode
    for (int b = 0; b < simData->getCIMModel()->getBreakersIED().size(); b++ ) {
        //qDebug() << "Parse dos dados de breaker";
        //qDebug() << simData->getCIMModel()->getBreakers().at(b)->getLDName();
        //qDebug() << QString("Count: %1").arg(b);

        //popula lista de breakers
        breakers.insert(simData->getCIMModel()->getBreakersIED().at(b)->getLDName(), simData->getCIMModel()->getBreakersIED().at(b)->getPos());
    }
    object["breakers"] = breakers;

    //buses encode
    for(int b = 0; b < simData->getCIMModel()->getBusesIED().size(); b++) {
        buses.insert(simData->getCIMModel()->getBusesIED().at(b)->getLDName(), simData->getCIMModel()->getBusesIED().at(b)->getVol());
    }
    object["buses"] = buses;

    //trafos encode
    for(int t = 0; t < simData->getCIMModel()->getTrafosIED().size(); t++) {
        QJsonObject trafo;

        trafo["pos"] = simData->getCIMModel()->getTrafosIED().at(t)->getPos();
        trafo["endposl"] = simData->getCIMModel()->getTrafosIED().at(t)->getEndPosL();
        trafo["endposr"] = simData->getCIMModel()->getTrafosIED().at(t)->getEndPosR();

        trafos.insert(simData->getCIMModel()->getTrafosIED().at(t)->getLDName(), trafo);
    }
    object["trafos"] = trafos;

    qDebug() << object;

    return object;
}
