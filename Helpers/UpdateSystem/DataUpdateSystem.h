#ifndef DATAUPDATESYSTEM_H
#define DATAUPDATESYSTEM_H

#include <PowerSystemResource.h>
#include <IEC61850Object.h>
#include <Measurement.h>
#include <Breaker.h>
#include <Discrete.h>
#include <Analog.h>
#include <PowerTransformer.h>
#include "PIU/BreakerIED.h"
#include <BusbarSection.h>
#include "PIU/busied.h"
#include "PIU/TrafoIED.h"


class DataUpdateSystem
{
private:
    QList<PowerSystemResource*> equipments;
public:
    DataUpdateSystem();
    void addEquipment(PowerSystemResource *equipement);
    void removeEquipment(PowerSystemResource *equipment);


    void updateBreaker(Breaker *breaker, BreakerIED *breakerIED);
    void updateBus (BusbarSection *busbar, BusIED *busIED);
    void updateTrafo(PowerTransformer *trafo, TrafoIED *trafoIED);

};

#endif // DATAUPDATESYSTEM_H
