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

    qDebug() << "updated data in breaker";
}

void DataUpdateSystem::updateTrafo(PowerTransformer *trafo, TrafoIED *trafoIED) {

    Discrete *measurement = dynamic_cast<Discrete*>(trafo->measurements[4]);

    qDebug() << "TODO: Dados do trafo para IED";
    qDebug() << trafoIED->getLDName();
    qDebug() << measurement->discreteValues[0]->value.val;

    trafoIED->setPos(measurement->discreteValues[0]->value.val);
}

void DataUpdateSystem::updateBus(BusbarSection *busbar, BusIED *busIED) {

    Analog *analogMeas = dynamic_cast<Analog*>(busbar->measurements[0]);
    busIED->setVol(analogMeas->analogValues[0]->value.val);

    qDebug() << analogMeas;
    qDebug() << "TODO: Updated Analog Values for bus";
}
