#include "DataUpdateSystem.h"
#include <QDebug>

DataUpdateSystem::DataUpdateSystem()
{
}

void DataUpdateSystem::addEquipment(PowerSystemResource *equipement) {
    this->equipments.append(equipement);
}

void DataUpdateSystem::removeEquipment(PowerSystemResource *equipment) {
    this->equipments.removeAll(equipment);
}

void DataUpdateSystem::updateBreaker(Breaker *breaker, BreakerIED *breakerIED) {

    //Measurement *meas = breaker->measurements[0];


    //Update Breaker Position (Pos)
    //Converte o valor no vetor measurementes para o tipo Discrete, que contem os valores
    Discrete *discreteMeas = dynamic_cast<Discrete*>(breaker->measurements[0]);
    breakerIED->setPos(discreteMeas->discreteValues[0]->value.val);

    qDebug() << breakerIED->getLDName();
    qDebug() << breakerIED->getPos();

    qDebug() << "updata data in breaker";
}

void DataUpdateSystem::updateTrafo(PowerTransformer *trafo, TrafoIED *trafoIED) {

    Discrete *discreteMeas = dynamic_cast<Discrete*>(trafo->measurements[0]);

    qDebug() << "TODO: Dados do trafo para IED";

    trafoIED->setPos(2);
}
